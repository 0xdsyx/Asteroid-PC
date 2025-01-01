#include <string>
#include <filesystem>
#include <fstream>
#include <openssl/evp.h>
#include <openssl/rand.h>

#include "fslog.hpp"
#include "obfusheader.h"
#include "json.h"

#include "menufeatures.h"

std::vector<unsigned char> AES_Encrypt(const std::string& data);
std::string AES_Decrypt(const std::vector<unsigned char>& ciphertext);
namespace config {
    void SaveKeyToJson(const std::string& key, const nlohmann::json& value);

    template<typename T>
    T LoadKeyFromJson(const std::string& key, const T& defaultValue);

    void SaveConfigs();
    void LoadConfigs();
}

#define LOADKEY(key, defaultv) config::LoadKeyFromJson(OBF(key), defaultv)
#define SAVEKEY(key, value) config::SaveKeyToJson(OBF(key), value)