#include "utils.h"

using namespace IL2CPP::Class::Utils;
bool hook(void* address, void* new_func, void** old_func, std::string id) {
	if (MH_CreateHook(address, new_func, old_func) != MH_OK) {
		fslog::error(OBF("Create Hook Failed at: {} | ID: {}"), address, id);
		return false;
	}
	if (MH_EnableHook(address) != MH_OK) {
		fslog::error(OBF("Enable Hook failed at: {} | ID: {}"), address, id);
		return false;
	}
	
	// fslog::info(OBF("Hooked at: {} | ID: {}"), address, id);
	return true;
}

std::string TraceMethod(const SignatureCondition &pattern) {
    std::string out = HANDLE_NULL_STR(pattern.modifier) + HANDLE_NULL_STR(pattern.typeName) + HANDLE_NULL_STR(pattern.name) + " ";

    if(!pattern.paramTypeName.empty()) {

        bool first = true;

        std::string str;

        for(int i = 0; i < std::size(pattern.paramTypeName); i++) {
            str += first ? HANDLE_NULL_STR(pattern.paramTypeName[i]) : ", " + HANDLE_NULL_STR(pattern.paramTypeName[i]);
            first = false;
        }

        out = + "{" + str + "}";
    }

    return out;
}

std::string GetMethodModifier(uint32_t flags) {
    std::stringstream outPut;
    auto access = flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK;

    switch (access) {
        case METHOD_ATTRIBUTE_PRIVATE:
            outPut << "private ";
            break;
        case METHOD_ATTRIBUTE_PUBLIC:
            outPut << "public ";
            break;
        case METHOD_ATTRIBUTE_FAMILY:
            outPut << "protected ";
            break;
        case METHOD_ATTRIBUTE_ASSEM:
        case METHOD_ATTRIBUTE_FAM_AND_ASSEM:
            outPut << "internal ";
            break;
        case METHOD_ATTRIBUTE_FAM_OR_ASSEM:
            outPut << "protected internal ";
            break;
    }
    if (flags & METHOD_ATTRIBUTE_STATIC) {
        outPut << "static ";
    }
    if (flags & METHOD_ATTRIBUTE_ABSTRACT) {
        outPut << "abstract ";
        if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
            outPut << "override ";
        }
    } else if (flags & METHOD_ATTRIBUTE_FINAL) {
        if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
            outPut << "sealed override ";
        }
    } else if (flags & METHOD_ATTRIBUTE_VIRTUAL) {
        if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_NEW_SLOT) {
            outPut << "virtual ";
        } else {
            outPut << "override ";
        }
    }
    if (flags & METHOD_ATTRIBUTE_PINVOKE_IMPL) {
        outPut << "extern ";
    }

    return outPut.str();
}


void* GetMethodPointerPattern(Unity::il2cppClass* klass, const SignatureCondition &pattern , int indexOffset) {
    if (klass == nullptr) {
        fslog::info("First arg (Il2CppClass*) is null. Target: {}", pattern.toString());
        return 0;
    }
	int method_count = 0;

    void* iterator = nullptr;
    Unity::il2cppMethodInfo* methodInfo = nullptr;

    std::vector<Unity::il2cppMethodInfo*> allMethods;
    while (methodInfo = IL2CPP::Class::GetMethods(klass, &iterator)) {
        method_count++;
        allMethods.push_back(methodInfo);
    }

     if(method_count <= 0) {
        fslog::error("No methods founded in {}", klass->m_pName);
        return 0;
    }

    int i = 0; void* iterator2 = nullptr;
    while (methodInfo = IL2CPP::Class::GetMethods(klass, &iterator2)) {
        Unity::il2cppMethodInfo* method = methodInfo;

        int checkScore = 0;

        uint32_t iflags = 0;
        uint32_t flags = IL2CPP::Class::Utils::MethodGetFlags(method, &iflags);

        std::string methodName = IL2CPP::Class::Utils::MethodGetName(method);
        std::string methodModif = GetMethodModifier(flags);
        std::string methodTypeName = ClassGetName(ClassFromType(MethodGetReturnType(method)));
        int methodParamCount = GetMethodParamCount(method);

        methodModif.pop_back();

        if (pattern.name == nullptr) {
            checkScore++;
        } else if(methodName == pattern.name) {
            checkScore++;
        }

        if (pattern.modifier == nullptr) {
            checkScore++;
        } else if(methodModif == pattern.modifier) {
            checkScore++;
        }

        if (pattern.typeName == nullptr) {
            checkScore++;
        } else if(methodTypeName == pattern.typeName) {
            checkScore++;
        }

        if(pattern.paramTypeName.size() > 0 && pattern.paramTypeName.size() == methodParamCount) {
            int successParamScore = 0;
            for (int i2 = 0; i2 < pattern.paramTypeName.size(); ++i2) {
                if (pattern.paramTypeName[i2] != nullptr) {
                    std::string typeName = pattern.paramTypeName[i2];
                    Unity::il2cppClass* paramClass = ClassFromType(GetMethodParamType(method, i2));
                    bool is_enum = ClassIsEnum(paramClass);
                    bool is_value = ClassIsValueType(paramClass);

                    if(typeName == "ENUM" && is_enum) {
                        successParamScore++;
                    } else if(typeName == "VALUE" && is_value && !is_enum) {
                        if(ClassIsValueType(ClassFromType(GetMethodParamType(method, i2)))) {
                            successParamScore++;
                        }
                    } else if (typeName == ClassGetName(ClassFromType(GetMethodParamType(method, i2)))) {
                        successParamScore++;
                    }
                } else {
                    successParamScore++;
                }
            }

            if (successParamScore == pattern.paramTypeName.size()) {
                checkScore++;
            }

        }
        else if(pattern.paramTypeName.size() == 0) {
            checkScore++;
        }
        if(checkScore >= 4) {
            if (indexOffset == 0) {
                void* ret = method->m_pMethodPointer;
                if (ret == nullptr) {
                    fslog::error(OBF("Can't find method signature condition: {}"), pattern.toString());
                }
                return ret;
            }
            void* ret = allMethods[indexOffset]->m_pMethodPointer;
            if (ret == nullptr) {
                fslog::error(OBF("Can't find method signature condition: {}"), pattern.toString());
            }
            return ret;
            
        } 

        i++;
    }

    fslog::error(OBF("Can't find method signature condition: {}"), pattern.toString());
    return 0;
}

uintptr_t get_offset(uintptr_t offset) {
	return (uintptr_t)GetModuleHandleW(L"GameAssembly.dll") + offset;
}

uintptr_t string2Offset(const char* c) {
	int base = 16;
	static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
		|| sizeof(uintptr_t) == sizeof(unsigned long long),
		"Please add string to handle conversion for this architecture.");

	if (sizeof(uintptr_t) == sizeof(unsigned long)) {
		return strtoul(c, nullptr, base);
	}

	return strtoull(c, nullptr, base);
}

int generateRandomNumber(unsigned long long min, unsigned long long max) {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(rng);
}

float generateRandomFloat(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	float randomNumber = dis(gen);
	return static_cast<float>(static_cast<int>(randomNumber * 100 + 0.5f)) / 100.0f;
}

bool cmpByHeight(const Vector3& a, const Vector3& b) {
    return a.Y < b.Y;
}

bool cmpWidth(const Vector3& a, const Vector3& b) {
	return a.X < b.X;
}

std::vector<Vector3> customSort(std::vector<Vector3> arr) {
    std::vector<Vector3> out;
    
    std::sort(arr.begin(), arr.end(), cmpWidth);
    std::vector<Vector3> left, right;
    left.push_back(arr.at(0));
    left.push_back(arr.at(1));
    right.push_back(arr.at(2));
    right.push_back(arr.at(3));
    std::sort(left.begin(), left.end(), cmpByHeight);
    std::sort(right.begin(), right.end(), cmpByHeight);
    out.push_back(left.at(0));
    out.push_back(left.at(1));
    out.push_back(right.at(0));
    out.push_back(right.at(1));
    return out;
}

void copyToClipboard(const char* text) {
	const size_t len = strlen(text) + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), text, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}

std::string stripQuotes(const char* str) {
    std::string original(str); 

    if (original.front() == '\"') {
        original.erase(original.begin());
    }

    if (original.back() == '\"') {
        original.pop_back();
    }

    return original;
}


Vector3 toLocalSpace(Vector3 relPos, Quaternion rot) {
    Quaternion invRot = Quaternion::Inverse(rot);
    Vector3 localVec = invRot * relPos;
    return localVec;
}

Vector3 getExtPos(Vector3 bone, Quaternion boneRot, float off) {
    Vector3 forward = boneRot * Vector3(0, 0, 1);
    Vector3 newBonePos = bone + forward * off;
    return newBonePos;
}

Vector3 addRotationRad(Vector3 euler, float x, float y, float z) {
    Vector3 out = euler + Vector3(x, y, z);
    if (out.X > M_PI) {
        out.X -= 2.f * M_PI;
    }
    else if (out.X < -M_PI) {
        out.X += 2.f * M_PI;
    }

    if (out.Y > M_PI) {
        out.Y -= 2.f * M_PI;
    }
    else if (out.Y < -M_PI) {
        out.Y += 2.f * M_PI;
    }

    if (out.Z > M_PI) {
        out.Z -= 2.f * M_PI;
    }
    else if (out.Z < -M_PI) {
        out.Z += 2.f * M_PI;
    }
    return out;
}

std::string GetKeyName(int virtualKey) {
    UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
    char keyNameBuffer[128];

    LONG lParam = (scanCode << 16);
    if (virtualKey == VK_SHIFT || virtualKey == VK_CONTROL || virtualKey == VK_MENU) {
        lParam |= 1 << 24; 
    }

    int result = GetKeyNameTextA(lParam, keyNameBuffer, sizeof(keyNameBuffer));
    if (result > 0) {
        return std::string(keyNameBuffer);
    }
    return "Unknown"; 
}

std::string rarityNameFromEnum(int rarity) {
	switch (rarity) {
		case ItemRarity::Common:
			return OBF("Common");
			break;
		case ItemRarity::Uncommon:
			return OBF("Uncommon");
			break;
		case ItemRarity::Rare:
			return OBF("Rare");
			break;
		case ItemRarity::Epic:
			return OBF("Epic");
			break;
		case ItemRarity::Legendary:
			return OBF("Legendary");
			break;
		case ItemRarity::Mythic:
			return OBF("Mythic");
			break;
		case ItemRarity::None:
		default:
			return OBF("None");
			break;
	}
}

void ClearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    if (hConsole == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', cellCount, homeCoords, &count)) return;

    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    SetConsoleCursorPosition(hConsole, homeCoords);
}

std::vector<std::string> OpenFileDialog(const wchar_t* filter) {
    OPENFILENAME ofn;
    wchar_t szFile[1024];  // Increase the buffer size to accommodate multiple file paths
    std::vector<std::string> filePaths;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL; 
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_ALLOWMULTISELECT;

    if (GetOpenFileNameW(&ofn) == TRUE) {
        std::wstring folderPath = szFile;
        wchar_t* p = szFile + folderPath.length() + 1;

        if (*p == '\0') {  // Only one file was selected
            filePaths.push_back(std::string(folderPath.begin(), folderPath.end()));
        } else {  // Multiple files were selected
            while (*p) {
                std::wstring filePath = folderPath + L"\\" + p;
                filePaths.push_back(std::string(filePath.begin(), filePath.end()));
                p += wcslen(p) + 1;
            }
        }
    }

    return filePaths; 
}

bool isSkinImageValid(const std::string& filePath) {
    int width, height, channels;
    unsigned char* img = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (!img) {
        std::cerr << "Error loading image: " << stbi_failure_reason() << std::endl;
        return false; 
    }
    
    bool isValid = (width == 64 && height == 32) || (width * 32 == height * 64);
    stbi_image_free(img); 
    return isValid;
}

std::string base64_encode(const std::string &in) {

    std::string out;

    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
}

std::string base64_decode(const std::string &in) {

    std::string out;

    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val=0, valb=-8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return out;
}

std::string encodeFileToBase64(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)), {});
    
    // Convert the vector to a string
    std::string data(buffer.begin(), buffer.end());
    
    return base64_encode(data); // Now this works
}

float CheckFieldPattern(Unity::il2cppClass* klass, FieldPattern& pattern) {

    if(klass == nullptr) {
        fslog::error(OBF("First arg (Il2CppClass*) is null."));
        return false;
    }

    int score = 0;
    void* iter = nullptr;
    while(auto field = IL2CPP::Class::GetFields(klass, &iter)) {
        auto fieldClass = IL2CPP::Class::Utils::ClassFromType(IL2CPP::Class::Utils::FieldGetType(field));

        if(fieldClass == nullptr) {
            continue;
        }

        if(pattern[score] == nullptr) {

            score++;
        }
        else if(strcmp(IL2CPP::Class::Utils::ClassGetName(fieldClass), pattern[score]) == 0) {
            score++;
        }
    }

    float ret = score/pattern.size();
    return ret;
}

bool CheckContentCount(Unity::il2cppClass* klass, std::pair<uint32_t, uint32_t> fieldCountPair, std::pair<uint32_t, uint32_t>  methodCountPair) {
    if(klass == nullptr) {
        fslog::error(OBF("First arg (Il2CppClass*) is null."));
        return false;
    }

    return IL2CPP::Class::Utils::GetFieldCount(klass) >= fieldCountPair.first && IL2CPP::Class::Utils::GetFieldCount(klass) <= fieldCountPair.second &&
           IL2CPP::Class::Utils::GetMethodCount(klass) >= methodCountPair.first && IL2CPP::Class::Utils::GetMethodCount(klass) <= methodCountPair.second; //klass->field_count == fieldCount && klass->method_count == methodCount;
}

void showLoadingBar(int progress, int total) {
    int barWidth = 65;
    int position = barWidth * progress / total;
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < position) std::cout << "=";
        else if (i == position) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int((float(progress) / total) * 100.0) << "%\r";
    std::cout.flush();
}

std::string nullToArray(const std::string &str) {
    std::string::size_type n = 0;
    std::string out = str;
    while ((n = out.find("null", n)) != std::string::npos) {
        out.replace(n, 4, "[]");
        n += 2;
    }
    return out;
}

Vector3 utilsFixW2Sout(Vector3 original, float dxheight) {
	return Vector3(original.X, (dxheight - original.Y), original.Z);
}

void create_console() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD consoleMode;
    if (GetConsoleMode(hInput, &consoleMode)) {
        consoleMode &= ~ENABLE_QUICK_EDIT_MODE;
        consoleMode &= ~ENABLE_MOUSE_INPUT;
        SetConsoleMode(hInput, consoleMode);
    }
}