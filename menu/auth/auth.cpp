#include "auth.h"

bool authVars::logincalled = false; // crack detection
bool authVars::Login = false;
bool authVars::initiatelogin = false;
int authVars::activeCount = 0;
int authVars::paidAtiveCount = 0;
bool authVars::gotNewsletter = false;
bool authVars::getnewsletter = false;
std::string authVars::sessionID = "";
std::string authVars::newsletter = "";
std::string authVars::statusText = OBF("...");
char authVars::usernameBuf[64] = "";
char authVars::passwordBuf[64] = "";
std::string authVars::username = "";
std::string authVars::password = "";
std::string authVars::expirydate = "";
bool authVars::isUsingProxy = false;

size_t WriteCallback(char* ptr, size_t size, size_t nmemb, std::string* data) {
    size_t bytes = size * nmemb;
    data->append(ptr, bytes);
    return bytes;
}

std::string openssl_sha(const char* data) {
    std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
    unsigned int len;
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fslog::error(OBF("Failed to create EVP_MD_CTX"));
        return "";
    }
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1 ||
        EVP_DigestUpdate(ctx, data, strlen(data)) != 1 ||
        EVP_DigestFinal_ex(ctx, hash.data(), &len) != 1) {
        fslog::error(OBF("SHA-256 hashing failed"));
        EVP_MD_CTX_free(ctx);
        return "";
    }
    EVP_MD_CTX_free(ctx);
    std::stringstream ss;
    for (unsigned int i = 0; i < len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

std::string md5(const std::string& content) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_md5();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    std::string output;

    EVP_DigestInit_ex(context, md, NULL);
    EVP_DigestUpdate(context, content.c_str(), content.length());
    EVP_DigestFinal_ex(context, md_value, &md_len);
    EVP_MD_CTX_free(context);

    output.resize(md_len * 2);
    for (unsigned int i = 0; i < md_len; ++i)
        sprintf_s(&output[i * 2], output.size() - i * 2 + 1, "%02x", md_value[i]);
    return output;
}

std::string getMAC() {
    std::string macAddress;
    IP_ADAPTER_INFO* AdapterInfo = nullptr;
    ULONG outBufLen = sizeof(IP_ADAPTER_INFO);

    AdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(malloc(outBufLen));
    if (AdapterInfo == nullptr) {
        fslog::error(OBF("Error allocating memory needed to call GetAdaptersInfo"));
        return "";
    }

    if (GetAdaptersInfo(AdapterInfo, &outBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(AdapterInfo);
        AdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(malloc(outBufLen));
        if (AdapterInfo == nullptr) {
            fslog::error(OBF("Error allocating memory needed to call GetAdaptersInfo"));
            return "";
        }
    }

    if (GetAdaptersInfo(AdapterInfo, &outBufLen) == NO_ERROR) {
        PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
        do {
            char mac[18];
            sprintf_s(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
                pAdapterInfo->Address[0], pAdapterInfo->Address[1],
                pAdapterInfo->Address[2], pAdapterInfo->Address[3],
                pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
            macAddress = mac;

            pAdapterInfo = pAdapterInfo->Next;
        } while (pAdapterInfo);
    }

    free(AdapterInfo);
    return macAddress;
}



std::string GetDeviceID() {
    DWORD volumeSerialNumber;
    GetVolumeInformation(L"C:\\", NULL, 0, &volumeSerialNumber, NULL, NULL, NULL, 0);

    std::stringstream ss;
    ss << std::hex << volumeSerialNumber;
    std::string cserial = ss.str();
    std::string final = cserial + getMAC();
    return final;
}

std::string auth::sendRequest(const std::string& url, const std::string& method, const std::string& userAgent) {
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    CURLcode res;
    std::string response_data;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        if (method == OBF("POST")) {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
        } else if (method == OBF("GET")) {
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        } else if (method == OBF("OPTIONS")) {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, OBF("OPTIONS"));
        }
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, (OBF("User-Agent: ") + userAgent).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fslog::error(OBF("Send request failed, error: {}"), curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
    return response_data;
}

void auth::pingFREE(std::string sessionID, int& activeCount) {
    std::string hashedID = md5(sessionID);
    std::string url = OBF("https://yeetdisdude.xyz/api/pingFREE?sessionid=") + hashedID;
    std::string response = auth::sendRequest(url, OBF("GET"), OBF("yddModMenuPC"));
    
    try {
        nlohmann::json jsonData = nlohmann::json::parse(response);
        activeCount = jsonData[OBF("active")].get<int>();
        // fslog::info("Pinged! Active Asteroid Users: {}", activeCount);
    } catch (const nlohmann::json::parse_error& e) {
        fslog::error(OBF("[Can be ignored] JSON parsing error when pinging: {} | r: {}"), e.what(), response);
        activeCount = 0;
    } catch (const std::exception& e) {
        fslog::error(OBF("[Can be ignored] An error occurred when pinging: {} | r: {}"), e.what(), response);
        activeCount = 0;
    }
}

std::string auth::get_newsletter() {
    std::string url = OBF("https://yeetdisdude.xyz/status/pc_newslettter");
    std::string response = auth::sendRequest(url, OBF("GET"), OBF("yddModMenuPC"));
    return response;
}

void auth::checkProxyStatus(bool &res) {
    INTERNET_PER_CONN_OPTION_LIST optionList;
    DWORD optionSize = sizeof(optionList);
    INTERNET_PER_CONN_OPTION options[1];
    options[0].dwOption = INTERNET_PER_CONN_FLAGS;

    optionList.dwSize = sizeof(optionList);
    optionList.pszConnection = NULL;
    optionList.dwOptionCount = 1;
    optionList.dwOptionError = 0;
    optionList.pOptions = options;

    if (InternetQueryOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &optionList, &optionSize)) {
        res = options[0].Value.dwValue & PROXY_TYPE_PROXY;
    } else {
        fslog::error(OBF("Error querying proxy settings: "));
        res = false;
    }
}
    
#ifndef FREEVERSION
void auth::niggas(std::string username, std::string password, bool& login, std::string& statusText, std::string id, std::string auth) {
    std::string deviceID = md5(GetDeviceID());
    password = openssl_sha(password.c_str());
    std::string url = OBF("https://yeetdisdude.xyz/api/auth/AsteroidPCLogin?username=") + username +
               OBF("&password=") + password +
               OBF("&deviceid=") + deviceID +
               OBF("&id=") + id +
               OBF("&auth=") + auth ;
    try {
        std::string response = auth::sendRequest(url, OBF("POST"), OBF("yddModMenuPC"));
        if (response == OBF("1")) {
            authVars::statusText = OBF("The username or password is invalid.");
        } else if (response == OBF("2")) {
            authVars::statusText = OBF("Your subscription has expired.");
        } else if (response == OBF("3")) {
            authVars::Login = true;
            authVars::logincalled = true;
        } else if (response == OBF("4")) {
            authVars::statusText = OBF("You are not allowed to use Asteroid on this device.");
        } else {
            authVars::statusText = OBF("Something went wrong on the server... check the console");
            fslog::error(OBF("Response: {}"), response);
        }
    } catch (const std::exception& e) {
        fslog::error(OBF("An error occurred when logging in: {}"), e.what());
    }
    // fslog::info("response: {}", response);
}

void auth::getActiveUsers(std::string username, std::string password, int &activeUserCount) {
    password = openssl_sha(password.c_str());
    std::string url = OBF("https://yeetdisdude.xyz/api/ping?username=") + username + OBF("&password=") + password;
    std::string response = auth::sendRequest(url, OBF("GET"), OBF("yddModMenu"));

    try {
        nlohmann::json jsonData = nlohmann::json::parse(response);
        activeUserCount = jsonData[OBF("active")].get<int>();
    } catch (const nlohmann::json::parse_error& e) {
        fslog::error(OBF("[Can be ignored] JSON parsing error when pinging: {} | r: {}"), e.what(), response);
    } catch (const std::exception& e) {
        fslog::error(OBF("[Can be ignored] An error occurred when pinging: {} | r: {}"), e.what(), response);
    }
}

void auth::getInfo(std::string username, std::string password, std::string&expirydate) {
    password = openssl_sha(password.c_str());
    std::string url = OBF("https://yeetdisdude.xyz/api/getUserInfo?username=") +  username + OBF("&password=") + password;
    std::string response = auth::sendRequest(url, OBF("GET"), OBF("yddModMenuPC"));
    
    try {
        nlohmann::json jsonData = nlohmann::json::parse(response); 
        expirydate = jsonData[OBF("expiry")].get<std::string>();
        std::replace(expirydate.begin(), expirydate.end(), '-', '/');
    } catch (const std::exception& e) {
        fslog::error(OBF("An error occurred when getting user info: {} | r: {}"), e.what(), response);
    }
}

void auth::saveCreds(const char* username, const char* password) {
    std::ofstream configFile(OBF("auth.asteroid"));
    if (configFile.is_open()) {
        configFile << username << std::endl;
        configFile << password << std::endl;
        configFile.close();
    }
}

void auth::loadCreds(char* usernameBuf, char* passwordBuf, size_t bufSize) {
    std::ifstream configFile(OBF("auth.asteroid"));
    if (configFile.is_open()) {
        configFile.getline(usernameBuf, bufSize);
        configFile.getline(passwordBuf, bufSize);
        configFile.close();
    }
}

#endif