#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <random>
#include <memory>
#include <windows.h>
#include <thread>
#include <chrono>
#include <cstdint>
#include <vector>
#include <fstream>
#include <sstream>
#include <wrl/client.h>
#include <d3d11.h>
#include <algorithm>

#include "stb_image.h"
#include "unity/Quaternion.h"
#include "unity/Vector3.h"
#include "obfusheader.h"
#include "fslog.hpp"
#include "MinHook.h"
#include "IL2CPP_Resolver.hpp"
#include "../imgui/imgui.h"
#include "FNPointer.h"

extern ID3D11Device* g_pd3dDevice;

struct SignatureCondition {
    const char* modifier = nullptr;
    const char* typeName = nullptr;
    const char* name = nullptr;
    std::vector<const char*> paramTypeName;

    std::string toString() const {
        std::ostringstream os;
        os << "{";

        os << (modifier ? "\"" + std::string(modifier) + "\"" : "nullptr") << ", ";
        os << (typeName ? "\"" + std::string(typeName) + "\"" : "nullptr") << ", ";
        os << (name ? "\"" + std::string(name) + "\"" : "nullptr") << ", ";

        os << "{";
        for (size_t i = 0; i < paramTypeName.size(); ++i) {
            os << "\"" << paramTypeName[i] << "\"";
            if (i < paramTypeName.size() - 1) {
                os << ", ";
            }
        }
        os << "}";

        os << "}";
        return os.str();
    }
};
typedef std::vector<const char*> FieldPattern;
enum ItemRarity { Common, Uncommon, Rare, Epic, Legendary, Mythic, None = -1 };

#define il2cppString Unity::System_String
#define NewIl2cppString(constchar) IL2CPP::String::New(constchar)
#define HANDLE_NULL_STR(str) std::string(str == nullptr ? "NULL" : str)

#define OFFSET(offset) get_offset(string2Offset(OBF(offset)))
#define IL2CPP_METHOD(klass, name) IL2CPP::Class::Utils::GetMethodPointer(OBF(klass), OBF(name))
#define IL2CPP_METHOD_P(klass, name, paramCount) IL2CPP::Class::Utils::GetMethodPointer(OBF(klass), OBF(name), paramCount)
#define GET_FIELDOFFSET(klass, name) IL2CPP::Class::Utils::GetFieldOffset(OBF(klass), OBF(name))
#define GET_CLASS(klass) IL2CPP::Class::Find(OBF(klass))
#define MINHOOK_IL2CPP(klass, name, function, id) hook(IL2CPP::Class::Utils::GetMethodPointer(OBF(klass), OBF(name)), (void *)function, (void **)&old_##function, OBF(id))
#define MINHOOK(offset, function, id) \
	hook((void*)OFFSET(offset), (void *)function, (void **)&old_##function, OBF(id))
#define MINHOOK2(addr, function, id) \
	hook(addr, (void *)function, (void **)&old_##function, OBF(id))

#define REG_CLASS_NAMECHECK(klass, name)  if(NAME_CHECK(klass, name)) { REG_CLASS(klass, name); }
#define NAME_CHECK(klass, name) strcmp(IL2CPP::Class::Utils::ClassGetName(klass), name) == 0
#define CHECK_CLASSIZE(klass, size) IL2CPP::Class::Utils::ClassGetDataSize(klass) == size
#define NAMESPACE_CHECK(klass, namespaze) strcmp(IL2CPP::Class::Utils::ClassGetNamespace(klass), namespaze) == 0

bool hook(void* address, void* new_func, void** old_func, std::string id);

std::string TraceMethod(const SignatureCondition &pattern);
std::string GetMethodModifier(uint32_t flags);
void* GetMethodPointerPattern(Unity::il2cppClass* klass, const SignatureCondition &pattern , int indexOffset = 0);
uintptr_t get_offset(uintptr_t offset);
uintptr_t string2Offset(const char* c);
int generateRandomNumber(unsigned long long min, unsigned long long max);
float generateRandomFloat(float min, float max);
bool cmpByHeight(const Vector3& a, const Vector3& b);
bool cmpWidth(const Vector3& a, const Vector3& b);
std::vector<Vector3> customSort(std::vector<Vector3> arr);
void copyToClipboard(const char* text);
std::string stripQuotes(const char* str);
Vector3 toLocalSpace(Vector3 relPos, Quaternion rot);
Vector3 getExtPos(Vector3 bone, Quaternion boneRot, float off);
Vector3 addRotationRad(Vector3 euler, float x, float y, float z);
std::string GetKeyName(int virtualKey);
std::string rarityNameFromEnum(int rarity);
void ClearConsole();
std::vector<std::string> OpenFileDialog(const wchar_t* filter);
bool isSkinImageValid(const std::string& filePath);
std::string base64_encode(const std::string &in);
std::string base64_decode(const std::string &in);
std::string encodeFileToBase64(const std::string& filePath);
float CheckFieldPattern(Unity::il2cppClass* klass, FieldPattern& pattern);
std::string FieldPatternToString(FieldPattern fieldPattern);
bool CheckContentCount(Unity::il2cppClass* klass, std::pair<uint32_t, uint32_t> fieldCountPair, std::pair<uint32_t, uint32_t>  methodCountPair);
void showLoadingBar(int progress, int total);
std::string nullToArray(const std::string &str);
Vector3 utilsFixW2Sout(Vector3 original, float dxheight);
void create_console();



#define METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK        0x0007
#define METHOD_ATTRIBUTE_COMPILER_CONTROLLED       0x0000
#define METHOD_ATTRIBUTE_PRIVATE                   0x0001
#define METHOD_ATTRIBUTE_FAM_AND_ASSEM             0x0002
#define METHOD_ATTRIBUTE_ASSEM                     0x0003
#define METHOD_ATTRIBUTE_FAMILY                    0x0004
#define METHOD_ATTRIBUTE_FAM_OR_ASSEM              0x0005
#define METHOD_ATTRIBUTE_PUBLIC                    0x0006
#define METHOD_ATTRIBUTE_STATIC                    0x0010
#define METHOD_ATTRIBUTE_FINAL                     0x0020
#define METHOD_ATTRIBUTE_VIRTUAL                   0x0040
#define METHOD_ATTRIBUTE_HIDE_BY_SIG               0x0080
#define METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK        0x0100
#define METHOD_ATTRIBUTE_REUSE_SLOT                0x0000
#define METHOD_ATTRIBUTE_NEW_SLOT                  0x0100
#define METHOD_ATTRIBUTE_PINVOKE_IMPL              0x2000
#define METHOD_ATTRIBUTE_ABSTRACT                  0x0400