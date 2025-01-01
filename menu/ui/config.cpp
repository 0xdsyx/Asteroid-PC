#include "config.h"

const std::string AES_KEY = OBF("9LzWDSz189gyHZDYmNKLXioHwwHmDIJvmsLXSs+8kZY2I8o3O+4HXuYB7kR4R1WA");
const std::string AES_IV = OBF("d302d71504e6c711fc4c9a6d7b9b0519"); 

std::vector<unsigned char> AES_Encrypt(const std::string& data) {
    std::vector<unsigned char> ciphertext(data.size() + EVP_MAX_BLOCK_LENGTH);
    int len;
    int ciphertext_len;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)AES_KEY.data(), (unsigned char*)AES_IV.data());
    
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, (unsigned char*)data.data(), data.size());
    ciphertext_len = len;
    
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;
    
    ciphertext.resize(ciphertext_len);
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext;
}

std::string AES_Decrypt(const std::vector<unsigned char>& ciphertext) {
    std::vector<unsigned char> decryptedtext(ciphertext.size());
    int len;
    int decryptedtext_len;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)AES_KEY.data(), (unsigned char*)AES_IV.data());

    EVP_DecryptUpdate(ctx, decryptedtext.data(), &len, ciphertext.data(), ciphertext.size());
    decryptedtext_len = len;

    EVP_DecryptFinal_ex(ctx, decryptedtext.data() + len, &len);
    decryptedtext_len += len;

    decryptedtext.resize(decryptedtext_len);
    EVP_CIPHER_CTX_free(ctx);

    return std::string(decryptedtext.begin(), decryptedtext.end());
}

void config::SaveKeyToJson(const std::string& key, const nlohmann::json& value) {
    std::string currentPath = std::filesystem::current_path().string();
    
    nlohmann::json configJson;
    std::ifstream inputFile(currentPath + OBF("/config.asteroid"), std::ios::binary);

    if (inputFile.is_open()) {
        try {
            std::vector<unsigned char> encryptedData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            std::string decryptedData = AES_Decrypt(encryptedData);
            configJson = nlohmann::json::parse(decryptedData);
        } catch (const std::exception& e) {
            fslog::error(OBF("Error reading config file: {}"), e.what());
        }
        inputFile.close();
    }

    configJson[key] = value;

    std::string jsonStr = configJson.dump(4);
    std::vector<unsigned char> encryptedData = AES_Encrypt(jsonStr);

    std::ofstream outputFile(currentPath + OBF("/config.asteroid"), std::ios::binary);
    if (outputFile.is_open()) {
        outputFile.write((char*)encryptedData.data(), encryptedData.size());
        outputFile.close();
    } else {
        fslog::error(OBF("Error writing to config file"));
    }
}

template<typename T>
T config::LoadKeyFromJson(const std::string& key, const T& defaultValue) {
    std::string currentPath = std::filesystem::current_path().string();
    std::ifstream file(currentPath + OBF("/config.asteroid"), std::ios::binary);

    if (file.is_open()) {
        std::vector<unsigned char> encryptedData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        try {
            std::string decryptedData = AES_Decrypt(encryptedData);
            
            nlohmann::json configJson = nlohmann::json::parse(decryptedData);
            return configJson.value(key, defaultValue);
        } catch (const std::exception& e) {
            fslog::error(OBF("Error reading config file: {}"), e.what());
        }
    } else {
        // fslog::warn(OBF("config not found, using default settings..."));
    }

    return defaultValue;
}

template int config::LoadKeyFromJson<int>(const std::string& key, const int& defaultValue);
template std::string config::LoadKeyFromJson<std::string>(const std::string& key, const std::string& defaultValue);


void config::SaveConfigs() {
    SAVEKEY("aimbot", Features::GameplayAimbot::aimbot);
    SAVEKEY("visibilityCheck", Features::GameplayAimbot::visibilitycheck);
    SAVEKEY("leftclicktrigger", Features::GameplayAimbot::leftclicktrigger);
    SAVEKEY("triggerbot", Features::GameplayAimbot::triggerbot);
    SAVEKEY("showfov", Features::GameplayAimbot::showfov);
    SAVEKEY("colorchangingfov", Features::GameplayAimbot::colorchangingfov);
    SAVEKEY("rgbfov", Features::GameplayAimbot::rgbfov);
    SAVEKEY("customcolor", Features::GameplayAimbot::customcolor);
    SAVEKEY("smoothing", Features::GameplayAimbot::smoothing);
    SAVEKEY("aimatindex", Features::GameplayAimbot::aimatIndex);
    SAVEKEY("fovsize", Features::GameplayAimbot::fovsize);
    SAVEKEY("esp", Features::GameplayESP::esp);
    SAVEKEY("espbone", Features::GameplayESP::espbone);
    SAVEKEY("espline", Features::GameplayESP::espline);
    SAVEKEY("espbox", Features::GameplayESP::espbox);
    SAVEKEY("esp3dbox", Features::GameplayESP::esp3dbox);
    SAVEKEY("esphealth", Features::GameplayESP::esphealth);
    SAVEKEY("espdistance", Features::GameplayESP::espdistance);
    SAVEKEY("teamcolor", Features::GameplayESP::teamcolor);
    SAVEKEY("enemycolor", Features::GameplayESP::enemycolor);
    SAVEKEY("showteam", Features::GameplayESP::showteam);
    SAVEKEY("showenemy", Features::GameplayESP::showenemy);
    SAVEKEY("esporigin", Features::GameplayESP::esporigin);
    SAVEKEY("showping", Features::GameplayESP::showping);
    SAVEKEY("killall", Features::GameplayMain::killall);
    SAVEKEY("godmode", Features::GameplayMain::godmode);
    SAVEKEY("friendlyfire", Features::GameplayMain::friendlyfire);
    SAVEKEY("polymorph", Features::GameplayMain::polymorph);
    SAVEKEY("silentaim", Features::GameplayMain::silentaim);
    SAVEKEY("infammo", Features::GameplayMain::infammo);
    SAVEKEY("killpoints", Features::GameplayMain::killpoints);
    SAVEKEY("doublejump", Features::GameplayMain::doublejump);
    SAVEKEY("chatbypass", Features::GameplayMain::chatbypass);
    SAVEKEY("jetpack", Features::GameplayMain::jetpack);
    SAVEKEY("xray", Features::GameplayMain::xray);
    SAVEKEY("emojispam", Features::GameplayMain::emojispam);
    SAVEKEY("quickscope", Features::GameplayWeapon::quickscope);
    SAVEKEY("maxdamage", Features::GameplayWeapon::maxdamage);
    SAVEKEY("lowdamage", Features::GameplayWeapon::lowdamage);
    SAVEKEY("multiplydamage", Features::GameplayWeapon::multiplydamage);
    SAVEKEY("damagemultiplier", Features::GameplayWeapon::damagemultiplier);
    SAVEKEY("chatspam", Features::GameplayTroll::chatspam);
    SAVEKEY("chatspamBuf", std::string(Features::GameplayTroll::chatspamBuf));
    SAVEKEY("masskill", Features::GameplayTroll::masskill);
    SAVEKEY("telekill", Features::GameplayTroll::telekill);
    SAVEKEY("middleclicktp", Features::GameplayTroll::middleclicktp);
    SAVEKEY("shootlaser", Features::GameplayBullet::shootlaser);
    SAVEKEY("shootrocket", Features::GameplayBullet::shootrocket);
    SAVEKEY("shootshotgun", Features::GameplayBullet::shootshotgun);
    SAVEKEY("shootdash", Features::GameplayBullet::shootdash);
    SAVEKEY("shootharpoon", Features::GameplayBullet::shootharpoon);
    SAVEKEY("shootexplodingbullet", Features::GameplayBullet::shootexplodingbullet);
    SAVEKEY("RickochetRocket", Features::GameplayBullet::RickochetRocket);
    SAVEKEY("stackingblindness", Features::GameplayEffects::stackingblindness);
    SAVEKEY("electricshock", Features::GameplayEffects::electricshock);
    SAVEKEY("charm", Features::GameplayEffects::charm);
    SAVEKEY("autoreloadws", Features::Settings::autoreloadws);
    SAVEKEY("adddlc", Features::Settings::adddlc);
    SAVEKEY("logws", Features::Settings::logwebsocket);
    SAVEKEY("freeclanupgrade", Features::Account::freeclanupgrade);
    SAVEKEY("espstartpoint", espStart[100]);
    SAVEKEY("nospread", Features::GameplayWeapon::nospread);
    SAVEKEY("ignoreshield", Features::GameplayBullet::ignoreshield);
    SAVEKEY("headmagnify", Features::GameplayMain::headmagnify);
    SAVEKEY("enemymarker", Features::GameplayMain::enemymarker);
    SAVEKEY("gadgetdisabler", Features::GameplayMain::gadgetdisabler);
    SAVEKEY("slowdown", Features::GameplayEffects::slowdown);
}

void config::LoadConfigs() {
    Features::GameplayAimbot::aimbot = LOADKEY("aimbot", Features::GameplayAimbot::aimbot);
    Features::GameplayAimbot::visibilitycheck = LOADKEY("visibilityCheck", Features::GameplayAimbot::visibilitycheck);
    Features::GameplayAimbot::leftclicktrigger = LOADKEY("leftclicktrigger", Features::GameplayAimbot::leftclicktrigger);
    Features::GameplayAimbot::triggerbot = LOADKEY("triggerbot", Features::GameplayAimbot::triggerbot);
    Features::GameplayAimbot::showfov = LOADKEY("showfov", Features::GameplayAimbot::showfov);
    Features::GameplayAimbot::colorchangingfov = LOADKEY("colorchangingfov", Features::GameplayAimbot::colorchangingfov);
    Features::GameplayAimbot::rgbfov = LOADKEY("rgbfov", Features::GameplayAimbot::rgbfov);
    Features::GameplayAimbot::customcolor = LOADKEY("customcolor", Features::GameplayAimbot::customcolor);
    Features::GameplayAimbot::smoothing = LOADKEY("smoothing", Features::GameplayAimbot::smoothing);
    aimatParts[100] = LOADKEY("aimatindex", aimatParts[100]);
    Features::GameplayAimbot::fovsize = LOADKEY("fovsize", Features::GameplayAimbot::fovsize);
    Features::GameplayESP::esp = LOADKEY("esp", false);
    Features::GameplayESP::espbone = LOADKEY("espbone", false);
    Features::GameplayESP::espline = LOADKEY("espline", true);
    Features::GameplayESP::espbox = LOADKEY("espbox", true);
    Features::GameplayESP::esp3dbox = LOADKEY("esp3dbox", false);
    Features::GameplayESP::esphealth = LOADKEY("esphealth", false);
    Features::GameplayESP::espdistance = LOADKEY("espdistance", false);
    Features::GameplayESP::teamcolor = LOADKEY("teamcolor", false);
    Features::GameplayESP::enemycolor = LOADKEY("enemycolor", false);
    Features::GameplayESP::showteam = LOADKEY("showteam", true);
    Features::GameplayESP::showenemy = LOADKEY("showenemy", true);
    Features::GameplayESP::esporigin = LOADKEY("esporigin", false);
    Features::GameplayESP::showping = LOADKEY("showping", false);
    Features::GameplayMain::killall = LOADKEY("killall", false);
    Features::GameplayMain::godmode = LOADKEY("godmode", false);
    Features::GameplayMain::friendlyfire = LOADKEY("friendlyfire", false);
    Features::GameplayMain::polymorph = LOADKEY("polymorph", false);
    Features::GameplayMain::silentaim = LOADKEY("silentaim", false);
    Features::GameplayMain::infammo = LOADKEY("infammo", false);
    Features::GameplayMain::killpoints = LOADKEY("killpoints", false);
    Features::GameplayMain::doublejump = LOADKEY("doublejump", false);
    Features::GameplayMain::chatbypass = LOADKEY("chatbypass", false);
    Features::GameplayMain::jetpack = LOADKEY("jetpack", false);
    Features::GameplayMain::xray = LOADKEY("xray", false);
    Features::GameplayMain::emojispam = LOADKEY("emojispam", false);
    Features::GameplayWeapon::quickscope = LOADKEY("quickscope", false);
    Features::GameplayWeapon::maxdamage = LOADKEY("maxdamage", false);
    Features::GameplayWeapon::lowdamage = LOADKEY("lowdamage", false);
    Features::GameplayWeapon::multiplydamage = LOADKEY("multiplydamage", false);
    Features::GameplayWeapon::damagemultiplier = LOADKEY("damagemultiplier", 2.0f);
    Features::GameplayTroll::chatspam = LOADKEY("chatspam", false);
    std::string chatspamBuf = LOADKEY("chatspamBuf", std::string("")); strncpy_s(Features::GameplayTroll::chatspamBuf, chatspamBuf.c_str(), sizeof(Features::GameplayTroll::chatspamBuf));
    Features::GameplayTroll::masskill = LOADKEY("masskill", false);
    Features::GameplayTroll::telekill = LOADKEY("telekill", false);
    Features::GameplayTroll::middleclicktp = LOADKEY("middleclicktp", false);
    Features::GameplayBullet::shootlaser = LOADKEY("shootlaser", false);
    Features::GameplayBullet::shootrocket = LOADKEY("shootrocket", false);
    Features::GameplayBullet::shootshotgun = LOADKEY("shootshotgun", false);
    Features::GameplayBullet::shootdash = LOADKEY("shootdash", false);
    Features::GameplayBullet::shootharpoon = LOADKEY("shootharpoon", false);
    Features::GameplayBullet::shootexplodingbullet = LOADKEY("shootexplodingbullet", false);
    Features::GameplayBullet::RickochetRocket = LOADKEY("RickochetRocket", false);
    Features::GameplayEffects::stackingblindness = LOADKEY("stackingblindness", false);
    Features::GameplayEffects::electricshock = LOADKEY("electricshock", false);
    Features::GameplayEffects::charm = LOADKEY("charm", false);
    Features::Settings::autoreloadws = LOADKEY("autoreloadws", false);
    Features::Settings::adddlc = LOADKEY("adddlc", false);
    Features::Settings::logwebsocket = LOADKEY("logws", true);
    Features::Account::freeclanupgrade = LOADKEY("freeclanupgrade", false);
    espStart[100] = LOADKEY("espstartpoint", 0);
    Features::GameplayWeapon::nospread = LOADKEY("nospread", false);
    Features::GameplayBullet::ignoreshield = LOADKEY("ignoreshield", false);
    Features::GameplayMain::headmagnify = LOADKEY("headmagnify", false);
    Features::GameplayMain::enemymarker = LOADKEY("enemymarker", false);
    Features::GameplayMain::gadgetdisabler = LOADKEY("gadgetdisabler", false);
    Features::GameplayEffects::slowdown = LOADKEY("slowdown", false);

    // others
    Variables::aimbotbind = LOADKEY("pressedKey", 0x70);
    Variables::menuToggleBind = LOADKEY("menuToggleKey", 0xA3);
}