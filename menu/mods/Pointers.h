#pragma once


#include "Structs.h"
#include "utils.h"
#include "../ui/menufeatures.h"

namespace player_move_c {
	inline Pointer<void(void*, il2cppString*, bool, il2cppString*)> SendChat;
	inline Pointer<void*(void*)> get_BaseCamera;
	inline Pointer<void(void*, bool)> set_Jetpack;
	inline Pointer<void(void*, bool)> set_Xray;
	inline Pointer<float(void*)> get_Health;
	inline Pointer<void(void*, float)> set_Health;
	inline Pointer<bool(void*, Vector3)> isVisible;
	inline Pointer<void (void*, bool)> ShotPressed;
}
namespace PlayerDamageable {
	inline Pointer<bool(void*, void*)> isEnemyTo;
	inline Pointer<bool(void*)> isDead;
}
namespace BaseCamera {
	inline Pointer<void*(void*)> get_Camera;
}
namespace ItemRecord {
	inline Pointer<int (void*)> get_Index;
	inline Pointer<int (void*)> get_Rarity;
	inline Pointer<int (void*)> get_WeaponNumber;
	inline Pointer<il2cppString* (void*)> get_Tag;
	inline Pointer<il2cppString* (void*)> get_AlternativeName;
	inline Pointer<il2cppString* (void*)> get_shopName;
	inline Pointer<il2cppString* (void*)> ToString;
}
namespace ExperienceController {
	inline Pointer<int()> get_CurrentLevel;
	inline Pointer<int()> get_CurrentEXP;
}
namespace GadgetClass {
	inline Pointer<void(il2cppString*, int*)> addGadget;
}
namespace ProgressUpdater {
	inline Pointer<void*()> get_Instance;
	inline Pointer<void(void*, int, void*, int, il2cppString*, AnalyticsParams2)> addWeapon2;
	inline Pointer<void(void*, int*, int*, il2cppString*, AnalyticsParams2)> addArmor;
	inline Pointer<void(void*, il2cppString*, int, int, bool, bool, AnalyticsParams2)> addCurrency2;
	inline Pointer<void(void*, il2cppString*, int, int, spendCurStruct)> spendCurrency;
	inline Pointer<void(void*, int, int, int, int, AnalyticsParams2)> addChest;
	inline Pointer<void(void*, int, il2cppString*)> insertModule;
}
namespace WeaponManger {
	inline Pointer<void(void*, il2cppString*, int, bool, bool, void*, AnalyticsParams2)> addWeapon;
}

namespace BankController {
	inline Pointer<void (int amount, int source, bool arg1, int arg2)> addCoupons;
	inline Pointer<void (il2cppString*, int, bool, int, int, int, int)> addCurrency;
	inline Pointer<void (int, bool, int, il2cppString*, bool, int)> addKeys; // this one is actually used by the game
}
namespace InappBonusesController {
	inline Pointer<bool()> isInMatch;
	inline Pointer<void (il2cppString*, bool, bool)> AddWeapon;
	inline Pointer<void (il2cppString*, int*)> addPet;
	inline Pointer<void (il2cppString*)> addLobbyItem;
}
namespace PhotonNetwork {
	inline Pointer<int()> get_Ping;
}
namespace PlayerPrefs {
	inline Pointer<void (il2cppString*, int)> setInt;
	inline Pointer<void (il2cppString*, float)> setFloat;
	inline Pointer<int (il2cppString*, il2cppString*)> setString;
}
namespace Camera {
	inline Pointer<Vector3(void*, Vector3)> WorldToScreenPoint;
	inline Pointer<float(void*)> get_fov;
	inline Pointer<void (void*, float)> set_fov;
	inline Pointer<void* ()> get_main;
}
namespace Transform {
	inline Pointer<Vector3 (void*)> get_Position;
	inline Pointer<void (void*, Vector3)> set_Position;
	inline Pointer<Quaternion(void*)> get_rotation;
	inline Pointer<Vector3(void*, Vector3)> inverseTransformPoint;
	inline Pointer<void(void*, Quaternion)> set_rotation;
	inline Pointer<void(void*, float, float, float)> rotate;
	inline Pointer<Vector3 (void*)> get_localScale;
	inline Pointer<void (void*, Vector3)> set_localScale;
	inline Pointer<Vector3(void*)> get_forward;
}
namespace Component {
	inline Pointer<void* (void*)> get_Transform;
}
namespace Shader {
	inline Pointer<void* (il2cppString*)> Find;
}
namespace UInput {
	inline Pointer<bool (int)> GetMouseButtonDown;
}
namespace Physics {
	inline Pointer<bool(Vector3, Vector3, void*)> Raycast;
	inline Pointer<bool(Vector3, Vector3, RaycastHit)> LineCast;
}
namespace Object {
	inline Pointer<int (void*)> GetInstanceID;
}
namespace Collider {
	inline Pointer<U_Bounds (void*)> get_Bounds;
}

namespace Bounds {
	inline Pointer<Vector3(void*)> get_min;
	inline Pointer<Vector3(void*)> get_max;
}

namespace Application {
	inline Pointer<il2cppString* ()> get_Version;
}

namespace Renderer {
	inline Pointer<bool(void*)> isVisible;
	inline Pointer<monoArray<void**>* (void*)> get_bones;
}
namespace CharacterController {
	inline Pointer<void (void*, float)> set_radius;
	inline Pointer<int (void*, Vector3)> Move;
}
namespace Debug {
	inline Pointer<void(Vector3 start, Vector3 end, void* color, float duration)> DrawLine;
}

namespace Websocket {
	inline Pointer<int(void* wsmsi, il2cppString* event, void* dict)> send;
	inline Pointer<int(void *, il2cppString *)> sendCommand;
}
namespace Encoding {
	inline Pointer<il2cppString *(void *, void *)> GetString;
	inline Pointer<void *()> get_UTF8;
	inline Pointer<void *(void *, il2cppString *)> GetBytes;
}


inline Pointer<il2cppString* (void*)> serializeObject;
inline Pointer<void* (il2cppString*)> deserializeObject;
inline Pointer<void(il2cppString*)> LoadScene;
inline Pointer<float ()> get_DeltaTime;
inline Pointer<il2cppString*()> get_AccountID;
inline Pointer<void(il2cppString*)> set_AccountID;
inline Pointer<il2cppString*(void*)> get_AccountAuth;
inline Pointer<void*()> get_AuthInstance;
inline Pointer<void(void*, il2cppString*)> set_AuthSecret;
inline Pointer<void(void*, il2cppString*)> set_AuthInfo;
inline Pointer<void*(il2cppString*)> getItemRecord;
inline Pointer<void* (int)> getItemRecordFromIndex;
inline Pointer<int* (il2cppString* str)>ptrwearIndex; 
inline Pointer<void(int*, il2cppString*)> addWear;
inline Pointer<void (il2cppString*, bool*, AnalyticsParams2)> addRoyaleItem;
inline Pointer<void* (void*, void*, bool)> EncryptCommand; 

inline Pointer<void(void*)> U_StartNewGameClicked;
inline Pointer<il2cppString*(void*)> PacketToString;
inline Pointer<void*(il2cppString*)> dictionaryFromJson;

void loadObfuscatedClass();
void initPointers();

extern Unity::il2cppClass* klass_Player_move_c;
extern Unity::il2cppClass* klass_WebsocketManager;
extern Unity::il2cppClass* klass_ExperienceController;
extern Unity::il2cppClass* klass_GadgetClass;
extern Unity::il2cppClass* klass_ProgressUpdater;
extern Unity::il2cppClass* klass_BankController;
extern Unity::il2cppClass* klass_InappBonusesController;
extern Unity::il2cppClass* klass_AccountID;
extern Unity::il2cppClass* klass_AuthClass;
extern Unity::il2cppClass* klass_PhotonNetwork;
extern Unity::il2cppClass* klass_RecvClass;
extern Unity::il2cppClass* klass_filterChat;
extern Unity::il2cppClass* klass_expClass;
extern Unity::il2cppClass* klass_PlaceableItemSettings;
extern Unity::il2cppClass* klass_OItemRecord;
extern Unity::il2cppClass* klass_WearClass;
extern Unity::il2cppClass* klass_RoyaleClass;
extern Unity::il2cppClass* klass_EncryptCommand;
extern Unity::il2cppClass* klass_Encoding;

namespace Sigs {
	static SignatureCondition WSMSendC {"internal", "Int32", nullptr, {"String", "Dictionary`2"}};
	static SignatureCondition WSMSend2C {"internal", "Int32", nullptr, {"String"}};
	static SignatureCondition GetBaseCamC {"internal", "BaseCamera", nullptr, {}};
	static SignatureCondition SetJetpackC {"internal", "Void", nullptr, {"Boolean"}};
	static SignatureCondition SetXrayC {"private", "Void", nullptr, {"Boolean"}};
	static SignatureCondition GetHealthC {"internal", "Single", nullptr, {}};
	static SignatureCondition SetHealthC {"internal", "Void", nullptr, {"Single"}};
	static SignatureCondition IsVisibleC {"internal", "Boolean", nullptr, {"Vector3"}};
	static SignatureCondition ShotPressedC {"internal", "Void", nullptr, {}};
	static SignatureCondition CurrentLevelC {"internal static", "Int32", nullptr, {}};
	static SignatureCondition WSRecvC {"private", "Void", nullptr, {"Socket", "Packet", "Object[]"}};
	static SignatureCondition GetPartsC {"internal", "Int32", nullptr, {"Int32"}};
	static SignatureCondition PU_getInstanceC {"internal static", nullptr, nullptr, {}};
	static SignatureCondition PU_addWeaponC {"internal", "Void", nullptr, {"Int32", nullptr, "ENUM", "String", nullptr}};
	static SignatureCondition PU_addArmor {"internal", "Void", nullptr, {"Int32", "Int32", "String", nullptr}};
	static SignatureCondition PU_addGadget {"internal static", "Void", nullptr, {"String", "Int32"}};
	static SignatureCondition PU_addCurrency {"internal", "Void", nullptr, {"String", "Int32", "ENUM", "Boolean", "Boolean", nullptr}};
	static SignatureCondition PU_spendCurrency {"internal", "Boolean", nullptr, {"String", "Int32", "ENUM", nullptr}};
	static SignatureCondition PU_addChest {"internal", "Void", nullptr, {"Int32", "ENUM", "Int32", "ENUM", nullptr}};
	static SignatureCondition addkeys {"internal static", "Boolean", nullptr, {"Int32", "Boolean", "ENUM", "String", "Boolean", "ENUM"}};
	static SignatureCondition isInMatchC {"private static", "Boolean", nullptr, {}};
	static SignatureCondition addWeaponC {"internal static", "Void", nullptr, {"String", "Boolean", "Boolean"}};
	static SignatureCondition AddPetsC {"internal static", "Void", nullptr, {"String", "Int32"}};
	static SignatureCondition AddLobbyItemC {"internal static", "Void", nullptr, {"String"}};
	static SignatureCondition GetAccountIdC {"internal static", "String", nullptr, {}};
	static SignatureCondition SetAccountIdC {"internal static", "Void", nullptr, {"String"}};
	static SignatureCondition GetAuthC {"internal", "String", nullptr, {}};
	static SignatureCondition GetAuthInstanceC {"internal static", nullptr, nullptr, {}};
	static SignatureCondition SetAuthC {"internal", "Void", nullptr, {"String"}};
	static SignatureCondition SetAuthInfoC {"internal", "Void", nullptr, {"String"}};
	static SignatureCondition GetPingC {"public static", "Int32", nullptr, {}};
	static SignatureCondition RecvC {"public static", "Void", nullptr, {"String", "Dictionary`2", "Dictionary`2", "List`1"}};
	static SignatureCondition FilterChatMessageC {"internal static", "String", nullptr, {"String"}};
	static SignatureCondition IdkNiggaC {"internal", "Int32", nullptr, {"ENUM"}};
	static SignatureCondition IdkNigga2C {"internal", "Boolean", nullptr, {"ENUM"}};
	static SignatureCondition GetItemRecordC {"public static", "ItemRecord", nullptr, {"String"}};
	static SignatureCondition GetItemRecordFromIndexC {"internal static", "ItemRecord", nullptr, {"Int32"}};
	static SignatureCondition AddWearC {"internal static", "Void", nullptr, {"ENUM", "String"}};
	static SignatureCondition WearIndexC {"internal static", "Int32", nullptr, {"String"}};
	static SignatureCondition AddRoyaleC {"internal static", "Void", nullptr, {"String", "Boolean", nullptr}};
	static SignatureCondition EncryptCommandC {"public", "Byte[]", nullptr, {"Byte[]", "Boolean"}};
	static SignatureCondition EncGetStringC {"public virtual", "String", "GetString", {"Byte[]"}};
	static SignatureCondition EncGetUTF8C {"public static", "Encoding", "get_UTF8", {}};
	static SignatureCondition EncGetBytesC {"public virtual", "Byte[]", "GetBytes", {"String"}};

	static FieldPattern ProgressUpdaterPattern {"List`1", "List`1", "String", "String", "String", nullptr, "Int32", "Int32", "Int32", "Int32", "String", "String", "String", "String", "String", "String", "String", "Action", "Action", "Action", "Action", "Boolean", "Boolean", "String", "String", "Queue`1", "List`1", "List`1", "Dictionary`2", "Dictionary`2", nullptr, "String", "Boolean", "Int32", "String", "Boolean", "String", "Boolean", "String", "Action`1", "Action`1", "Dictionary`2", "List`1", "Dictionary`2", "Dictionary`2", "Int32", "Int32", "Int32", "Int32", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "Dictionary`2", "List`1", "List`1", "Int32", "Int32", "Dictionary`2", "List`1", "Coroutine", "UInt32"};
	static FieldPattern GadgetClass {"GadgetCategory", "Dictionary`2", "Dictionary`2", "Action`1"};
	static FieldPattern BankController {"Boolean", "Action`1", "Action`2", "Action`2", "Action`2", "Action`1", "Action`1", "Action"};
	static FieldPattern InappBonusesController {"String", "String", nullptr, "Action`1", "Int32", "String"};
	static FieldPattern AccountID {"String", "Int32", "String", "Boolean", "Boolean", "Nullable`1", "Boolean", "String", "String", "Action"};
	static FieldPattern AuthClass {"Int32", "Int32", "Int32", "Single", "Single", "Single", "Single", nullptr, "Coroutine", nullptr, "ValueTuple`2", "String", "String", nullptr, "Boolean", "Boolean", "String", "String", "Int32", "String", "HAuthTicket", "AuthorizationStates", "Coroutine", "Coroutine", "CancellationTokenSource", "Task`1", "String", "String", "Single", "String", "Boolean", "Boolean", nullptr, "Boolean", "Action", "Action", "Action", "Action", "Action", "Action`1", "Action", "Action"};
	static FieldPattern PhotonNetwork {"String", "String", "PhotonHandler", nullptr, "Int32", "Int32", "String", "ServerSettings", "Boolean", "PhotonLogLevel", "List`1", "Single", "Single", "Single", "Boolean", "Boolean", "Dictionary`2", "HashSet`1", "HashSet`1", "Type", "Boolean", "Boolean", nullptr, "Int32", "Boolean", "Boolean", "Int32", "Int32", "Boolean", nullptr, "Boolean", "Stopwatch", "Single", "Boolean", nullptr, "Int32", "Int32", "List`1"};
	static FieldPattern recvClass {"Dictionary`2"};
	static FieldPattern filterChatClass {"String", "String", "RegexOptions", "String[]", "String[]", "String[]", "String[]", "Boolean"};
	static FieldPattern expClass {"Int32", "String", "String", "String", "String", "String", nullptr, "List`1", "List`1", "Int32", "Boolean", "Int32"};
	static FieldPattern oitemRecord {"IEqualityComparer`1", "Int32", "String[]", "String[]", "Color[]", "List`1", "Dictionary`2", "Dictionary`2", "Dictionary`2", "HashSet`1", "Dictionary`2", nullptr, nullptr, nullptr, nullptr, "Dictionary`2", "WeakReference"};
	static FieldPattern WearClass {"String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "List`1", "HashSet`1", "List`1", "String", "String", "String", "String", "String", "List`1", "Dictionary`2", "Dictionary`2", "Dictionary`2", "Int32", "WearScriptableObject_GENERATED", "Action"};
	static FieldPattern RoyaleClass {"String", "String", "String", "String", "String", "String", "String", "String", "String", "RoyaleScriptableObject_GENERATED", "Action`1", "Action`1", "Action`1", "Action`1", "Action`1", "Dictionary`2"};
	static FieldPattern encryptCommandClass {"SymmetricAlgorithm"};
	static FieldPattern EncodingClass {"Encoding", "Encoding", "Encoding", "Encoding", "Encoding", "Encoding", "Encoding", "Encoding", "Dictionary`2", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "Int32", "CodePageDataItem", "Boolean", "Boolean", "EncoderFallback", "DecoderFallback", "Object"};
}