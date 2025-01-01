#pragma once
#include <iostream>
#include <d3d11.h>
#include <vector>
#include "../imgui/imgui.h"

namespace Features {
    namespace GameplayMain {
        extern bool killall;
        extern bool godmode;
        extern bool friendlyfire;
        extern bool polymorph;
        extern bool silentaim;
        extern bool infammo;
        extern bool killpoints;
        extern bool doublejump;
        extern bool chatbypass;
        extern bool jetpack;
        extern bool xray;
        extern bool emojispam;
        extern bool headmagnify;
        extern bool enemymarker;
        extern bool gadgetdisabler;
    }
    namespace GameplayWeapon {
        extern bool quickscope;
        extern bool maxdamage;
        extern bool lowdamage;
        extern bool multiplydamage;
        extern float damagemultiplier;
        extern bool nospread;
    }
    namespace GameplayTroll {
        extern bool chatspam;
        extern char chatspamBuf[64];
        extern bool masskill;
        extern bool telekill;
        extern bool middleclicktp;
    }
    namespace GameplayBullet {
        extern bool shootlaser;
        extern bool shootrocket;
        extern bool shootshotgun;
        extern bool shootdash;
        extern bool shootharpoon;
        extern bool shootexplodingbullet;
        extern bool RickochetRocket;
        extern bool ignoreshield;
    }
    namespace GameplayEffects {
        extern bool stackingblindness;
        extern bool electricshock;
        extern bool charm;
        extern bool slowdown;
    }
    namespace GameplayAimbot {
        extern bool aimbot;
        extern bool visibilitycheck;
        extern bool leftclicktrigger;
        extern bool triggerbot;
        // fov
        extern bool showfov;
        extern bool colorchangingfov;
        extern bool rgbfov;
        extern bool customcolor;
        extern float fovaimbotcolor[4];
        extern float fovsize;
        // config
        extern bool smoothing;
        extern float smoothingamount;
        extern int aimatIndex;
        extern float timer;
        extern float speed;
    }
    namespace GameplayESP {
        extern bool esp;
        extern bool espbone;
        extern bool espline;
        extern bool espbox;
        extern bool esp3dbox;
        extern bool esphealth;
        extern bool espdistance;
        // configs
        extern bool teamcolor;
        extern bool enemycolor;
        extern bool showteam;
        extern bool showenemy;
        extern float espTeamColor[4];
        extern float espEnemyColor[4];
        // others
        extern bool esporigin;
        extern bool showping;
    }

    namespace Account {
        extern bool collectibles;
        extern bool expmultiplier;
        extern bool freeclanupgrade;
        extern int collectiblesMultiplier;
        extern int collectiblesLoop;
        extern int expmultiplierAmount;

        extern int currencyAmount;
        extern int maxCurSlider;
        extern bool isAddingCoins;
        extern bool isAddingGems;
        extern bool isAddingPPTickets;
        extern bool isAddingSilver;
        extern bool isAddingKeys;
        extern bool isAddingCoupons;
        extern bool isAddingNoviceChest;
        extern bool isAddingFighterChest;
        extern bool isAddingWinnerChest;
        extern bool isAddingClanSCPoints;

        extern bool isAddingArmor;
        extern bool isAddingHats;
        extern bool isAddingMasks;
        extern bool isAddingSkins;
        extern bool isAddingCapes;
        extern bool isAddingBoots;
        extern bool isAddingGadgets;
        extern bool isAddingPets;
        extern bool isAddingCars;
        extern bool isAddingGliders;
        extern bool isAddingLobbyItems;
        extern bool isAddingVeterenSet;
        extern bool isAddingUnknownSkin;
        extern bool isAddingIndividual;

        extern bool addCustomWepRange;
        extern int addWeaponStartRange;
        extern int addWeaponEndRange;
        extern bool addCustomWep;
        extern char addwepBuf[64];

        extern bool reloadws;
        extern bool addwepskins;
        extern bool addallmodules;
        extern bool upgradeallmodules;
        extern bool addboosters;
        extern bool addgrafiti;
        extern bool addallwepparts;
        extern bool adddlcweps;
        extern bool addallwear;
        extern bool addallgadgets;
        extern bool addallroyale;
        extern bool addallweapons;

        extern bool changenickname;
        extern bool addbadge;
        extern bool setlevel;
        extern bool windeathmatch;
        extern char changenamebuf[32];
        extern bool wsaddcurrency;
        extern int boostersAmount;
        extern bool bugclan;
        extern int wscurrencyamount;
        extern int setleveltarget;
        extern char clanidBuf[64];
        
        extern bool getslot;

        namespace SkinModder {
            extern bool addskin;
            extern char skinnameBuf[32];
            extern std::string skinpngpath;
            extern std::vector<std::string> skinfiles;
        }
    }

    namespace Settings {
        extern bool autoreloadws;
        extern bool adddlc;
        extern bool bruteforceitemrecord;
        extern bool logwebsocket;
    }
}

namespace Variables {
    extern bool versionCompatible;
    extern bool imguiinit;
    extern bool wepsoundshooked;
    extern bool pixeltimehooked;
    extern std::string accountID;
    extern std::string accountAuth;
    extern std::string asteroidVersion;
    extern int aimbotbind;
    extern std::string aimbotbindkey;
    extern int menuToggleBind;
    extern std::string menuToggleBindKey;
    extern bool listenforkeybind;
    extern bool listenforkeybindAimbot;
    extern bool listenforkeybindMenuToggle;
    extern bool openMenuYet;
    extern bool menuLoaded;
    extern int classesFound;
    extern int totalClasses;
    extern float dxwidth;
    extern float dxheight;
}

namespace Textures {
    extern int skin_imageWidth;
    extern int skin_imageHeight;
    extern ID3D11ShaderResourceView* skin_Texture;
}

// ImGui
enum Heads {
    Combat, Account, Misc, Settings
};

enum SubHeads {
    tab1, tab2, tab3, tab4, tab5, tab6
};

extern Heads Tab;
inline int Sliders[100];
inline SubHeads GameplaySubTab;
inline SubHeads AccountSubTab;
inline SubHeads MiscSubTab;
inline SubHeads SettingsSubTab;
extern int aimatParts[100];
extern const char* aimAtPartsItems[4];
extern int boosters[100];
extern const char* boosterscombo[5];
extern int espStart[100];
extern const char* espStartcombo[3];

extern int wscurrencytype[100];
extern const char* wscurrencyCombo[6];
extern const char* wscurrencyComboVisualName[6];
extern int selectedAdderTypeIndex;
extern int selectedItemIndex;
extern int wearTypeIndex;
extern int selectedSkinIndex;
extern int selectedPetIndex;
extern int selectedLobbyIndex;