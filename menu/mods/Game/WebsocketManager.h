#pragma once
#include <iostream>
#include <sstream>
#include "json.h"
#include "utils.h"

#include "../List.h"
#include "../menu/ui/menufeatures.h"
#include "../Pointers.h"
#include "../../defs.h"
#include "../../../imgui/ImGuiNotify.h"

using json = nlohmann::json;

class WebsocketManager {
public:
	WebsocketManager(void* wsmi);
    
	void reloadws();
    void _reloadws();
	void add_wepskins(int index); // 0 for all
	void add_modules(int index, int amount = 2500);
    void upgrade_modules(int index);
	void add_all_weps(int level);
	void change_nickname(const std::string& nickname);
	void add_badge();
    void add_boosters(int amount, int index);
    void add_grafitis(int index);
    void add_currency(int amount, const std::string &_type, const std::string &cause);
    void report_player(int id);
    json get_progress(int uniq_id, std::vector<int> slots = {});
    json fetch_slot(int slot);
    void set_level(int level);
    void win_deathmatch();
    void add_parts(int index, int amount, int item_records);
    void add_weapons_ranged(int startIndex, int endIndex, int level);
    void add_weapon(int index, int level);
    void bug_clan(const std::string &ClanID, int index, int amount);
    void add_dlcweps(int level);
    void add_armor(int index, int level);
    void add_all_wear(int level);
    void add_gadget(int index, int level);
    void add_all_royale();
    void add_skin(const std::string& name, const std::string& base64);

    void setversion(std::string version);
    void set_playerid(std::string id);
	void* get_wsmi();
private:
	void* wsmi;
	std::string version;
    int playerid;
	int playerlevel;
	std::string rand_hex();
	int SendWebsocket(il2cppString* event, void* dict, std::function<void(json &)> callback = nullptr);
    int SendWebsocket2(const json& request, std::function<void(json &)> callback = nullptr);
    int callWebsocket(const json &request, std::function<void(json &)> callback = nullptr);
	void* dict_from_json(json payload);
    json createCommand(std::string cmdID, json payload, std::vector<int> u = {140, 6});
    
};

extern std::unordered_map<int, std::unique_ptr<json>> command_params;
const static std::unordered_map<std::string, int> commandIDs{
    {OBF("None"), 0},
    {OBF("SetNick"), 1},
    {OBF("AddRating"), 2},
    {OBF("SetLeagueInTournament"), 3},
    {OBF("AddCurrency"), 10},
    {OBF("GetGemOrCoinInCompany"), 11},
    {OBF("ShowComicsInCompany"), 13},
    {OBF("CompleteLevelInCompany"), 14},
    {OBF("UpdateAchivements"), 15},
    {OBF("ShowComicsInBox"), 16},
    {OBF("AddOrUpgradePet"), 17},
    {OBF("AddEgg"), 18},
    {OBF("EggHatched"), 19},
    {OBF("UpdateLobbyItems"), 20},
    {OBF("RemoveLobbyItem"), 21},
    {OBF("UpdateLobbyItemAndRewardExperience"), 22},
    {OBF("UpdateBestScore"), 23},
    {OBF("MergeCampaingSlot"), 24},
    {OBF("UpdatePlayerEquipment"), 25},
    {OBF("UpdateBool"), 26},
    {OBF("UpdateSkinList"), 27},
    {OBF("UpdateBattleRoyaleList"), 28},
    {OBF("UpdateCustomSkin"), 29},
    {OBF("DeleteCustomSkin"), 30},
    {OBF("AddPurchasedWear"), 31},
    {OBF("StartUpArmor"), 32},
    {OBF("AddPurhasedGadget"), 33},
    {OBF("SetTutorialStage"), 35},
    {OBF("PurchaseWeaponSkin"), 36},
    {OBF("GameEvents_Spin"), 38},
    {OBF("GameEvents_FreeSpin"), 39},
    {OBF("GameEvents_UpdateFreeSpin"), 40},
    {OBF("GameEvents_UpdateCurreny"), 41},
    {OBF("GameEvents_RemoveCurreny"), 42},
    {OBF("GameEvents_RemoveGameEvent"), 43},
    {OBF("GameEvents_SetDurtyChest"), 44},
    {OBF("BattlePassInitSeason"), 50},
    {OBF("BattlePassGiveDailyExp"), 51},
    {OBF("BattlePassBuyPaymentStatus"), 52},
    {OBF("BattlePassTutorialChangeState"), 53},
    {OBF("BattlePassChangeInfo"), 54},
    {OBF("BattlePassCompleteSeason"), 55},
    {OBF("BattlePassChangeChallengesProgress"), 56},
    {OBF("BattlePassBannerEndViewed"), 57},
    {OBF("BattlePassBuyLevel"), 58},
    {OBF("UpdateConfig"), 60},
    {OBF("UpdateProgress"), 61},
    {OBF("UpdateRewards"), 62},
    {OBF("Snapshot"), 63},
    {OBF("UpdateLevel"), 64},
    {OBF("UpdateExperience"), 65},
    {OBF("SpendCurrency"), 66},
    {OBF("UpdateUtilityDictionaryValue"), 67},
    {OBF("UpdateUtilityIds"), 68},
    {OBF("UpdateWeaponsGotInCampaing"), 69},
    {OBF("GatchaGifts_UpdateFreeSpin"), 71},
    {OBF("GatchaGifts_UpdateGiftIndex"), 72},
    {OBF("GatchaGifts_UpdateSpinStep"), 73},
    {OBF("GatchaGifts_UpdateCachedState"), 74},
    {OBF("GatchaGifts_UpdateGiftList"), 75},
    {OBF("GatchaGifts_UpdateGiftTime"), 76},
    {OBF("GatchaGifts_UpdateConfigVersion"), 77},
    {OBF("InventoryAddItemExpiryOnServer"), 78},
    {OBF("InventoryAddItemExpiry"), 79},
    {OBF("InventoryAddItemConsumable"), 80},
    {OBF("InventoryRemoveItemConsumable"), 81},
    {OBF("InventoryAddItemUnique"), 82},
    {OBF("InventoryRemoveItemUnique"), 83},
    {OBF("InventoryAddItemSingle"), 84},
    {OBF("InventoryRemoveItemSingle"), 85},
    {OBF("InventoryRemoveItemExpiry"), 86},
    {OBF("ModuleInfoIncreaseUp"), 87},
    {OBF("ModuleStorageAddModule"), 88},
    {OBF("ModuleStorageRemoveModule"), 89},
    {OBF("AddWeapon"), 100},
    {OBF("StartUpgradingWeapon"), 101},
    {OBF("FinishUpgradingWeapon"), 102},
    {OBF("StartCraftItem"), 103},
    {OBF("FinishCraftItem"), 104},
    {OBF("UpdateFirstUps"), 105},
    {OBF("EmptyCommand"), 106},
    {OBF("AddTryGun"), 110},
    {OBF("DecreaseTryGunMatchesCount"), 111},
    {OBF("AddTryGunOffer"), 112},
    {OBF("UpdateTryGunTime"), 113},
    {OBF("RemoveTryGunOffer"), 114},
    {OBF("RemoveTryGun"), 115},
    {OBF("EquipWeaponSkin"), 116},
    {OBF("UpdateLobbyItemTimer"), 117},
    {OBF("UpdateEgg"), 118},
    {OBF("AddDetails"), 120},
    {OBF("UpdateBRVehicle"), 130},
    {OBF("UpdateUpgradingBRVehicle"), 131},
    {OBF("AddWeaponV17"), 132},
    {OBF("AddTryGunV17"), 133},
    {OBF("RemoveTryGunV17"), 134},
    {OBF("AddTryGunOfferV17"), 135},
    {OBF("RemoveTryGunOfferV17"), 136},
    {OBF("DecreaseTryGunMatchesCountV17"), 137},
    {OBF("UpdateTryGunTimeV17"), 138},
    {OBF("UpdateFirstUpsV17"), 139},
    {OBF("Offers_ResetSeason"), 141},
    {OBF("ChangeRank"), 142},
    {OBF("EquipWeaponSkinV2"), 143},
    {OBF("UnequipWeaponSkinV2"), 144},
    {OBF("AddTryGunBuffV17"), 145},
    {OBF("GameTaskChangeProgress"), 150},
    {OBF("GameTaskCompleted"), 151},
    {OBF("GameTaskRewarded"), 152},
    {OBF("GameTaskChangeInfoInBattle"), 153},
    {OBF("GameTaskReset"), 154},
    {OBF("GameTaskResetAllTasks"), 155},
    {OBF("Almanach_SetRewarded_Weapons"), 160},
    {OBF("Almanach_SetRewarded_WeaponSets"), 161},
    {OBF("Almanach_SetRewarded_CollectWeaponsSteps"), 162},
    {OBF("Almanach_SetCount_CollectWeaponsStep"), 163},
    {OBF("ValidateInApp"), 164},
    {OBF("AddGiftInSlot"), 165},
    {OBF("UnpackGift"), 166},
    {OBF("RemoveGiftFromSlot"), 167},
    {OBF("ReplaceGiftsInSlot"), 168},
    {OBF("Offers_AddOrUpdateOffer"), 169},
    {OBF("Offers_RemoveOffer"), 170},
    {OBF("Offers_ResetOffers"), 171},
    {OBF("Offers_UpdateOffersModule"), 172},
    {OBF("Offers_ResetOffersModule"), 173},
    {OBF("AddClanItems"), 174},
    {OBF("RemoveClanItems"), 175},
    {OBF("ReplaceClanItems"), 176},
    {OBF("ClanWarSetClanWarSeasonId"), 177},
    {OBF("ClanWarAddRewardedCaptureCellKey"), 178},
    {OBF("CheckSubscriptionOnGiveReward"), 179},
    {OBF("UpdateClanLevel"), 180},
    {OBF("UpdateClanExperience"), 181},
    {OBF("CreateClanItems"), 182},
    {OBF("AddFinishingClanItemUpgrade"), 184},
    {OBF("RemoveFinishingClanItemUpgrade"), 185},
    {OBF("ClanWarRewardedKeysMigration"), 186},
    {OBF("AddMailBoxRewardRecord"), 187},
    {OBF("RemoveMailBoxRewardRecord"), 188},
    {OBF("ClanWarSetGoblinCollectSilverAndShields"), 189},
    {OBF("UpdateClanLevelAndExperience"), 190},
    {OBF("BuyArmor"), 191},
    {OBF("CompleteCommonMatch"), 192},
    {OBF("CompleteBRDGMatch"), 193},
    {OBF("BlackMarketReset"), 194},
    {OBF("BlackMarketOpenCell"), 195},
    {OBF("BlackMarketUpdateCells"), 196},
    {OBF("EquipArmorSkin"), 197},
    {OBF("UnequipArmorSkin"), 198},
    {OBF("BlackMarketFirstSetClanWarSeasonId"), 199},
    {OBF("RemoveLegacyArmors"), 200},
    {OBF("ClanStorePromotionSetLastGenerateIndex"), 201},
    {OBF("ClanStorePromotionSetLastDollarPrice"), 202},
    {OBF("ClanStorePromotionReInit"), 203},
    {OBF("ClanStorePromotionSave"), 204},
    {OBF("ClanStorePromotionClear"), 205},
    {OBF("ClanBuildingsAddItems"), 206},
    {OBF("ClanBuildingsUpgradeBuilding"), 207},
    {OBF("ClanStorePromotionSendGenerateData"), 208},
    {OBF("BlackMarketUpdateRefreshCounter"), 211},
    {OBF("ClanGovernorSaveTask"), 212},
    {OBF("ClanGovernorResetCell"), 213},
    {OBF("ClanGovernorOpenCell"), 214},
    {OBF("ClanGovernorGiveCellReward"), 215},
    {OBF("ClanGovernorSetRefreshCountByVideo"), 216},
    {OBF("ClanGovernorSetRefreshCountByPrice"), 217},
    {OBF("ClanGovernorSelectBuilding"), 218},
    {OBF("ClanGovernorSetBuildingPoints"), 219},
    {OBF("ClanGovernorResetSlot"), 220},
    {OBF("AddTryGunAdCell"), 221},
    {OBF("RemoveTryGunAdCell"), 222},
    {OBF("AdsGunSetSeason"), 223},
    {OBF("AdsGunResetCells"), 224},
    {OBF("AdsGunIncrementAds"), 225},
    {OBF("AdsGunCollectTryGun"), 226},
    {OBF("AdsGunEndTryGun"), 227},
    {OBF("AdsGunSetAsShown"), 228},
    {OBF("AddPetV3"), 229},
    {OBF("UpgradePetV3"), 230},
    {OBF("RenamePetV3"), 231},
    {OBF("AddPetCardsV3"), 232},
    {OBF("RemovePetCardsV3"), 233},
    {OBF("GameModeTapReward_SetRewardTime"), 234},
    {OBF("ConnectSceneChestSetCountOpenedSmallChest"), 235},
    {OBF("ConnectSceneChestSetCountAlgorithmAttempt"), 236},
    {OBF("ConnectSceneChestSetAlgorithmWeights"), 237},
    {OBF("ConnectSceneChestSetIsInitAvailableKeys"), 238},
    {OBF("ConnectSceneChestSetAvailableKeys"), 239},
    {OBF("ConnectSceneChestSetRefreshKeyStartTime"), 240},
    {OBF("ConnectSceneChestSaveSpendKeys"), 241},
    {OBF("AddEggV3"), 242},
    {OBF("RemoveEggV3"), 243},
    {OBF("StartEggV3"), 244},
    {OBF("SpeedUpEggV3"), 245},
    {OBF("UpdateRankV2"), 246},
    {OBF("UpdateTrophyRoadLevel"), 247},
    {OBF("TrophyRoadGiveReward"), 248},
    {OBF("TrophyRoadStartSeason"), 249},
    {OBF("TrophyRoadEndSeason"), 250},
    {OBF("TrophyRoadMarkEndSeason"), 251},
    {OBF("TrophyRoadDevEndSeason"), 252},
    {OBF("TutorialComplete"), 253},
    {OBF("SaveMatchInHistory"), 254},
    {OBF("UpdateCupsForMatchHistory"), 255},
    {OBF("UpdateCupsForPlayersMatchHistory"), 256},
    {OBF("ConstructableOffersSaveGeneratedOffers"), 257},
    {OBF("ConstructableOffersSelectItemInCell"), 258},
    {OBF("ConstructableOffersIncrementPurchasedCount"), 259},
    {OBF("MarkWeaponSkinDiscovered"), 260},
    {OBF("Marathon"), 261},
    {OBF("GameEventDropChanceSetEventUniqueId"), 262},
    {OBF("GameEventDropChanceSetEventFirstInit"), 263},
    {OBF("GameEventDropChanceAddInappPrice"), 264},
    {OBF("GameEventDropChanceClearInappPrice"), 265},
    {OBF("GameEventDropChanceSetChances"), 266},
    {OBF("SetSecretPickedUp"), 267},
    {OBF("PiggyUpdateLevel_OLD"), 268},
    {OBF("PiggyUpdateSeason_OLD"), 269},
    {OBF("PiggyViewBanner_OLD"), 270},
    {OBF("PiggyBuyPromotion_OLD"), 271},
    {OBF("PiggyUpdateLevelView_OLD"), 272},
    {OBF("ManualOffersUpdateSlot"), 273},
    {OBF("ManualOffersBuyPromotion"), 274},
    {OBF("ManualOffersViewBanner"), 275},
    {OBF("DoubleOffersGenerateOffers"), 276},
    {OBF("DoubleOffersSetIsBought"), 277},
    {OBF("DoubleOffersSetStartTime"), 278},
    {OBF("DoubleOffersSetLastShowTime"), 279},
    {OBF("Vip20UpdatePaymentType"), 280},
    {OBF("Vip20BuyPromotion"), 281},
    {OBF("Vip20UpdateState"), 282},
    {OBF("Vip20ViewOverBanner"), 283},
    {OBF("ConstructableOffersViewBanner"), 284},
    {OBF("ManualOffersPresentationViewBanner"), 285},
    {OBF("ConstructableOffersViewPresentationBanner"), 286},
    {OBF("SetCurrentLoadoutNumber"), 287},
    {OBF("WriteUpdateLoadout"), 288},
    {OBF("Vip20CompleteMigration"), 289},
    {OBF("DoubleOffersRegenerateItems"), 290},
    {OBF("GachaNoviceGiftSetItemIndex"), 291},
    {OBF("GachaNoviceGiftCollectItem"), 292},
    {OBF("GachaNoviceGiftSetWasShow"), 293},
    {OBF("GachaNoviceGiftIncrementCountBattle"), 294},
    {OBF("GachaNoviceGiftCompleteTutorial"), 295},
    {OBF("PiggyStartSeason"), 296},
    {OBF("PiggyCompleteSeason_OLD_V2"), 297},
    {OBF("PiggyFakeCompleteSeason"), 298},
    {OBF("PiggyGiveRewards"), 299},
    {OBF("PiggyBuyPromotion"), 300},
    {OBF("PiggyUpdateLevel"), 301},
    {OBF("PiggyViewBanner"), 302},
    {OBF("PiggyUpdateLevelView"), 303},
    {OBF("NoviceDoubleOffersOpen"), 304},
    {OBF("NoviceDoubleOffersStart"), 305},
    {OBF("NoviceDoubleOffersShow"), 306},
    {OBF("NoviceDoubleOffersPurchase"), 307},
    {OBF("ProgressRoadUpdateRewardsProgress"), 308},
    {OBF("PiggyCompleteSeasonV3"), 309},
    {OBF("AttributeChange"), 310},
    {OBF("ProgressRoadUpdateStateMigration"), 311},
    {OBF("ProgressRoadSetTakenRewards"), 312},
    {OBF("UniversalPromotionStartPromotion"), 313},
    {OBF("UniversalPromotionSetGroupStartCounter"), 314},
    {OBF("UniversalPromotionSetGroupCooldownStartTime"), 315},
    {OBF("UniversalPromotionBuyPromotion"), 316},
    {OBF("UniversalPromotionStopPromotion"), 317},
    {OBF("UniversalPromotionSetPromotionLastBannerView"), 318},
    {OBF("UniversalPromotionGenerate"), 319},
    {OBF("GameModeHubTapRewardsSet"), 320},
    {OBF("ShopSetBuyTime"), 321},
    {OBF("PixelPassSaveConfig"), 322},
    {OBF("PixelPassGiveLevelCellReward"), 323},
    {OBF("PixelPassBuyPremium"), 324},
    {OBF("PixelPassGiveEliteReward"), 325},
    {OBF("PixelPassObtainExp"), 326},
    {OBF("PixelPassSpendExp"), 327},
    {OBF("PixelPassSetIsCompleteEliteTasks"), 328},
    {OBF("PixelPassSetChangedTaskIndex"), 329},
    {OBF("PixelPassSetWatchedVideo"), 330},
    {OBF("PixelPassCloseSeason"), 331},
    {OBF("PixelPassIncrementOfferBuyCount"), 332},
    {OBF("PixelPassSaveOffersStartDay"), 333},
    {OBF("RemoveWearItemIndeces"), 334},
    {OBF("PixelPassPresentationView"), 335},
    {OBF("BattleStatisticEndMatch"), 336},
    {OBF("PixelPassAddCompleteTaskReward"), 337},
    {OBF("PixelPassRemoveCompleteTaskReward"), 338},
    {OBF("PixelPassSaveLastViewedBuyPremiumWindow"), 339},
    {OBF("UniversalPromotionSetGroupPromotionLastBannerView"), 340},
    {OBF("Subscription20Subscribe"), 341},
    {OBF("Subscription20CollectReward"), 342},
    {OBF("Subscription20CollectLastReward"), 343},
    {OBF("Subscription20RemoveSubscription"), 344},
    {OBF("Subscription20SetPromotionLastBannerView"), 345},
    {OBF("UniversalPromotionSetSeasonId"), 350},
    {OBF("PromocodeUsePromocode"), 351},
    {OBF("UpdatePlayerStats"), 352},
    {OBF("InappTransactionAddTransaction"), 353},
    {OBF("InappTransactionsMarkTransactionAsRefunded"), 354},
    {OBF("RemoveWeapon"), 355},
    {OBF("RemoveDetails"), 356},
    {OBF("RemoveBRVehicle"), 357},
    {OBF("RemoveGadget"), 358},
    {OBF("EquipWearSkin"), 360},
    {OBF("UnequipWearSkin"), 361},
    {OBF("RouletteAdsSaveConfig"), 362},
    {OBF("RouletteAdsSelectReward"), 363},
    {OBF("RouletteAdsIncrementTotalSpins"), 364},
    {OBF("RouletteAdsAddGivenProgressBarReward"), 365},
    {OBF("RouletteAdsIncrementOfferBuyCount"), 366},
    {OBF("RouletteAdsEndSeason"), 367},
    {OBF("RouletteAdsSetWatchedVideo"), 368},
    {OBF("RouletteAdsSetLastTimeAdView"), 369},
    {OBF("UpdatePlayerStatsV2"), 370},
    {OBF("ConstructableAdsOffersGenerate"), 373},
    {OBF("ConstructableAdsOffersSelectItem"), 374},
    {OBF("ConstructableAdsOffersIncrementWatchedVideoCount"), 375},
    {OBF("ClanWarV2StartSeason"), 380},
    {OBF("ClanWarV2GeneratePersonalTaskIndexes"), 381},
    {OBF("ClanWarV2GiveTaskReward"), 382},
    {OBF("ClanWarV2SpentEventFuel"), 383},
    {OBF("ClanWarV2SetGoblinCollectSilverAndShields"), 384},
    {OBF("ClanWarV2GiveEndWarReward"), 385},
    {OBF("ClanWarV2SaveFlagRegistration"), 386},
    {OBF("ClanWarV2GiveEventBattleReward"), 387},
    {OBF("ClanWarV2SaveClanId"), 388},
    {OBF("CardRouletteStart"), 390},
    {OBF("CardRouletteSaveShuffleCards"), 391},
    {OBF("CardRouletteObtainReward"), 392},
    {OBF("TopUpStartSeason"), 393},
    {OBF("TopUpEndSeason"), 394},
    {OBF("TopUpUpdateLastTimeFirstBanner"), 395},
    {OBF("TopUpUpdateLastTimeEndBanner"), 396},
    {OBF("TopUpUpdatePurchasedPromotions"), 397},
    {OBF("TopUpUpdateLastTimePresentationBanner"), 398},
    {OBF("AdventCalendarStartSeason"), 401},
    {OBF("AdventCalendarOpenCell"), 402},
    {OBF("AdventCalendarUnlockCell"), 403},
    {OBF("AdventCalendarSaveFlag"), 404},
    {OBF("AdventCalendarShowCell"), 405},
    {OBF("ConfrontationEventStartSeason"), 406},
    {OBF("ConfrontationEventEndSeason"), 407},
    {OBF("ConfrontationEventUpdateLastTimePresentationBanner"), 408},
    {OBF("ConfrontationEventUpdateLastTimeFirstBanner"), 409},
    {OBF("ConfrontationEventUpdateLastTimeEndBanner"), 410},
    {OBF("ConfrontationEventGiveEventRewards"), 411},
    {OBF("ConfrontationEventAcceptEvent"), 412},
    {OBF("ConfrontationEventGiveLeaderboardRewards"), 413},
    {OBF("ConfrontationEventUpdateStateTutorial"), 414},
    {OBF("ConfrontationEventUpdateLastTimeAboutToEndBanner"), 415},
    {OBF("TemplateEventStart"), 420},
    {OBF("TemplateEventStop"), 421},
    {OBF("TemplateEventPurchaseCell"), 422},
    {OBF("TemplateEventSaveShownBanner"), 423},
    {OBF("TemplateEventSaveSetting"), 424},
    {OBF("TemplateEventSaveShownExp"), 425},
    {OBF("ConfrontationEventV2StartSeason"), 426},
    {OBF("ConfrontationEventV2EndSeason"), 427},
    {OBF("ConfrontationEventV2AcceptEvent"), 428},
    {OBF("ConfrontationEventV2ShowBanner"), 429},
    {OBF("ConfrontationEventV2CollectRewards"), 430},
    {OBF("GameModeShopInit"), 440},
    {OBF("GameModeShopEquipItem"), 441},
    {OBF("GameModeShopAddToBoughtItem"), 442},
    {OBF("GameModeShopRemoveFromBuyItems"), 443},
    {OBF("GameModeShopUnEquipItems"), 444},
    {OBF("GameModeShopAddFlag"), 445},
    {OBF("GameModeShopRemoveFlag"), 446},
    {OBF("ChainOfferEventStart"), 450},
    {OBF("ChainOfferEventStop"), 451},
    {OBF("ChainOfferEventBuyCell"), 452},
    {OBF("ChainOfferEventSaveShownBanner"), 453},
    {OBF("TemplateEventPutItem"), 454},
    {OBF("TemplateEventSaveSpinData"), 455},
    {OBF("TemplateEventAddCellFlag"), 456},
    {OBF("TemplateEventSaveBuyCount"), 457},
    {OBF("TemplateEventSaveNumDay"), 458},
    {OBF("TemplateEventSaveRewardedCount"), 459},
    {OBF("ReturnGift"), 460},
    {OBF("DeleteDailyStatKeys"), 461},
    {OBF("TakeRewardForLeaderboard2023"), 462},
    {OBF("XsollaInappTaken"), 463},
    {OBF("UpdateWeaponKillsStats"), 464},
    {OBF("TemplateEventSaveSelectedTask"), 465},
    {OBF("TemplateEventSaveCompletedTask"), 466},
    {OBF("WebShopTransactionAddTransaction"), 467},
    {OBF("WebShopTransactionsMarkTransactionAsRefunded"), 468},
    {OBF("GMHRecommendationSaveSelectedRule"), 470},
    {OBF("GMHRecommendationSaveSelectedItemIndex"), 471},
    {OBF("GMHRecommendationSaveLastLevel"), 472},
    {OBF("GMHRecommendationResetLevelData"), 473},
    {OBF("GMHRecommendationResetDataByItem"), 474},
    {OBF("PixelPassSaveLastViewedOfferPremiumWindow"), 475},
    {OBF("GMHTournamentSaveTournamentId"), 476},
    {OBF("GMHTournamentSaveTrophyRoadGivenLevels"), 477},
    {OBF("GMHTournamentResetTournament"), 478},
    {OBF("GMHTournamentSaveSelectedMode"), 479},
    {OBF("GMHTournamentSaveLastSeenProgress"), 480},
    {OBF("GMHTournamentSaveSeenTutorialBanner"), 481},
    {OBF("SteamDlcShopAddDlcId"), 482},
    {OBF("TemplateEventAddEventFlag"), 483},
    {OBF("ViewedEntrySetViewed"), 484},
    {OBF("CardRouletteV2Start"), 485},
    {OBF("CardRouletteV2Stop"), 486},
    {OBF("CardRouletteV2SaveShuffleCards"), 487},
    {OBF("CardRouletteV2ObtainReward"), 488},
    {OBF("CardRouletteV2Migrate"), 489},
    {OBF("CardRouletteClear"), 490},
    {OBF("AnalyticsProgress"), 777}
};

enum class SlotTypes {
    PlayerInfo = 1,
    Rating = 2,
    Currency = 3,
    Leveling = 4,
    Achievement = 5,
    LobbyCraft = 6,
    Campaign = 7,
    Pets = 8,
    PlayerEquipment = 9,
    SkinsIds = 10,
    BattleRoyaleIds = 11,
    CustomSkin = 12,
    Wear = 13,
    UtilityDictionary = 14,
    UtilityIds = 15,
    Gadgets = 16,
    WeaponSkin = 17,
    BattlePass = 18,
    GameEvents = 19,
    GME = 20,
    GatchaGifts = 21,
    Weapons = 22,
    FirstUps = 23,
    Details = 24,
    BattleRoyaleVehicle = 25,
    Inventory = 26,
    ModuleStorage = 27,
    WeaponsV17 = 28,
    FirstUpsV17 = 29,
    Offers = 30,
    RankSlot = 31,
    WeaponSkinV2 = 32,
    GameTask = 33,
    AlmanachSlot = 34,
    InAppValidatorSlot = 35,
    Gifts = 36,
    ModulesInfo = 37,
    ClanItems = 38,
    ClanWar = 39,
    ClanFinishingUpgrades = 40,
    InventoryExpiry = 41,
    MailBoxRewards = 42,
    Armor = 43,
    ArmorSkins = 44,
    KillRate = 45,
    BlackMarket = 46,
    ClanStorePromotion = 47,
    ClanGovernor = 48,
    ClanBuildings = 49,
    AdsGun = 50,
    GameModeTapReward = 51,
    ConnectSceneChest = 52,
    PetsV3 = 53,
    RankV2 = 54,
    TrophyRoad = 55,
    Tutorial = 56,
    MatchHistory = 57,
    ConstructableOffers = 58,
    WeaponSkinsNotification = 59,
    GameEventDropChance = 60,
    Marathon = 61,
    MapSecretsSlot = 62,
    Piggy_OLD = 63,
    ManualOffers = 64,
    DoubleOffers = 65,
    Vip20 = 66,
    Loadouts = 67,
    GachaNoviceGift = 68,
    Piggy = 69,
    NoviceDoubleOffers = 70,
    ProgressRoad = 71,
    Attributes = 72,
    UniversalPromotion = 73,
    PixelPass = 74,
    GameModeHub = 75,
    Shop = 76,
    BattleStatistic = 77,
    Subscription20 = 78,
    Promocode = 79,
    PlayerStats = 80,
    InappTransaction = 81,
    WearSkins = 82,
    RouletteAds = 83,
    PlayerStatsV2 = 84,
    ConstructableAdsOffers = 85,
    ClanWarV2 = 86,
    CardRoulette = 87,
    TopUp = 88,
    AdventCalendar = 89,
    ConfrontationEvent = 90,
    TemplateEventsSlot = 91,
    ConfrontationEventV2 = 92,
    GameModeShop = 93,
    ChainOfferEventsSlot = 94,
    GMHRecommendation = 95
};

inline const int levelExp[] = { 0, 15, 65, 170, 280, 395, 515, 640, 770, 910, 1055, 1210, 1370, 1540, 1715, 1900, 2095, 2300, 2515, 2750, 3000, 3270, 3560, 3870, 4195, 4540, 4905, 5290, 5690, 6110, 6550, 7010, 7485, 7980, 8495, 9030, 9580, 10150, 10740, 11350, 11975, 12620, 13285, 13970, 14670, 15390, 16130, 16890, 17665, 18640, 19275, 20110, 20960, 21830, 22720, 23630, 24555, 25500, 26465, 27450, 28450, 29470, 30510, 31570, 32645 };

struct ProgressSlot {
    SlotTypes type = SlotTypes::Wear;
    json data = {};

    ProgressSlot() = default;

    ProgressSlot(SlotTypes type) : type(type) {}
};
inline std::unordered_map<int, std::function<void(json&)>> response_callbacks = {};