#include "menufeatures.h"
/* GameplayMain */
bool Features::GameplayMain::killall = false;
bool Features::GameplayMain::godmode = false;
bool Features::GameplayMain::friendlyfire = false;
bool Features::GameplayMain::polymorph = false;
bool Features::GameplayMain::silentaim = false;
bool Features::GameplayMain::infammo = false;
bool Features::GameplayMain::killpoints = false;
bool Features::GameplayMain::doublejump = false;
bool Features::GameplayMain::chatbypass = false;
bool Features::GameplayMain::jetpack = false;
bool Features::GameplayMain::xray = false;
bool Features::GameplayMain::emojispam = false;
bool Features::GameplayMain::headmagnify = false;
bool Features::GameplayMain::enemymarker = false;
bool Features::GameplayMain::gadgetdisabler = false;


/* GameplayWeapon */
bool Features::GameplayWeapon::quickscope = false;
bool Features::GameplayWeapon::maxdamage = false;
bool Features::GameplayWeapon::lowdamage = false;
bool Features::GameplayWeapon::multiplydamage = false;
float Features::GameplayWeapon::damagemultiplier = 2.0f;
bool Features::GameplayWeapon::nospread = false;


/* GamePlayTroll */
bool Features::GameplayTroll::chatspam = false;
char Features::GameplayTroll::chatspamBuf[64] = "";
bool Features::GameplayTroll::masskill = false;
bool Features::GameplayTroll::telekill = false;
bool Features::GameplayTroll::middleclicktp = false;

/* GameplayBullet */
bool Features::GameplayBullet::shootlaser = false;
bool Features::GameplayBullet::shootrocket = false;
bool Features::GameplayBullet::shootshotgun = false;
bool Features::GameplayBullet::shootdash = false;
bool Features::GameplayBullet::shootharpoon = false;
bool Features::GameplayBullet::shootexplodingbullet = false;
bool Features::GameplayBullet::RickochetRocket = false;
bool Features::GameplayBullet::ignoreshield = false;

/* GamePlayEffects */
bool Features::GameplayEffects::stackingblindness = false;
bool Features::GameplayEffects::electricshock = false;
bool Features::GameplayEffects::charm = false;
bool Features::GameplayEffects::slowdown = false;

/* GameplayAimbot */
bool Features::GameplayAimbot::aimbot = false;
bool Features::GameplayAimbot::visibilitycheck = true;
bool Features::GameplayAimbot::leftclicktrigger = false;
bool Features::GameplayAimbot::triggerbot = false;
// fov
bool Features::GameplayAimbot::showfov = true; 
bool Features::GameplayAimbot::colorchangingfov = true;
bool Features::GameplayAimbot::rgbfov = false;
bool Features::GameplayAimbot::customcolor = false;
float Features::GameplayAimbot::fovaimbotcolor[4] = { 255 / 255.0, 255.0 / 255.0, 255.0 / 255.0, 1.0 };
float Features::GameplayAimbot::fovsize = 200.0f; 
//config
bool Features::GameplayAimbot::smoothing = false;
float Features::GameplayAimbot::smoothingamount = 0.9f;
int Features::GameplayAimbot::aimatIndex = 0;
float Features::GameplayAimbot::timer = 0.0f;
float Features::GameplayAimbot::speed = 2.5f;

/* GameplayESP */
bool Features::GameplayESP::esp = false;
bool Features::GameplayESP::espbone = false;
bool Features::GameplayESP::espline = true;
bool Features::GameplayESP::espbox = true;
bool Features::GameplayESP::esp3dbox = false;
bool Features::GameplayESP::esphealth = false;
bool Features::GameplayESP::espdistance = false;
//configs
bool Features::GameplayESP::teamcolor = false; 
bool Features::GameplayESP::enemycolor = false;
bool Features::GameplayESP::showteam = true;
bool Features::GameplayESP::showenemy = true;
float Features::GameplayESP::espTeamColor[4] = { 37.0 / 255.0, 144.0 / 255.0, 245.0 / 255.0, 1.0 };
float Features::GameplayESP::espEnemyColor[4] = { 245.0 / 255.0, 52.0 / 255.0, 27.0 / 255.0, 1.0 };
//others
bool Features::GameplayESP::esporigin = false; 
bool Features::GameplayESP::showping = false;

/* Account */
bool Features::Account::collectibles = false;
bool Features::Account::expmultiplier = false;
bool Features::Account::freeclanupgrade = false;
int Features::Account::collectiblesMultiplier = 2;
int Features::Account::collectiblesLoop = 10;
int Features::Account::expmultiplierAmount = 25;

int Features::Account::currencyAmount = 1500;
int Features::Account::maxCurSlider = 5000;
bool Features::Account::isAddingCoins = false;
bool Features::Account::isAddingGems = false;
bool Features::Account::isAddingPPTickets = false;
bool Features::Account::isAddingSilver = false;
bool Features::Account::isAddingKeys = false;
bool Features::Account::isAddingCoupons = false;
bool Features::Account::isAddingNoviceChest = false;
bool Features::Account::isAddingFighterChest = false;
bool Features::Account::isAddingWinnerChest = false;
bool Features::Account::isAddingClanSCPoints = false;

bool Features::Account::isAddingArmor = false;
bool Features::Account::isAddingHats = false;
bool Features::Account::isAddingMasks = false;
bool Features::Account::isAddingSkins = false;
bool Features::Account::isAddingCapes = false;
bool Features::Account::isAddingBoots = false;
bool Features::Account::isAddingGadgets = false;
bool Features::Account::isAddingPets = false;
bool Features::Account::isAddingCars = false;
bool Features::Account::isAddingGliders = false;
bool Features::Account::isAddingLobbyItems = false;
bool Features::Account::isAddingVeterenSet = false;
bool Features::Account::isAddingUnknownSkin = false;
bool Features::Account::isAddingIndividual = false;

bool Features::Account::addCustomWepRange = false;
int Features::Account::addWeaponStartRange = 0;
int Features::Account::addWeaponEndRange = 150;
bool Features::Account::addCustomWep = false;
char Features::Account::addwepBuf[64] = "ultimatum";

bool Features::Account::reloadws = false;
bool Features::Account::addwepskins = false;
bool Features::Account::addallmodules = false;
bool Features::Account::upgradeallmodules = false;
bool Features::Account::addboosters = false;
bool Features::Account::addgrafiti = false;
bool Features::Account::addallwepparts = false;
bool Features::Account::adddlcweps = false;
bool Features::Account::addallwear = false;
bool Features::Account::addallgadgets = false;
bool Features::Account::addallroyale = false;
bool Features::Account::addallweapons = false;

bool Features::Account::changenickname = false;
bool Features::Account::addbadge = false;
bool Features::Account::setlevel = false;
bool Features::Account::windeathmatch = false;
char Features::Account::changenamebuf[32] = "discord.gg/pg3d";
int Features::Account::boostersAmount = 10;
int Features::Account::wscurrencyamount = 5000;
int Features::Account::setleveltarget = 30;
bool Features::Account::bugclan = false;
bool Features::Account::wsaddcurrency = false;
char Features::Account::clanidBuf[64] = "123456789";

bool Features::Account::getslot = false;

bool Features::Account::SkinModder::addskin = false;
char Features::Account::SkinModder::skinnameBuf[32] = "skin";
std::string Features::Account::SkinModder::skinpngpath = "";
std::vector<std::string> Features::Account::SkinModder::skinfiles;

bool Features::Settings::autoreloadws = false;
bool Features::Settings::adddlc = false;
bool Features::Settings::bruteforceitemrecord = false;
bool Features::Settings::logwebsocket = false;

/* Menu variables */
bool Variables::versionCompatible = true;
bool Variables::imguiinit = false;
bool Variables::wepsoundshooked = false;
bool Variables::pixeltimehooked = false;
std::string Variables::accountID = "";
std::string Variables::accountAuth = "";
std::string Variables::asteroidVersion = "2.0";
int Variables::aimbotbind = 0x70;
std::string Variables::aimbotbindkey = "None";
int Variables::menuToggleBind = 0xA3;
std::string Variables::menuToggleBindKey = "None";
bool Variables::listenforkeybind = false;
bool Variables::listenforkeybindAimbot = false;
bool Variables::listenforkeybindMenuToggle = false;
bool Variables::openMenuYet = false;
bool Variables::menuLoaded = false;
int Variables::classesFound = 0;
int Variables::totalClasses = 14;
float Variables::dxwidth = 0.0f;
float Variables::dxheight = 0.0f;

int Textures::skin_imageHeight = 32;
int Textures::skin_imageWidth = 64;
ID3D11ShaderResourceView* Textures::skin_Texture = NULL;


const char* aimAtPartsItems[4] = { "Head", "Body", "Feet", "Random" };
int aimatParts[100] = { 0 };
const char *boosterscombo[] = { "None", "25% Booster", "50% Booster", "100% Booster", "200% Booster" };
Heads Tab{ Combat };
int boosters[100] = {0};

int espStart[100] = { 0 };
const char* espStartcombo[] = { "Middle", "Top", "Bottom" };

int wscurrencytype[100] = {};
const char *wscurrencyCombo[] = { "GemsCurrency", "Coins", "ClanSilver", "Coupons", "PixelPassCurrency", "keys_mirrored_lottery" };
const char* wscurrencyComboVisualName[] = { "Gems", "Coins", "Silver", "Coupons", "Pixel Pass Tickets", "Keys" };
int selectedAdderTypeIndex = 0;
int selectedItemIndex = 0;
int wearTypeIndex = 0;
int selectedSkinIndex = 0;
int selectedPetIndex = 0;
int selectedLobbyIndex = 0;