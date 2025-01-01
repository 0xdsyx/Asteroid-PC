#include "Pointers.h"

Unity::il2cppClass* klass_Player_move_c = nullptr;
Unity::il2cppClass* klass_WebsocketManager = nullptr;
Unity::il2cppClass* klass_ExperienceController = nullptr;
Unity::il2cppClass* klass_GadgetClass = nullptr;
Unity::il2cppClass* klass_ProgressUpdater = nullptr;
Unity::il2cppClass* klass_BankController = nullptr;
Unity::il2cppClass* klass_InappBonusesController = nullptr;
Unity::il2cppClass* klass_AccountID = nullptr;
Unity::il2cppClass* klass_AuthClass = nullptr;
Unity::il2cppClass* klass_PhotonNetwork = nullptr;
Unity::il2cppClass* klass_RecvClass = nullptr;
Unity::il2cppClass* klass_filterChat = nullptr;
Unity::il2cppClass* klass_expClass = nullptr;
Unity::il2cppClass* klass_PlaceableItemSettings = nullptr;
Unity::il2cppClass* klass_OItemRecord = nullptr;
Unity::il2cppClass* klass_WearClass = nullptr;
Unity::il2cppClass* klass_RoyaleClass = nullptr;
Unity::il2cppClass* klass_EncryptCommand = nullptr;
Unity::il2cppClass* klass_Encoding = nullptr;




void loadObfuscatedClass() {
    size_t m_sAssembliesCount = 0U;
    Unity::il2cppAssembly** m_pAssemblies = IL2CPP::Domain::GetAssemblies(&m_sAssembliesCount);

	for (size_t i = 0U; m_sAssembliesCount > i; ++i) {
	    Unity::il2cppAssembly* m_pAssembly = m_pAssemblies[i];
		const char* assemblyName = m_pAssembly->m_aName.m_pName;

		if (strcmp(assemblyName, OBF("Assembly-CSharp")) != 0) continue;
		for(int j = 0; j < IL2CPP::Class::Utils::ImageGetClassCount(m_pAssembly->m_pImage); j++) {
			Unity::il2cppClass* klass = IL2CPP::Class::Utils::ImageGetClass(m_pAssembly->m_pImage, j);
			Unity::il2cppType* type = IL2CPP::Class::GetType(klass);
			Unity::il2cppClass* typeklass = IL2CPP::Class::Utils::ClassFromType(type);
			if (NAMESPACE_CHECK(typeklass, OBF("Progress"))) {
				if (CheckContentCount(klass, {72, 100}, {471, 500}) && CheckFieldPattern(klass, Sigs::ProgressUpdaterPattern)) {
					klass_ProgressUpdater = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {4, 5}, {25, 30}) && CheckFieldPattern(klass, Sigs::GadgetClass)) {
					klass_GadgetClass = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {8, 10}, {41, 50}) && CheckFieldPattern(klass, Sigs::BankController)) {
					klass_BankController = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {6, 10}, {45, 50}) && CheckFieldPattern(klass, Sigs::InappBonusesController)) {
					klass_InappBonusesController = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {10, 15}, {10, 15}) && CheckFieldPattern(klass, Sigs::AccountID)) {
					klass_AccountID = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {42, 45}, {99, 105}) && CheckFieldPattern(klass, Sigs::AuthClass)) {
					klass_AuthClass = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {38, 40}, {148, 150}) && CheckFieldPattern(klass, Sigs::PhotonNetwork)) {
					klass_PhotonNetwork = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, OBF("Rilisoft.WebSocket"))) {
				if (CheckContentCount(klass, {1, 2}, {6, 7}) && CheckFieldPattern(klass, Sigs::recvClass)) {
					klass_RecvClass = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {8, 10}, {5, 6}) && CheckFieldPattern(klass, Sigs::filterChatClass)) {
					klass_filterChat = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, OBF("Rilisoft"))) {
				if (CheckContentCount(klass, {12, 15}, {23, 25}) && CheckFieldPattern(klass, Sigs::expClass)) {
					klass_expClass = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {17, 20}, {46, 50}) && CheckFieldPattern(klass, Sigs::oitemRecord)) {
					klass_OItemRecord = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {204, 210}, {65, 70}) && CheckFieldPattern(klass, Sigs::WearClass)) {
					klass_WearClass = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, "")) {
				if (CheckContentCount(klass, {16, 20}, {48, 50}) && CheckFieldPattern(klass, Sigs::RoyaleClass)) {
					klass_RoyaleClass = klass; Variables::classesFound++;
				}
			}
			if (NAMESPACE_CHECK(typeklass, OBF("Rilisoft"))) {
				if (CheckContentCount(klass, {1, 2}, {3, 5}) && CheckFieldPattern(klass, Sigs::encryptCommandClass)) {
					klass_EncryptCommand = klass; Variables::classesFound++;
				}
			}
		}
		

		/* if (strcmp(assemblyName, OBF("mscorlib")) == 0) {
			for(int j = 0; j < IL2CPP::Class::Utils::ImageGetClassCount(m_pAssembly->m_pImage); j++) {
				Unity::il2cppClass* klass = IL2CPP::Class::Utils::ImageGetClass(m_pAssembly->m_pImage, j);
				Unity::il2cppType* type = IL2CPP::Class::GetType(klass);
				Unity::il2cppClass* typeklass = IL2CPP::Class::Utils::ClassFromType(type);
				if (NAMESPACE_CHECK(typeklass, OBF("System.Text"))) {
					if (CheckContentCount(klass, {1, 2}, {3, 5}) && CheckFieldPattern(klass, Sigs::EncodingClass)) {
						klass_Encoding = klass; Variables::classesFound++;
					}
				}
			}
		} */
	}
	fslog::info(OBF("Found {}/{} classes, success: {}"), Variables::classesFound, Variables::totalClasses, Variables::classesFound == Variables::totalClasses);
}

#pragma region
void initPointers() {
	klass_Player_move_c = IL2CPP::Class::Find(OBF("Player_move_c"));
	klass_WebsocketManager = IL2CPP::Class::Find(OBF("Rilisoft.WebSocket.WebSocketManager"));
	klass_ExperienceController = IL2CPP::Class::Find(OBF("ExperienceController"));
	klass_PlaceableItemSettings = IL2CPP::Class::Find(OBF("PlaceableItemSettings"));

	Camera::WorldToScreenPoint = IL2CPP_METHOD_P("UnityEngine.Camera", "WorldToScreenPoint", 1); //	public Vector3 WorldToScreenPoint(Vector3 position) { }
	Camera::get_fov = IL2CPP_METHOD("UnityEngine.Camera", "get_fieldOfView");
	Camera::set_fov = IL2CPP_METHOD("UnityEngine.Camera", "set_fieldOfView");
	Camera::get_main = IL2CPP_METHOD("UnityEngine.Camera", "get_main");
	player_move_c::SendChat = IL2CPP_METHOD("Player_move_c", "SendChat");
	player_move_c::get_BaseCamera  = GetMethodPointerPattern(klass_Player_move_c, Sigs::GetBaseCamC); // internal BaseCamera .{9}\(\) \{ \}
	player_move_c::set_Jetpack = GetMethodPointerPattern(klass_Player_move_c, Sigs::SetJetpackC, 0x146); // few methods below internal Void .{9}\(.{9} .{9}, .{9} .{9}, EffectAdditionalOptions .{9}\) \{ \}
 	player_move_c::set_Xray = GetMethodPointerPattern(klass_Player_move_c, Sigs::SetXrayC, 0x17e);
	player_move_c::get_Health = OFFSET("0x1c1ac40"); // above private Void .{9}\(Single .{9}, Byte .{9}, Byte .{9}, Byte .{9}, Byte .{9}, Int32 .{9}, String .{9}\) \{ \}
	player_move_c::set_Health = OFFSET("0x1bd8200"); 
	player_move_c::isVisible = OFFSET("0x1c081f0"); // GetMethodPointerPattern(klass_Player_move_c, Sigs::IsVisibleC);  // internal Boolean .{1,9}\(Vector3 .{1,9}\) \{ \}
	player_move_c::ShotPressed = OFFSET("0x1bb3a10"); // GetMethodPointerPattern(klass_Player_move_c, Sigs::ShotPressedC, 0x369);
	PlayerDamageable::isEnemyTo = IL2CPP_METHOD("PlayerDamageable", "IsEnemyTo");
	PlayerDamageable::isDead = IL2CPP_METHOD("PlayerDamageable", "IsDead");
	BaseCamera::get_Camera = IL2CPP_METHOD("BaseCamera", "get_camera");
	ItemRecord::get_Index = IL2CPP_METHOD("ItemRecord", "get_Index");
	ItemRecord::get_Rarity = IL2CPP_METHOD("ItemRecord", "get_Rarity");
	ItemRecord::get_WeaponNumber = IL2CPP_METHOD("ItemRecord", "get_WeaponNumber");
	ItemRecord::get_Tag = IL2CPP_METHOD("ItemRecord", "get_Tag");
	ItemRecord::get_AlternativeName = IL2CPP_METHOD("ItemRecord", "get_AlternativeName");
	ItemRecord::get_shopName = IL2CPP_METHOD("ItemRecord", "get_shopName");
	ItemRecord::ToString = IL2CPP_METHOD("ItemRecord", "ToString");
	ExperienceController::get_CurrentLevel = GetMethodPointerPattern(klass_ExperienceController, Sigs::CurrentLevelC, 0x6); // method below LogError("RefreshExpControllers ExperienceController.sharedController == null");
	GadgetClass::addGadget = GetMethodPointerPattern(klass_GadgetClass, Sigs::PU_addGadget); // below internal static IEnumerable`1 .{9}\(Int32 .{9}\) \{ \}
	ProgressUpdater::get_Instance = GetMethodPointerPattern(klass_ProgressUpdater, Sigs::PU_getInstanceC, 0x58);
	ProgressUpdater::addWeapon2 = GetMethodPointerPattern(klass_ProgressUpdater, Sigs::PU_addWeaponC); // internal Void .{9}\(Int32 .{9}, .{9} .{9}, .{9} .{9}, String .{9}, .{9} .{9}\) \{ \}
	ProgressUpdater::addArmor = GetMethodPointerPattern(klass_ProgressUpdater, Sigs::PU_addArmor); // internal Void .{9}\(Int32 .{9}, Int32 .{9}, String .{9}, .{9} .{9}\) \{ \}
	ProgressUpdater::addCurrency2 = GetMethodPointerPattern(klass_ProgressUpdater, Sigs::PU_addCurrency); // internal Void .{9}\(String .{9}, Int32 .{9}, .{9} .{9}, Boolean .{9}, Boolean .{9}, .{9} .{9}\) \{ \}
	ProgressUpdater::spendCurrency = GetMethodPointerPattern(klass_ProgressUpdater, Sigs::PU_spendCurrency);
	ProgressUpdater::addChest = GetMethodPointerPattern(klass_ProgressUpdater, Sigs::PU_addChest); // internal Void .{9}\(Int32 .{9}, .{9} .{9}, Int32 .{9}, .{9} .{9}, .{9} .{9}\) \{ \}
	BankController::addKeys = GetMethodPointerPattern(klass_BankController, Sigs::addkeys); // internal static Boolean .{9}\(Int32 .{9}, Boolean .{9}, .{9} .{9}, String .{9}, Boolean .{9}, .{9} .{9}\) \{ \}
	InappBonusesController::isInMatch = GetMethodPointerPattern(klass_InappBonusesController, Sigs::isInMatchC); // bool below internal static Boolean .{9}\(List`1 .{9}, List`1 .{9}\) \{ \}
	InappBonusesController::AddWeapon = GetMethodPointerPattern(klass_InappBonusesController, Sigs::addWeaponC); // internal static Void .{9}\(String .{9}, Boolean .{9}, Boolean .{9}\) \{ \}
	InappBonusesController::addPet = GetMethodPointerPattern(klass_InappBonusesController, Sigs::AddPetsC); // Exception in GiveBonusForInapp giving pet: {0}
	InappBonusesController::addLobbyItem = GetMethodPointerPattern(klass_InappBonusesController, Sigs::AddLobbyItemC, 0x8); // 1 method above give weapon
	PhotonNetwork::get_Ping = GetMethodPointerPattern(klass_PhotonNetwork, Sigs::GetPingC, 0x74); // below public static GameObject .{9}\(String .{9}, Vector3 .{9}, Quaternion .{9}, Byte .{9}, Object\[\] .{9}\) \{ \}
	PlayerPrefs::setInt = IL2CPP_METHOD("UnityEngine.PlayerPrefs", "SetInt");
	PlayerPrefs::setFloat = IL2CPP_METHOD("UnityEngine.PlayerPrefs", "SetFloat");
	PlayerPrefs::setString = IL2CPP_METHOD("UnityEngine.PlayerPrefs", "SetString");
	Transform::get_Position = IL2CPP_METHOD("UnityEngine.Transform", "get_position");
	Transform::set_Position = IL2CPP_METHOD("UnityEngine.Transform", "set_position");
	Transform::get_rotation = IL2CPP_METHOD("UnityEngine.Transform", "get_rotation");
	Transform::set_rotation = IL2CPP_METHOD("UnityEngine.Transform", "set_rotation");
	Transform::rotate = IL2CPP_METHOD_P("UnityEngine.Transform", "Rotate", 3);
	Transform::get_localScale = IL2CPP_METHOD("UnityEngine.Transform", "get_localScale");
	Transform::set_localScale = IL2CPP_METHOD("UnityEngine.Transform", "set_localScale");
	Transform::inverseTransformPoint = IL2CPP_METHOD("UnityEngine.Transform", "InverseTransformPoint");
	Transform::get_forward = IL2CPP_METHOD("UnityEngine.Transform", "get_forward");
	Component::get_Transform = IL2CPP_METHOD("UnityEngine.Component", "get_transform");
	Shader::Find = IL2CPP_METHOD("UnityEngine.Shader", "Find");
	UInput::GetMouseButtonDown = IL2CPP_METHOD("UnityEngine.Input", "GetMouseButtonDown");
	Physics::Raycast = IL2CPP_METHOD_P("UnityEngine.Physics", "Raycast", 3); // public static Boolean Raycast(Vector3 origin, Vector3 direction, out RaycastHit hitInfo) { }
	Object::GetInstanceID = IL2CPP_METHOD("UnityEngine.Object", "GetInstanceID");
	Collider::get_Bounds = IL2CPP_METHOD("UnityEngine.Collider", "get_bounds");
	Bounds::get_min = IL2CPP_METHOD("UnityEngine.Bounds", "get_min");
	Bounds::get_max = IL2CPP_METHOD("UnityEngine.Bounds", "get_max");
	CharacterController::set_radius = IL2CPP_METHOD("UnityEngine.CharacterController", "set_radius");
	CharacterController::Move = IL2CPP_METHOD("UnityEngine.CharacterController", "Move");
	Renderer::get_bones = IL2CPP_METHOD("UnityEngine.SkinnedMeshRenderer", "get_bones");
	Renderer::get_bones = IL2CPP_METHOD("UnityEngine.SkinnedMeshRenderer", "get_bones");
	Websocket::send = GetMethodPointerPattern(klass_WebsocketManager, Sigs::WSMSendC); // OFFSET("0xed93c0");
	Websocket::sendCommand = GetMethodPointerPattern(klass_WebsocketManager, Sigs::WSMSend2C); // OFFSET("0xed9490");
	// Encoding::GetString = GetMethodPointerPattern(klass_Encoding, Sigs::EncGetStringC);
	// Encoding::get_UTF8 = GetMethodPointerPattern(klass_Encoding, Sigs::EncGetUTF8C);
	// Encoding::GetBytes = GetMethodPointerPattern(klass_Encoding, Sigs::EncGetBytesC);
	
	// Others
	serializeObject = IL2CPP_METHOD("Newtonsoft.Json.JsonConvert", "SerializeObject");
	deserializeObject = IL2CPP_METHOD("Newtonsoft.Json.JsonConvert", "DeserializeObject");
	LoadScene = IL2CPP_METHOD("UnityEngine.SceneManagement.SceneManager", "LoadScene");
	get_DeltaTime = IL2CPP_METHOD("UnityEngine.Time", "get_deltaTime");
	get_AccountID = GetMethodPointerPattern(klass_AccountID, Sigs::GetAccountIdC, 0x2); // search AccountCreated in the dark green class
	set_AccountID = GetMethodPointerPattern(klass_AccountID, Sigs::SetAccountIdC); // AccountCreated
	get_AccountAuth = GetMethodPointerPattern(klass_AuthClass, Sigs::GetAuthC, 0x9); // OFFSET("0x1ce7450"); // above private Void .{9}\(HAuthTicket .{9}\) \{ \}
	get_AuthInstance = GetMethodPointerPattern(klass_AuthClass, Sigs::GetAuthInstanceC);
	set_AuthSecret = GetMethodPointerPattern(klass_AuthClass, Sigs::SetAuthC, 0xa); // OFFSET("0x1ce9850"); // terceShtuA
	set_AuthInfo = GetMethodPointerPattern(klass_AuthClass, Sigs::SetAuthInfoC, 0x8); // method above the method above
	getItemRecord = GetMethodPointerPattern(klass_OItemRecord, Sigs::GetItemRecordC, 0xe);
	getItemRecordFromIndex = GetMethodPointerPattern(klass_OItemRecord, Sigs::GetItemRecordFromIndexC, 0x7);
	ptrwearIndex = GetMethodPointerPattern(klass_WearClass, Sigs::WearIndexC, 0xf); // method below "ScriptableObjects/Wear_GENERATED"
	addWear = GetMethodPointerPattern(klass_WearClass, Sigs::AddWearC);
	addRoyaleItem = GetMethodPointerPattern(klass_RoyaleClass, Sigs::AddRoyaleC); // RoyaleCustomiza_tionItemsManager Provid_eItem {0}
	Application::get_Version = IL2CPP_METHOD("UnityEngine.Application", "get_version");
	EncryptCommand = GetMethodPointerPattern(klass_EncryptCommand, Sigs::EncryptCommandC);

	U_StartNewGameClicked = IL2CPP_METHOD("PGCompany.AuthorizationScene.AccountBlockedWindow", "U_StartNewGameClicked");
	PacketToString = IL2CPP_METHOD("BestHTTP.SocketIO.Packet", "ToString");
	dictionaryFromJson = IL2CPP_METHOD("Prime31.JsonExtensions", "dictionaryFromJson");
}