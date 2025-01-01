#define CURL_STATICLIB
#include <curl/curl.h>
#include <openssl/evp.h>
#include <Wbemidl.h>
#include <comdef.h>
#include <Iphlpapi.h>
#include <wininet.h>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <fstream>
#include "fslog.hpp"
#include "json.h"
#include "obfusheader.h"
#include "../defs.h"
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "wininet.lib")

namespace authVars {
    extern bool logincalled;
    extern bool Login;
    extern bool initiatelogin;
    extern int activeCount;
    extern int paidAtiveCount;
    extern bool gotNewsletter;
    extern bool getnewsletter;
    extern std::string sessionID;
    extern std::string newsletter;
    extern std::string statusText;
    extern char usernameBuf[64];
    extern char passwordBuf[64];
    extern std::string username;
    extern std::string password;
    extern std::string expirydate;
    extern bool isUsingProxy;
}


size_t WriteCallback(char* ptr, size_t size, size_t nmemb, std::string* data);
std::string openssl_sha(const char* data);
std::string md5(const std::string& content);
std::string getMAC();
std::string GetDeviceID();

namespace auth {
    std::string sendRequest(const std::string& url, const std::string& method, const std::string& userAgent);
    void pingFREE(std::string sessionID, int& activeCount);
    std::string get_newsletter();
    void checkProxyStatus(bool &res);

    #ifndef FREEVERSION
    void niggas(std::string username, std::string password, bool& login, std::string& statusText, std::string id, std::string auth);
    void getActiveUsers(std::string username, std::string password, int& activeUserCount);
    void getInfo(std::string username, std::string password, std::string&expirydate);
    void saveCreds(const char* username, const char* password);
    void loadCreds(char* usernameBuf, char* passwordBuf, size_t bufSize);
    #endif
}