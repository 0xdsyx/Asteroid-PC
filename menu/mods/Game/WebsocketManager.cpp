#include "WebsocketManager.h"

WebsocketManager::WebsocketManager(void* wsmi) : wsmi(wsmi), playerlevel(1), version("25.0.1") {};
std::unordered_map<int, std::unique_ptr<json>> command_params = {};

std::string WebsocketManager::rand_hex() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);
    std::stringstream ss;
    for (int i = 0; i < 4; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << distrib(gen);
    }
    return ss.str();
}

json WebsocketManager::createCommand(std::string cmdID, json payload, std::vector<int> u) {
    return {
        {OBF("id"), commandIDs.at(cmdID)},
        {OBF("i"), WebsocketManager::rand_hex()},
        {OBF("p"), payload},
        {OBF("h"), json::object()},
        {OBF("v"), this->version},
        {OBF("u"), u}
    };
}

void* WebsocketManager::dict_from_json(json payload) {
    return dictionaryFromJson(NewIl2cppString(payload.dump()));
}

void WebsocketManager::setversion(std::string version) {
    this->version = version;
}

void WebsocketManager::set_playerid(std::string id) {
    this->playerid = std::atoi(id.c_str());
}

void* WebsocketManager::get_wsmi() {
    return this->wsmi;
}

int WebsocketManager::SendWebsocket(il2cppString* event, void* payload, std::function<void(json &)> callback ) {
    this->playerlevel = ExperienceController::get_CurrentLevel();
    if (this->wsmi != nullptr) {
        int currentID = *(int *) ((uint64_t) this->wsmi + 0x38); // request id
        // fslog::info("current id: {}", currentID);
        if (callback != nullptr) {
            response_callbacks.insert(std::make_pair(currentID, callback));
        }
        
        return Websocket::send(this->wsmi, event, payload);
    } else {
        ImGui::InsertNotification({ImGuiToastType::Error, 1500, OBF("WebsocketManager is null!")});
    }
    return 0;
}

int WebsocketManager::SendWebsocket2(const json& request, std::function<void(json &)> callback ) {
    this->playerlevel = ExperienceController::get_CurrentLevel();
    if (this->wsmi != nullptr) {
        int currentID = *(int *) ((uint64_t) this->wsmi + 0x38);
        if (callback != nullptr) {
            response_callbacks.insert(std::make_pair(currentID, callback));
        }
        
        fslog::info("req: {}", request.dump());
        std::string commandPayload = request[0];
        Websocket::sendCommand(this->wsmi, NewIl2cppString(commandPayload.c_str()));
    } else {
        ImGui::InsertNotification({ImGuiToastType::Error, 1500, OBF("WebsocketManager is null!")});
    }
    return 0;
}


int WebsocketManager::callWebsocket(const json &request, std::function<void(json &)> callback) {
    if (this->wsmi == nullptr) {
        return -1;
    }

    std::string eventName = request[0];

    int currentID = *(int *) ((uint64_t) this->wsmi + 0x38);
    if (callback != nullptr) {
        response_callbacks.insert(std::make_pair(currentID, callback));
    }
    command_params.insert(std::make_pair(currentID, std::make_unique<json>(request)));
    fslog::info("Sending command {} with id {}", eventName.c_str(), currentID);
    fslog::debug("Request: {}", request.dump().c_str());
    Websocket::sendCommand(this->wsmi, NewIl2cppString(eventName.c_str()));
    return currentID;
}

void WebsocketManager::reloadws() {
    if (Features::Settings::autoreloadws) {
        void* dict = this->dict_from_json(json::parse(R"( {} )"));
        this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
    }
}



void WebsocketManager::_reloadws() {
    void* dict = this->dict_from_json(json::parse(R"( {} )"));

    json empty = {{}};
    json reloadp = json::array({"update_progress", empty});
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
    // this->callWebsocket(reloadp);
}

void WebsocketManager::add_wepskins(int index) {
        json commands;
        if (index == 0) {
            for (int i = 1; i < 2000; i++) {
                if ((i >= 496 && i <= 513) || (i >= 531 && i <= 541) || (i == 547))
                    continue;
                commands.push_back(
                        this->createCommand(OBF("InventoryAddItemSingle"), {{"i", i * 1000 + 14}}));
            }
        } else {
            commands.push_back(
                    this->createCommand(OBF("InventoryAddItemSingle"), {{"i", index * 1000 + 14}}));
        }

        json result = {
                {OBF("id"), commandIDs.at(OBF("Snapshot"))},
                {OBF("i"),  WebsocketManager::rand_hex()},
                {OBF("p"),  {{"c", commands}}},
                {OBF("u"), {140, 6}}
        };

        void* dict = this->dict_from_json(result);
        this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_modules(int index, int amount) {
    json commands;
    if (index == 0) {
        for (int i = 346; i <= 387; i++) {
            commands.push_back(this->createCommand(OBF("InventoryAddItemConsumable"), 
            {
                    {"t", 1155},
                    {"i", i * 1000 + 9},
                    {"c", amount}
            }));
        }
    } else {
        commands.push_back(this->createCommand(OBF("InventoryAddItemConsumable"),
        {
                {"t", 1155},
                {"i", index * 1000 + 9},
                {"c", amount}
        }));
    }
    json result = {
            {OBF("id"), commandIDs.at(OBF("Snapshot"))},
            {OBF("i"),  WebsocketManager::rand_hex()},
            {OBF("p"),  {{"c", commands}}},
            {OBF("u"), {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}


void WebsocketManager::upgrade_modules(int index) {
    json commands;
    if (index == 0) {
        for (int i = 304; i <= 345; i++) {
            for (int j = 0; j < 9; j++) {
                commands.push_back(this->createCommand(OBF("ModuleInfoIncreaseUp"), {{"i", i * 1000 + 9}}));
            }
        }
    } else {
        for (int j = 0; j < 9; j++) {
            commands.push_back(this->createCommand(OBF("ModuleInfoIncreaseUp"), {{"i", index * 1000 + 9}}));
        }
    }
    json result = {
            {"id", commandIDs.at("Snapshot")},
            {"i",  this->rand_hex()},
            {"p",  {{"c", commands}}},
            {"u", {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::change_nickname(const std::string& nickname) {
    json payload = {{OBF("Nick"), nickname}};
    json namechange = this->createCommand(OBF("SetNick"), payload);
    void* dict = this->dict_from_json(namechange);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_badge() {
    json badge = {
        {OBF("h"), json::object()},
        {OBF("i"), "0"},
        {OBF("id"), commandIDs.at(OBF("InventoryAddItemSingle"))},
        {OBF("p"), {{"ca", 115}, {"i", 700015}}},
        {OBF("v"), this->version},
        {OBF("d"), OBF("516d10856935ea5db83b5b0eb719309e3e973174")},
        {OBF("req_id"), 747},
        {OBF("sid"), OBF("8884dc7137af4b1c950fb186a3f876e2")}
    };

    void* dict = this->dict_from_json(badge);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_boosters(int amount, int index) {
        json commands;
        commands.push_back(this->createCommand(OBF("InventoryAddItemConsumable"), {{"t", 1520}, {"i", index * 1000 + 30}, {"c", amount}}));
        for (int l = 0; l < 10; l++) {
            commands.push_back(this->createCommand(OBF("AnalyticsProgress"), {{"t", 1520}, {"i", index * 1000 + 30}, {"c", amount}}));
        }

        json result = {
                {"id", commandIDs.at(OBF("Snapshot"))},
                {"i",  WebsocketManager::rand_hex()},
                {"p",  {{"c", commands}}},
                {"u", {140, 6}}
        };

        void* dict = this->dict_from_json(result);
        this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_grafitis(int index) {
    json commands;
    if (index == 0) {
        for (int i = 1; i < 2000; i++) {
            commands.push_back(
                    this->createCommand(OBF("InventoryAddItemSingle"), {{"i", i * 1000 + 28}}));
        }
    } else {
        commands.push_back(
                this->createCommand(OBF("InventoryAddItemSingle"), {{"i", index * 1000 + 28}}));
    }
    json result = {
            {"id", commandIDs.at(OBF("Snapshot"))},
            {"i",  WebsocketManager::rand_hex()},
            {"p",  {{"c", commands}}},
            {"u", {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_currency(int amount, const std::string &_type, const std::string &cause) {
    json commands = {
            this->createCommand(OBF("AddCurrency"), {{"c",  _type},
                                           {"v",  amount},
                                           {"ca", 6}}, {141, 278}),
            this->createCommand(OBF("AnalyticsProgress"), {
                    {OBF("eid"),    1012},
                    {OBF("params"), {
                                       {OBF("ip1"), amount},
                                       {OBF("sp1"), _type},
                                       {OBF("sp2"), cause},
                                       {OBF("ip2"), 0}
                               }}
            }, {141, 278})
    };

    json result = {
            {OBF("id"), commandIDs.at(OBF("Snapshot"))},
            {OBF("i"),  this->rand_hex()},
            {OBF("p"),  {{"c", commands}}},
            {OBF("u"), {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict, [](json& callback_data) {
        // fslog::info("callbackdata: {}", callback_data.dump());
    });
}

void WebsocketManager::report_player(int id) {
    json command = {
        {OBF("AnalyticsProgress"), {
            {OBF("eid"), 1124},
            {OBF("params"), {
                {OBF("ip1"), id},
                {OBF("ip2"), 1},
                {OBF("jp1"), {
                    {OBF("reason_1"), OBF("Aimlock")},
                    {OBF("reason_2"), OBF("Effect_overlay")},
                    {OBF("reason_3"), OBF("Msg_spam")}
                }},
            }},
        }}
    };
    json finalcommand = this->createCommand(OBF("AnalyticsProgress"), command);
    void* dict = this->dict_from_json(finalcommand);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

json WebsocketManager::get_progress(int uniq_id, std::vector<int> slots) {
    fslog::info("{}", uniq_id);
    json j = {
            {OBF("player_id"), std::to_string(uniq_id)}
    };

    /*if (!slots.empty()) {
        for (auto &slot: slots) {
            j[OBF("slots")].push_back(slot);
        }
    } */

    json result = {
            {OBF("id"), commandIDs.at(OBF("Snapshot"))},
            {OBF("i"),  this->rand_hex()},
            {OBF("p"),  {{"c", j}}},
            {OBF("u"), {140, 6}}
    };

    json finalcommand = json::array({OBF("get_progress"), j});
    return finalcommand;
    // this->SendWebsocket2(finalcommand);
}

json WebsocketManager::fetch_slot(int slot) {
    json response;
    if (this->playerid == 0) {
        this->set_playerid(get_AccountID()->ToString());
    }

    json payload = WebsocketManager::get_progress(this->playerid, {slot});
    this->SendWebsocket2(payload, [](json& callback_data) {
        fslog::info("callbackdata: {}", callback_data.dump());
    });
    return response;
}

void WebsocketManager::set_level(int level) {
    json commands;
    if (level > 0) {
        for (int _level = 1; _level <= level; _level += 2) {
            commands.push_back(this->createCommand(OBF("UpdateLevel"), {{"l", _level}}));
        }
    } else {
        commands.push_back(this->createCommand(OBF("UpdateLevel"), {{"l", level}}));
    }

    commands.insert(commands.end(), {
            this->createCommand(OBF("AnalyticsProgress"), {{OBF("eid"), 52}, {OBF("params"), {{OBF("ip1"), 0}, {OBF("ip2"), 0}}}}),
            this->createCommand(OBF("UpdateExperience"), {{OBF("e"),  0}, {OBF("ec"), 4}, {OBF("ad"), {}}}),
            this->createCommand(OBF("AnalyticsProgress"), {
                    {OBF("eid"),    1043},
                    {OBF("params"), {
                                       {OBF("ip1"), levelExp[level] - levelExp[this->playerlevel]},
                                       {OBF("ip2"), levelExp[level]},
                                       {OBF("ip3"), levelExp[this->playerlevel]},
                                       {OBF("sp1"), OBF("MultiplayerMatchReward")},
                                       {OBF("jp1"), {{OBF("v_ProgressRoad"), level}, {OBF("v_Tutorial"), 8}}}
                               }}
            }),
    });

    json result = {
            {"id", commandIDs.at(OBF("Snapshot"))},
            {"i", this->rand_hex()},
            {"p", {{"c", commands}}},
            {"req_id", 0},
            {"u", {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::win_deathmatch() {
    int kill = generateRandomNumber(1, 40);
    int death = generateRandomNumber(1, 10);
    json result = {
            {OBF("kill_cnt"),        kill},
            {OBF("death_cnt"),       death},
            {OBF("kill_cnt_month"),  kill},
            {OBF("death_cnt_month"), death},
            {OBF("accuracy"),        100},
            {OBF("mode"),            2},
            {OBF("rating"),          0},
            {OBF("league_id"),       0},
            {OBF("req_id"),          106},
            {OBF("sid"),             ""}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_player")), dict);
}

void WebsocketManager::add_parts(int index, int amount, int item_records) {
    json commands;
    if (index == 0) {
        for (int i = 1; i < 2000; i++) {
            int ItemIndex = i * 1000 + item_records;
            commands.push_back(this->createCommand(OBF("AddDetails"), {{"i", ItemIndex},
                                                             {"d", amount}}));
        }
    } else {
        int ItemIndex = index * 1000 + item_records;
        commands.push_back(this->createCommand(OBF("AddDetails"), {{"i", ItemIndex},
                                                         {"d", amount}}));
    }
    json result = {
            {OBF("id"), commandIDs.at(OBF("Snapshot"))},
            {OBF("i"),  this->rand_hex()},
            {OBF("p"),  {{OBF("c"), commands}}},
            {OBF("u"), {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_weapons_ranged(int startIndex, int endIndex, int level) {
    json commands;
    for (int i = startIndex; i <= endIndex; i++) {
        int realIndex = i * 1000 + 1;
        void* itemrecord = getItemRecordFromIndex(realIndex);
        if (itemrecord != nullptr) {
            int grade = ItemRecord::get_Rarity(itemrecord);
            if (Features::Settings::adddlc && i >= 1702 && i <= 1704) {
                commands.push_back(this->createCommand(OBF("AddWeaponV17"), {{"i", realIndex}, {"oc", 9999},
                                                                {"u", {{"l", level}, {"r", grade}}}}));
            } else if (!(i >= 1702 && i <= 1704) && (true || std::find(illegalWepIndex.begin(), illegalWepIndex.end(), realIndex) == illegalWepIndex.end())) {
                commands.push_back(this->createCommand(OBF("AddWeaponV17"), {{"i", realIndex},
                                                                {"u", {{"l", level}, {"r", grade}}}}));
            }
        }
    }
    json result = {
            {OBF("id"), commandIDs.at(OBF("Snapshot"))},
            {OBF("i"),  this->rand_hex()},
            {OBF("p"),  {{OBF("c"), commands}}},
            {OBF("u"), {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_weapon(int index, int level) {
    json commands;
    void* itemrecord = getItemRecordFromIndex(index);
    if (itemrecord != nullptr) {
        int grade = ItemRecord::get_Rarity(itemrecord);
        commands.push_back(this->createCommand(OBF("AddWeaponV17"), {{"i", index},
                                                        {"u", {{"l", level}, {"r", grade}}}}));
    }

    json result = {
            {OBF("id"), commandIDs.at(OBF("Snapshot"))},
            {OBF("i"), this->rand_hex()},
            {OBF("p"), {{OBF("c"), commands}}},
            {OBF("u"), {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::bug_clan(const std::string &ClanID, int index, int amount) {
    json commands;
    commands.push_back(this->createCommand(OBF("InventoryRemoveItemConsumable"), {{"t", 1460},
                                                                        {"i", 56027},
                                                                        {"c", 1}}));
    commands.push_back(this->createCommand(OBF("CreateClanItems"), {{"items",
                                                           {{{OBF("id"), OBF("302262401.1698698027.1")},
                                                             {OBF("clan"), ClanID},
                                                             {OBF("item_index"), 1017},
                                                             {OBF("count"), amount},
                                                             {OBF("buy"), false}}}}}));
    if (index == 0) {
        for (int i = 1; i < 2000; i++) {
            commands.push_back(this->createCommand(OBF("AnalyticsProgress"), {{"t", 1460},
                                                                    {"i", 56027},
                                                                    {"c", 1}}));
            commands.push_back(this->createCommand(OBF("CreateClanItems"), {{OBF("items"), {{{"id",
                                                                               OBF("302262401.1698698027.1")},
                                                                              {OBF("clan"), ClanID},
                                                                              {OBF("item_index"),
                                                                               i * 1000 + 17 +
                                                                               1000},
                                                                              {OBF("count"), amount},
                                                                              {OBF("buy"),
                                                                               false}}}}}));
        }
    } else {
        commands.push_back(this->createCommand(OBF("AnalyticsProgress"), {{"t", 1460},
                                                                {"i", 56027},
                                                                {"c", 1}}));
        commands.push_back(this->createCommand(OBF("CreateClanItems"), {{OBF("items"), {{{"id",
                                                                           OBF("302262401.1698698027.1")},
                                                                          {OBF("clan"), ClanID},
                                                                          {OBF("item_index"),
                                                                           index * 1000 + 17 +
                                                                           1000},
                                                                          {OBF("count"), amount},
                                                                          {OBF("buy"), false}}}}}));
    }
    json result = {
            {"id", commandIDs.at(OBF("Snapshot"))},
            {"i",  this->rand_hex()},
            {"p",  {{"c", commands}}},
            {"u", {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_dlcweps(int level) {
    json commands;
    commands.push_back(this->createCommand(OBF("AddWeaponV17"), {{"i", 1703001}, {OBF("oc"), 9999}, {"u", {{"l", level}, {"r", 5}}}})); // fps destroyer
    commands.push_back(this->createCommand(OBF("AddWeaponV17"), {{"i", 1704001}, {OBF("oc"), 9999}, {"u", {{"l", level}, {"r", 5}}}})); // achivement hunter
    commands.push_back(this->createCommand(OBF("AddWeaponV17"), {{"i", 1702001}, {OBF("oc"), 9999}, {"u", {{"l", level}, {"r", 5}}}})); // new well pistol

    json result = {
            {"id", commandIDs.at("Snapshot")},
            {"i",  this->rand_hex()},
            {"p",  {{"c", commands}}},
            {"u", {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}


void WebsocketManager::add_armor(int index, int level) {
    json commands;
    if (index == 0) {
        for (int i = 1; i < 2000; i++) {
            commands.push_back(
                this->createCommand(OBF("BuyArmor"), {
                    {"a", i * 1000 + 2},
                    {"u", level},
                    {"c", "migr"}
                })
            );
        }
    } else {
        commands.push_back(
            this->createCommand(OBF("BuyArmor"), {
                {"a", index * 1000 + 2},
                {"u", level},
                {"c", "migr"}
            })
        );
    }

    json result = {
            {"id", commandIDs.at(OBF("Snapshot"))},
            {"i",  this->rand_hex()},
            {"p",  {{"c", commands}}},
            {"u", {140, 6}}
    };

    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_all_wear(int level) {
    json commands;
    for (int i = 1; i < 2000; i++) {
        commands.push_back(this->createCommand(OBF("AddPurchasedWear"), {{"w", "a*" + std::to_string(i * 1000 + 2)}})); // wear
        commands.push_back(this->createCommand(OBF("InventoryAddItemSingle"), {{"i", i * 1000 + 29}})); // skins
        commands.push_back(this->createCommand(OBF("BuyArmor"), {{"a", i * 1000 + 2}, {"u", level}})); // armor
        commands.push_back(this->createCommand(OBF("InventoryAddItemSingle"), {{"i", i * 1000 + 23}})); // armor skins
    }

    json result = {
            {"id", commandIDs.at(OBF("Snapshot"))},
            {"i",  this->rand_hex()},
            {"p",  {{"c", commands}}},
            {"u", {140, 6}}
    };
    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_gadget(int index, int level) {
    json commands;
    if (index == 0) {
        for (int i = 1; i < 1000; i++) {
            int realindex = i * 1000 + 7;
            commands.push_back(
                {{
                "c", {{
                    {"id", commandIDs.at(OBF("AddPurhasedGadget"))},
                    {
                        "p", {
                            {"g", realindex}, {"u", level}
                        }
                    },
                    {"u", {7}}}
                }}
            });
        }
    } else {
        commands.push_back(
            {{
            "c", {{
                {"id", commandIDs.at(OBF("AddPurhasedGadget"))},
                {
                    "p", {
                        {"g", index * 1000 + 7}, {"u", level}
                    }
                },
                {"u", {7}}}
            }}
        });
    }

    json result = {
            {"id", commandIDs.at(OBF("Snapshot"))},
            {"i",  this->rand_hex()},
            {"p",  {{"c", commands}}},
            {"u", {140, 6}}
    };
    void* dict = this->dict_from_json(result);
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_all_royale() {
    json commands;
    for (int i = 1; i < 2000; i++) {
        commands.push_back(this->createCommand(OBF("UpdateBattleRoyaleList"), {{"1", i * 1000 + 5}}));
        // commands.push_back(this->createCommand(OBF("UpdateBRVehicle"), {{"i", i * 1000 + 5}, {"u", 4}}));
    }

    json result = {
            {"id", commandIDs.at(OBF("Snapshot"))},
            {"i",  this->rand_hex()},
            {"p",  {{"c", commands}}},
            {"u", {140, 6}}
    };
    void* dict = this->dict_from_json(result);  
    this->SendWebsocket(NewIl2cppString(OBF("update_progress")), dict);
}

void WebsocketManager::add_skin(const std::string& name, const std::string& base64) { 
    json payload = json::array({"update_player", 
        {{"skin", base64}},
    });
    fslog::info("payload: {}", payload.dump());
    this->SendWebsocket2(payload);
}
