#include "imgui_menu.h"



void ImguiDX11Manager::render() {
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	this->render_overlays();
	this->ProcessKeyInput();
	if (authVars::isUsingProxy) { ImGui::EndFrame(); ImGui::Render(); this->p_context->OMSetRenderTargets(1, &this->mainRenderTargetView, nullptr); ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData()); return; }
	if (this->menuclosed) { ImGui::EndFrame(); ImGui::Render(); this->p_context->OMSetRenderTargets(1, &this->mainRenderTargetView, nullptr); ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData()); return; }
	
	#ifdef PAIDVERSION 
	if (!authVars::Login) {
		ImGui::SetNextWindowSize(ImVec2(900, 650));
		ImGui::Begin(OBF("asteroidlogin"), nullptr, ImGuiWindowFlags_NoDecoration); {
			auto draw = ImGui::GetWindowDrawList();
			auto pos = ImGui::GetWindowPos();
			auto size = ImGui::GetWindowSize();
			
			draw->AddText(Fonts::FontAwesome, 25.0f, ImVec2(pos.x + 15, pos.y + 15), ImColor(255, 255, 255), OBF("Asteroid"));
			draw->AddText(Fonts::FontAwesome, 25.0f, ImVec2(pos.x + 115, pos.y + 15), ImColor(147, 68, 207), OBF("++"));

			ImGui::SetCursorPos(ImVec2(50, 100));
			ImGui::BeginGroup(); {
				ImGui::Text(OBF("Username: ")); ImGui::SameLine(); ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.5);
				ImGui::InputText(OBF("##username"), authVars::usernameBuf, IM_ARRAYSIZE(authVars::usernameBuf)); SPACING2();
				
				ImGui::Text(OBF("Password: ")); ImGui::SameLine(); ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.5);
				ImGui::InputText(OBF("##passwordinput"), authVars::passwordBuf, IM_ARRAYSIZE(authVars::passwordBuf));

				SPACING2(); SPACING2();
				if (ImGui::CustomButton(OBF("login"), OBF("Login"), 100, 30)) {
					authVars::statusText = OBF("Checking... Please wait...");
					authVars::username = authVars::usernameBuf;
					authVars::password = authVars::passwordBuf;
					if (authVars::username != "" && authVars::password != "") {
						auth::saveCreds(authVars::username.c_str(), authVars::password.c_str());
						authVars::initiatelogin = true;
					} else {
						authVars::statusText = OBF("The username or password is empty!");
					}
				} SPACING2();
				std::string Test = std::string(OBF("Status: ")) + authVars::statusText;
				ImGui::Text(Test.c_str());
			}
			ImGui::EndGroup();
		}
		ImGui::End(); ImGui::Render(); this->p_context->OMSetRenderTargets(1, &this->mainRenderTargetView, nullptr);
	}
	#endif

	ImGui::SetNextWindowSize(ImVec2(900, 650));
	ImGui::Begin(OBF("asteroidv2"), nullptr, ImGuiWindowFlags_NoDecoration); {
		auto draw = ImGui::GetWindowDrawList();
		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();
		Variables::menuLoaded = true;

		draw->AddRectFilled(ImVec2(pos.x + 75, pos.y), ImVec2(pos.x + size.x, pos.y + size.y), ImColor(15, 15, 20, 225.0), 5.0f, ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomRight);
		draw->AddRectFilled(ImVec2(pos.x + 75, pos.y), ImVec2(pos.x + size.x, pos.y + 50), ImColor(20, 20, 25, 225.0), 5.0f, ImDrawFlags_RoundCornersTopRight);

		draw->AddText(Fonts::FontAwesome, 25.0f, ImVec2(pos.x + 15, pos.y + 15), ImColor(255, 255, 255), OBF("AST"));

		draw->AddText(Fonts::FontAwesome, 25.0f, ImVec2(pos.x + 600, pos.y + 15), ImColor(255, 255, 255), OBF("Asteroid"));
		#ifdef PAIDVERSION
		draw->AddText(Fonts::FontAwesome, 25.0f, ImVec2(pos.x + 700, pos.y + 15), ImColor(147, 68, 207), OBF("++"));
		#endif
		#ifdef FREEVERSION
		draw->AddText(Fonts::FontAwesome, 18.0f, ImVec2(pos.x + 680, pos.y + 36), ImColor(147, 68, 207), OBF("Free"));
		#endif
		std::string versionText = OBF("v") + Variables::asteroidVersion + OBF(" | 25.0.1");

		draw->AddText(Fonts::FontAwesome, 25.0f, ImVec2(pos.x + 740, pos.y + 15), ImColor(255, 255, 255), versionText.c_str());

		ImGui::SetCursorPos({ 11,66 });
		ImGui::BeginGroup(); {
			ImGui::PushFont(Fonts::FontAwesome);
			if (ImGui::CustomTab(ICON_FA_GUN, 15, 45, Tab == Combat)) { Tab = Combat; }
			if (ImGui::CustomTab(ICON_FA_USER, 15, 45, Tab == Account)) { Tab = Account; }
			if (ImGui::CustomTab(ICON_FA_BARS, 15, 45, Tab == Misc)) { Tab = Misc; }
			if (ImGui::CustomTab(ICON_FA_GEAR, 15, 45, Tab == Settings)) { Tab = Settings; }
			ImGui::PopFont();
		} ImGui::EndGroup();

		if (Tab == Combat) {
			ImGui::SetCursorPos(ImVec2{ 86, 16 });
			if (ImGui::SubTab(GameplaySubTab == tab1, OBF("Gameplay"), ImVec2(85, 25))) GameplaySubTab = tab1;
			ImGui::SameLine();
			if (ImGui::SubTab(GameplaySubTab == tab2, OBF("Aimbot"), ImVec2(85, 25))) GameplaySubTab = tab2;
			ImGui::SameLine();
			if (ImGui::SubTab(GameplaySubTab == tab3, OBF("ESP"), ImVec2(85, 25))) GameplaySubTab = tab3;
		}
		if (Tab == Account) {
			ImGui::SetCursorPos(ImVec2{ 86, 16 });
			if (ImGui::SubTab(AccountSubTab == tab1, OBF("Account"), ImVec2(85, 25))) AccountSubTab = tab1;
			ImGui::SameLine();
			if (ImGui::SubTab(AccountSubTab == tab2, OBF("WebSocket"), ImVec2(85, 25))) AccountSubTab = tab2;
			ImGui::SameLine();
			if (ImGui::SubTab(AccountSubTab == tab3, OBF("Skin"), ImVec2(85, 25))) AccountSubTab = tab3;
		}
		if (Tab == Misc) {
			ImGui::SetCursorPos(ImVec2{ 86, 16 });
			if (ImGui::SubTab(MiscSubTab == tab1, OBF("Misc"), ImVec2(85, 25))) MiscSubTab = tab1;
		}
		if (Tab == Settings) {
			ImGui::SetCursorPos(ImVec2{ 86, 16 });
			if (ImGui::SubTab(SettingsSubTab == tab1, OBF("Settings"), ImVec2(85, 25))) SettingsSubTab = tab1;
			ImGui::SameLine();
			if (ImGui::SubTab(SettingsSubTab == tab2, OBF("Account"), ImVec2(85, 25))) SettingsSubTab = tab2;
		}
		ImGui::SetCursorPos(ImVec2(85, 54));
		ImGui::BeginChild(OBF("Cat"), ImVec2(0, 0), true); {
			switch (Tab) {
			case Combat:
				if (GameplaySubTab == tab1) { // main
					ImGui::SetCursorPos(ImVec2(25, 10));
					ImGui::PushFont(Fonts::Medium);
					ImGui::MenuChild(OBF("Main"), ImVec2(355, 300)); {
						SPACING2();
						ImGui::Indent(10);
						ImGui::CustomCheckbox(OBF("Kill All"), &Features::GameplayMain::killall); SPACING2();
						ImGui::CustomCheckbox(OBF("Godmode"), &Features::GameplayMain::godmode); SPACING2();
						ImGui::CustomCheckbox(OBF("Friendly Fire"), &Features::GameplayMain::friendlyfire); SPACING2();
						ImGui::CustomCheckbox(OBF("Polymorph"), &Features::GameplayMain::polymorph); SPACING2();
						ImGui::CustomCheckbox(OBF("Silent Aim"), &Features::GameplayMain::silentaim); SPACING2();
						ImGui::CustomCheckbox(OBF("Infinite Ammo"), &Features::GameplayMain::infammo); SPACING2();
						ImGui::CustomCheckbox(OBF("Kill Points"), &Features::GameplayMain::killpoints); SPACING2();
						ImGui::CustomCheckbox(OBF("Double Jump"), &Features::GameplayMain::doublejump); SPACING2();
						ImGui::CustomCheckbox(OBF("Chat Filter Bypass"), &Features::GameplayMain::chatbypass); SPACING2();
						ImGui::CustomCheckbox(OBF("Jetpack"), &Features::GameplayMain::jetpack); SPACING2();
						ImGui::CustomCheckbox(OBF("X-ray"), &Features::GameplayMain::xray); SPACING2();
						ImGui::CustomCheckbox(OBF("Emoji Spam"), &Features::GameplayMain::emojispam); SPACING2();
						ImGui::CustomCheckbox(OBF("Head Magnify"), &Features::GameplayMain::headmagnify); SPACING2();
						ImGui::CustomCheckbox(OBF("Enemy Marker"), &Features::GameplayMain::enemymarker); SPACING2();
						ImGui::CustomCheckbox(OBF("Gadget Disabler"), &Features::GameplayMain::gadgetdisabler); SPACING2();
					} ImGui::EndChild(); 

					ImGui::SetCursorPos(ImVec2(400, 10));
					ImGui::MenuChild(OBF("Weapon"), ImVec2(355, 225)); {
						SPACING2();
						ImGui::Indent(10);
						ImGui::CustomCheckbox(OBF("Quick Scope"), &Features::GameplayWeapon::quickscope); SPACING2();
						if (ImGui::CustomCheckbox(OBF("Max Damage"), &Features::GameplayWeapon::maxdamage)) {
							if (Features::GameplayWeapon::maxdamage) {
								Features::GameplayWeapon::lowdamage = false; Features::GameplayWeapon::multiplydamage = false;
							}
						} SPACING2();
						if (ImGui::CustomCheckbox(OBF("Low Damage"), &Features::GameplayWeapon::lowdamage)) {
							if (Features::GameplayWeapon::lowdamage) {
								Features::GameplayWeapon::maxdamage = false; Features::GameplayWeapon::multiplydamage = false;
							}
						}; SPACING2();
						if (ImGui::CustomCheckbox(OBF("Multiply Damage"), &Features::GameplayWeapon::multiplydamage)) {
							if (Features::GameplayWeapon::multiplydamage) {
								Features::GameplayWeapon::maxdamage = false; Features::GameplayWeapon::lowdamage = false;
							}
						}; ImGui::SameLine();
						ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8f);
						ImGui::SliderFloat(OBF("##dmgslider"), &Features::GameplayWeapon::damagemultiplier, 1, 10); SPACING2();
						ImGui::CustomCheckbox(OBF("No Spread"), &Features::GameplayWeapon::nospread); SPACING2();

					} ImGui::EndChild(); 

					ImGui::SetCursorPos(ImVec2(400, 250));
					ImGui::MenuChild(OBF("Trolling"), ImVec2(355, 225)); {
						SPACING2();
						ImGui::Indent(10);
						ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.9);
						ImGui::CustomCheckbox(OBF("Chat Spam"), &Features::GameplayTroll::chatspam); ImGui::SameLine();
						// ImGui::CustomInputText(OBF("##chatinput"), "Input", 150, Features::GameplayTroll::chatspamBuf, IM_ARRAYSIZE(Features::GameplayTroll::chatspamBuf), ImGuiInputTextFlags_None);
						ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8f);
						ImGui::InputText(OBF("##chatinput"), Features::GameplayTroll::chatspamBuf, IM_ARRAYSIZE(Features::GameplayTroll::chatspamBuf)); SPACING2();
						ImGui::CustomCheckbox(OBF("Mass kill"), &Features::GameplayTroll::masskill); SPACING2();
						ImGui::CustomCheckbox(OBF("Tele kill"), &Features::GameplayTroll::telekill); SPACING2();
						ImGui::CustomCheckbox(OBF("Middle Click TP"), &Features::GameplayTroll::middleclicktp); SPACING2();
					} ImGui::EndChild(); 

					ImGui::SetCursorPos(ImVec2(25, 325));
					ImGui::MenuChild(OBF("Bullet"), ImVec2(355, 300)); {
						SPACING2();
						ImGui::Indent(10);
						ImGui::CustomCheckbox(OBF("Laser"), &Features::GameplayBullet::shootlaser); SPACING2();
						ImGui::CustomCheckbox(OBF("Rocket"), &Features::GameplayBullet::shootrocket); SPACING2();
						ImGui::CustomCheckbox(OBF("Shotgun"), &Features::GameplayBullet::shootshotgun); SPACING2();
						ImGui::CustomCheckbox(OBF("Dash"), &Features::GameplayBullet::shootdash); SPACING2();
						ImGui::CustomCheckbox(OBF("Harpoon"), &Features::GameplayBullet::shootharpoon); SPACING2();
						ImGui::CustomCheckbox(OBF("Exploding Bullet"), &Features::GameplayBullet::shootexplodingbullet); SPACING2();
						ImGui::CustomCheckbox(OBF("Rickochet Rocket"), &Features::GameplayBullet::RickochetRocket); SPACING2();
						ImGui::CustomCheckbox(OBF("Ignore Shield"), &Features::GameplayBullet::ignoreshield); SPACING2();
					} ImGui::PopFont(); ImGui::EndChild(); 

					ImGui::SetCursorPos(ImVec2(400, 475));
					ImGui::MenuChild(OBF("Effects"), ImVec2(355, 225)); {
						SPACING2();
						ImGui::Indent(10);
						ImGui::CustomCheckbox(OBF("Stacking Blindness"), &Features::GameplayEffects::stackingblindness); SPACING2();
						ImGui::CustomCheckbox(OBF("Electric Shock"), &Features::GameplayEffects::electricshock); SPACING2();
						ImGui::CustomCheckbox(OBF("Charm"), &Features::GameplayEffects::charm); SPACING2();
						ImGui::CustomCheckbox(OBF("Slowdown"), &Features::GameplayEffects::slowdown); SPACING2();
					} ImGui::EndChild(); 

				} else if (GameplaySubTab == tab2) { // aimbot
					ImGui::SetCursorPos(ImVec2(25, 10));
					ImGui::PushFont(Fonts::Medium);
					ImGui::MenuChild(OBF("Main"), ImVec2(355, 200)); {
						SPACING2();
						ImGui::CustomCheckbox(OBF("Aimbot"), &Features::GameplayAimbot::aimbot); SPACING2();
						ImGui::CustomCheckbox(OBF("Visibility Check"), &Features::GameplayAimbot::visibilitycheck); SPACING2();
						ImGui::CustomCheckbox(OBF("Left Click Trigger"), &Features::GameplayAimbot::leftclicktrigger); SPACING2();
						ImGui::CustomCheckbox(OBF("Trigger Bot"), &Features::GameplayAimbot::triggerbot); SPACING2();
						ImGui::Indent(10);
					} ImGui::EndChild(); 

					ImGui::SetCursorPos(ImVec2(400, 10));
					ImGui::MenuChild(OBF("FOV"), ImVec2(355, 225)); {
						SPACING2();
						ImGui::CustomCheckbox(OBF("Show FOV"), &Features::GameplayAimbot::showfov); SPACING2();
						ImGui::CustomCheckbox(OBF("Color Changing FOV"), &Features::GameplayAimbot::colorchangingfov); SPACING2();
						ImGui::CustomCheckbox(OBF("RGB Fov"), &Features::GameplayAimbot::rgbfov); SPACING2();
						ImGui::CustomCheckbox(OBF("Custom Color"), &Features::GameplayAimbot::customcolor); ImGui::SameLine();
						ImGui::ColorEdit4(OBF("##fovcolor"), Features::GameplayAimbot::fovaimbotcolor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs); SPACING2();
						ImGui::Text(OBF("Size: "));
						ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8);
						ImGui::SliderFloat(OBF("##fovslider"), &Features::GameplayAimbot::fovsize, 10, 360); SPACING2();
						ImGui::Indent(10);
					} ImGui::EndChild(); 

					ImGui::SetCursorPos(ImVec2(25, 225));
					ImGui::MenuChild(OBF("Config"), ImVec2(360, 200)); {
						SPACING2();
						ImGui::CustomCheckbox(OBF("Smoothing"), &Features::GameplayAimbot::smoothing); SPACING2();
						ImGui::SliderFloat(OBF("##smoothingslider"), &Features::GameplayAimbot::smoothingamount, 0.9f, 1.f);
						ImGui::CustomCombo(OBF("Aim at:"), &aimatParts[1], aimAtPartsItems, IM_ARRAYSIZE(aimAtPartsItems));
						ImGui::Indent(10);
					} ImGui::PopFont(); ImGui::EndChild(); 
					SPACING2();
					ImGui::Text(OBF("Aimbot bind: ")); ImGui::SameLine();
					ImGui::SetCursorPosY(ImGui::GetCursorPos().y + - 5);
					if (ImGui::CustomButton(OBF("##aimbotbind"), Variables::aimbotbindkey.c_str(), 100, 25)) {
						Variables::listenforkeybind = true; Variables::listenforkeybindAimbot = true;
					} 

				} else if (GameplaySubTab = tab3) { // esp
					ImGui::SetCursorPos(ImVec2(25, 10));
					ImGui::PushFont(Fonts::Medium);
					ImGui::MenuChild(OBF("Main"), ImVec2(355, 340)); {
						SPACING2();
						ImGui::CustomCheckbox(OBF("ESP"), &Features::GameplayESP::esp); SPACING2();
						ImGui::CustomCheckbox(OBF("Bone ESP"), &Features::GameplayESP::espbone); SPACING2();
						ImGui::CustomCheckbox(OBF("Line ESP"), &Features::GameplayESP::espline); SPACING2();
						if (ImGui::CustomCheckbox(OBF("Box ESP"), &Features::GameplayESP::espbox)) {
							if (Features::GameplayESP::espbox) {
								Features::GameplayESP::esp3dbox = false; 
							}
						} ImGui::SameLine();
						if (ImGui::CustomCheckbox(OBF("3D Box ESP"), &Features::GameplayESP::esp3dbox)) {
							if (Features::GameplayESP::esp3dbox) {
								Features::GameplayESP::espbox = false;
							}
						} SPACING2();
						ImGui::CustomCheckbox(OBF("Health ESP"), &Features::GameplayESP::esphealth); SPACING2();
						ImGui::CustomCheckbox(OBF("Distance ESP"), &Features::GameplayESP::espdistance); SPACING2();
						ImGui::Indent(10);
					} ImGui::EndChild(); 
					
					ImGui::SetCursorPos(ImVec2(400, 10));
					ImGui::MenuChild(OBF("Config"), ImVec2(355, 200)); {
						SPACING2();
						ImGui::Text(OBF("Team Color: "));  ImGui::SameLine();
						ImGui::ColorEdit4(OBF("##teamcolor"), Features::GameplayESP::espTeamColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs); SPACING2();
						ImGui::Text(OBF("Enemy Color: ")); ImGui::SameLine();
						ImGui::ColorEdit4(OBF("##enemycolor"), Features::GameplayESP::espEnemyColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs); SPACING2();
						ImGui::CustomCheckbox(OBF("Show Team"), &Features::GameplayESP::showteam); SPACING2();
						ImGui::CustomCheckbox(OBF("Show Enemy"), &Features::GameplayESP::showenemy); SPACING2();
						ImGui::Indent(10);
						
					} ImGui::EndChild(); 

					ImGui::SetCursorPos(ImVec2(400, 225));
					ImGui::MenuChild(OBF("Others"), ImVec2(355, 200)); {
						SPACING2();
						ImGui::CustomCheckbox(OBF("Origin ESP"), &Features::GameplayESP::esporigin); SPACING2();
						ImGui::CustomCheckbox(OBF("Show Ping"), &Features::GameplayESP::showping); SPACING2();
						ImGui::Indent(10);
					} ImGui::EndChild(); 

					ImGui::PopFont(); 
				}
				break;

				case Account:
					if (AccountSubTab == tab1) {
						ImGui::SetCursorPos(ImVec2(25, 10));
						ImGui::PushFont(Fonts::Medium);
						ImGui::MenuChild(OBF("Basic"), ImVec2(355, 150)); {
							SPACING2();
							std::string multipliertext = OBF("Collectibles: x") + std::to_string(Features::Account::collectiblesLoop * Features::Account::collectiblesMultiplier);
							ImGui::CustomCheckbox(multipliertext.c_str(), &Features::Account::collectibles); ImGui::SameLine();
							ImGui::SetNextItemWidth(75);
							ImGui::SliderInt(OBF("##currencyinput"), &Features::Account::collectiblesMultiplier, 1, 10);
							ImGui::SameLine(); ImGui::Text(OBF(" x ")); ImGui::SameLine();
							ImGui::SetNextItemWidth(75);
							ImGui::SliderInt(OBF("##currencyinput_"), &Features::Account::collectiblesLoop, 1, 10); SPACING2();

							std::string expmultipliertext = OBF("EXP Multiplier: x") + std::to_string(Features::Account::expmultiplierAmount);
							ImGui::CustomCheckbox(expmultipliertext.c_str(), &Features::Account::expmultiplier); ImGui::SameLine();
							ImGui::SetNextItemWidth(125);
							ImGui::SliderInt(OBF("##expmultiplierinput"), &Features::Account::expmultiplierAmount, 1, 25); SPACING2();
							ImGui::CustomCheckbox(OBF("Free clan upgrades"), &Features::Account::freeclanupgrade);
							ImGui::Indent(10);
						}ImGui::EndChild(); 

						ImGui::SetCursorPos(ImVec2(400, 10));
						ImGui::MenuChild(OBF("Currency Adder"), ImVec2(355, 250)); {
							SPACING2();
							ImGui::Text(OBF("Amount: ")); ImGui::SameLine();
							ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8);
							ImGui::InputInt(OBF("##currencyadderinput"), &Features::Account::currencyAmount); SPACING2();
							ImGui::Columns(4, NULL, false);
							if (ImGui::CustomButton(OBF("##coins"), OBF("Coins"), 75, 30)) {
								Features::Account::isAddingCoins = true;
							} ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##gems"), OBF("Gems"), 75, 30)) {
								Features::Account::isAddingGems = true;
							} ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##tickets"), OBF("Tickets"), 75, 30)) {
								Features::Account::isAddingPPTickets = true;
							} ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##silver"), OBF("Silver"), 75, 30)) {
								Features::Account::isAddingSilver = true;
							} ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##keys"), OBF("Keys"), 75, 30)) {
								Features::Account::isAddingKeys = true;
							} ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##coupons"), OBF("Coupons"), 75, 30)) {
								Features::Account::isAddingCoupons = true;
							} ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##novice"), OBF("Novice"), 75, 30)) {
								Features::Account::isAddingNoviceChest = true;
							} ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##fighter"), OBF("Fighter"), 75, 30)) {
								Features::Account::isAddingFighterChest = true;
							} ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##winner"), OBF("Winner"), 75, 30)) {
								Features::Account::isAddingWinnerChest = true;
							} ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##clansc"), OBF("Clan SC"), 75, 30)) {
								Features::Account::isAddingClanSCPoints = true;
							} ImGui::NextColumn();

							ImGui::Columns(1);

							ImGui::Indent(10);
						} ImGui::EndChild(); 

						ImGui::SetCursorPos(ImVec2(25, 200));
						ImGui::MenuChild(OBF("All Item Adder"), ImVec2(355, 250)); {
							SPACING2();
							if (ImGui::CustomButton(OBF("##armor"), OBF("Armors"), 75, 30)) {
								Features::Account::isAddingArmor = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##hats"), OBF("Hats"), 75, 30)) {
								Features::Account::isAddingHats = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##masks"), OBF("Masks"), 75, 30)) {
								Features::Account::isAddingMasks = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##skins"), OBF("Skins"), 75, 30)) {
								Features::Account::isAddingSkins = true;
							} 

							if (ImGui::CustomButton(OBF("##capes"), OBF("Capes"), 75, 30)) {
								Features::Account::isAddingCapes = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##boots"), OBF("Boots"), 75, 30)) {
								Features::Account::isAddingBoots = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##gadgets"), OBF("Gadgets"), 75, 30)) {
								Features::Account::isAddingGadgets = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##pets"), OBF("Pets"), 75, 30)) {
								Features::Account::isAddingPets = true;
							} 
							if (ImGui::CustomButton(OBF("##cars"), OBF("Cars"), 75, 30)) {
								Features::Account::isAddingCars = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##gliders"), OBF("Gliders"), 75, 30)) {
								Features::Account::isAddingGliders = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##lobby"), OBF("Lobby"), 75, 30)) {
								Features::Account::isAddingLobbyItems = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##veteren"), OBF("Vet Set"), 75, 30)) {
								Features::Account::isAddingVeterenSet = true;
							} 
							if (ImGui::CustomButton(OBF("##unknownskin"), OBF("? Skin"), 75, 30)) {
								Features::Account::isAddingUnknownSkin = true;
							} ImGui::NextColumn();

							ImGui::Indent(10);
						}ImGui::EndChild(); 

						ImGui::SetCursorPos(ImVec2(400, 280));
						ImGui::PushFont(Fonts::Medium);
						ImGui::MenuChild(OBF("Weapon Adder"), ImVec2(355, 250)); {

							if (Features::Account::addWeaponEndRange < Features::Account::addWeaponStartRange) {
								Features::Account::addWeaponEndRange = Features::Account::addWeaponStartRange;
							}
							if (Features::Account::addWeaponStartRange > Features::Account::addWeaponEndRange) {
								Features::Account::addWeaponStartRange = Features::Account::addWeaponEndRange;
							}
							if (Features::Account::addWeaponStartRange < 0) { Features::Account::addWeaponStartRange = 1; }
							if (Features::Account::addWeaponEndRange < 0) { Features::Account::addWeaponEndRange = 1; }
							if (Features::Account::addWeaponEndRange > IM_ARRAYSIZE(weaponList)) { Features::Account::addWeaponEndRange = IM_ARRAYSIZE(weaponList); }
							if (Features::Account::addWeaponStartRange > IM_ARRAYSIZE(weaponList)) { Features::Account::addWeaponStartRange = IM_ARRAYSIZE(weaponList); }

							SPACING2();
							ImGui::Text(OBF("Start Range: ")); ImGui::SameLine();
							ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8);
							ImGui::InputInt(OBF("##startrange"), &Features::Account::addWeaponStartRange); 

							ImGui::Text(OBF("End Range: ")); ImGui::SameLine();
							ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8);
							ImGui::InputInt(OBF("##endrange"), &Features::Account::addWeaponEndRange); 

							#ifdef PAIDVERSION
								const char* buttonTextRanged = OBF("[ws] Add:");
							#else
								const char* buttonTextRanged = OBF("Add:");
							#endif
							if (ImGui::CustomButton(OBF("##addweaponrange"), buttonTextRanged, 75, 20)) {
								Features::Account::addCustomWepRange = true;
							}
							SPACING2(); SPACING2();

							#ifdef PAIDVERSION
								const char* buttonText = OBF("[ws] Add:");
							#else
								const char* buttonText = OBF("Add:");
							#endif
							if (ImGui::CustomButton(OBF("##addweapon"), buttonText, 75, 20)) {
								Features::Account::addCustomWep = true;
							} ImGui::SameLine();
							ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8);
							ImGui::InputText(OBF("##wepstringinput"), Features::Account::addwepBuf, IM_ARRAYSIZE(Features::Account::addwepBuf));
							if (ImGui::CustomButton(OBF("##wepstrings"), OBF("Weapon Strings"), 120, 20)) {
								ShellExecuteA(NULL, OBF("open"), OBF("https://yeetdisdude.xyz/weaponstrings"), NULL, NULL, SW_SHOWNORMAL);
							}

							ImGui::Indent(10);
						} ImGui::EndChild();

						ImGui::SetCursorPos(ImVec2(25, 475));
						ImGui::MenuChild(OBF("Individual Adder"), ImVec2(355, 250)); {
							if (ImGui::Button(OBF("Add:  ", ImVec2(125, 30)))) {
								Features::Account::isAddingIndividual = OBF(true);
							} ImGui::SameLine();
							ImGui::Text(OBF("Type: ")); ImGui::SameLine();
							ImGui::SetNextItemWidth(100);
							ImGui::Combo(OBF("##itemtype_combo"), &selectedAdderTypeIndex, itemAdderTypes, IM_ARRAYSIZE(itemAdderTypes)); ImGui::SameLine();
							if (selectedAdderTypeIndex == 0) { // wear
								ImGui::SetNextItemWidth(100);
								ImGui::Combo(OBF("##weartype"), &wearTypeIndex, wearTypes, IM_ARRAYSIZE(wearTypes)); 
								ImGui::Text(OBF("Name: ")); ImGui::SameLine();
								ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.6);
								if (wearTypeIndex == 0) { // Hat
									ImGui::Combo(OBF("##hatname"), &selectedItemIndex, hatList, IM_ARRAYSIZE(hatList));
								} else if (wearTypeIndex == 1) { // mask
									ImGui::Combo(OBF("##maskname"), &selectedItemIndex, maskList, IM_ARRAYSIZE(maskList));
								} else if (wearTypeIndex == 2) { /// cape
									ImGui::Combo(OBF("##capename"), &selectedItemIndex, capeList, IM_ARRAYSIZE(capeList));
								} else if (wearTypeIndex == 3) { // bost
									ImGui::Combo(OBF("##bootname"), &selectedItemIndex, bootsList, IM_ARRAYSIZE(bootsList));
								}
							} else if (selectedAdderTypeIndex == 1) { // Armor
								ImGui::NewLine(); ImGui::Text(OBF("Name: ")); 
								ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.6); ImGui::SameLine();
								ImGui::Combo(OBF("##armorname"), &selectedItemIndex, armorList, IM_ARRAYSIZE(armorList));
							} else if (selectedAdderTypeIndex == 2) { // royale
								ImGui::NewLine(); ImGui::Text(OBF("Name: ")); 
								ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.6); ImGui::SameLine();
								ImGui::Combo(OBF("##skinname"), &selectedSkinIndex, skinList, IM_ARRAYSIZE(skinList));
							} else if (selectedAdderTypeIndex == 3) { // gadget
								ImGui::NewLine(); ImGui::Text(OBF("Name: ")); 
								ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.6); ImGui::SameLine();
								ImGui::Combo(OBF("##gadgetname"), &selectedItemIndex, gadgetList, IM_ARRAYSIZE(gadgetList));
							} else if (selectedAdderTypeIndex == 4) { // pet
								ImGui::NewLine(); ImGui::Text(OBF("Name: ")); 
								ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.6); ImGui::SameLine();
								ImGui::Combo(OBF("##petname"), &selectedPetIndex, petsList, IM_ARRAYSIZE(petsList));
							} else if (selectedAdderTypeIndex == 5) { // lobby
								ImGui::NewLine(); ImGui::Text(OBF("Name: ")); 
								ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.6); ImGui::SameLine();
								ImGui::Combo(OBF("##lobbyname"), &selectedLobbyIndex, lobbyItemList, IM_ARRAYSIZE(lobbyItemList));
							}
						}

						ImGui::PopFont();
					}
					if (AccountSubTab == tab2) { // websocket
						#ifdef FREEVERSION
						ImGui::Text(OBF("Asteroid++ will be for sale soon!"));
						SPACING2(); SPACING2();
						ImGui::Text(OBF("Websocket mods are only availale in Asteroid++!"));
						ImGui::Text(OBF("You can purchase it from our Discord server"));
						if (ImGui::CustomButton(OBF("##discordbtn"), OBF("Discord"), 125, 35)) {
							ShellExecuteA(NULL, OBF("open"), OBF("https://discord.com/invite/3cnQwMWnFh"), NULL, NULL, SW_SHOWNORMAL);
						} SPACING2();

						if (ImGui::CustomButton(OBF("##modules"), OBF("All Moduules"), 100, 30)) {
							Features::Account::addallmodules = true;
						}
						if (ImGui::CustomButton(OBF("##wepskins"), OBF("All Wep Skins"), 100, 30)) {
							Features::Account::addwepskins = true;
						}
						if (ImGui::CustomButton(OBF("##reloadws"), OBF("Reload"), 100, 30)) {
							Features::Account::reloadws = true;
						}
						#endif 

						#ifdef PAIDVERSION
						ImGui::SetCursorPos(ImVec2(25, 10));
						ImGui::PushFont(Fonts::Medium);
						ImGui::MenuChild(OBF("Adders"), ImVec2(355, 450)); {
							SPACING2()
							if (ImGui::CustomButton(OBF("##modules"), OBF("All Moduules"), 100, 30)) {
								Features::Account::addallmodules = true;
							} ImGui::SameLine();
							if (ImGui::CustomButton(OBF("##modulesupgrade"), OBF("Upgrade All"), 100, 30)) {
								Features::Account::upgradeallmodules = true;
							} 
							SPACING2() 
							ImGui::SetNextItemWidth(100);
							ImGui::InputInt(OBF("##boostersslider"), &Features::Account::boostersAmount); ImGui::SameLine();
							ImGui::SetCursorPosY(ImGui::GetCursorPos().y - 25);
							ImGui::PushItemWidth(100);
							ImGui::CustomCombo(OBF("Boosters"), &boosters[1], boosterscombo, IM_ARRAYSIZE(boosterscombo));
							ImGui::PopItemWidth();
							if (ImGui::CustomButton(OBF("##addbooster"), OBF("Add Booster"), 100, 30)) {
								Features::Account::addboosters = true;
							} SPACING2() SPACING2()
							
							ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 15);
							ImGui::Columns(3, NULL, false);
							if (ImGui::CustomButton(OBF("##wepskins"), OBF("All Wep Skins"), 100, 30)) {
								Features::Account::addwepskins = true;
							} SPACING2() ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##grafiti"), OBF("All Graffitis"), 100, 30)) {
								Features::Account::addgrafiti = true;
							} SPACING2() ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##wepparts"), OBF("All Wep Parts"), 100, 30)) {
								Features::Account::addallwepparts = true;
							} SPACING2() ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##dlcweps"), OBF("DLC Weps"), 100, 30)) {
								Features::Account::adddlcweps = true;
							} SPACING2() ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##allwear"), OBF("All Wear"), 100, 30)) {
								Features::Account::addallwear = true;
							} SPACING2() ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##wsallgadget"), OBF("All Gadgets"), 100, 30)) {
								Features::Account::addallgadgets = true;
							} SPACING2() ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##wsallroyale"), OBF("All Royale"), 100, 30)) {
								Features::Account::addallroyale = true;
							} SPACING2() ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##allweps"), OBF("All Weapons"), 100, 30)) {
								Features::Account::addallweapons = true;
							} SPACING2() ImGui::NextColumn();
							if (ImGui::CustomButton(OBF("##getpress"), OBF("Get Progress"), 100, 30)) {
								Features::Account::getslot = true;
							} SPACING2() ImGui::NextColumn();
							ImGui::Columns(1);


							ImGui::Indent(10);
						}ImGui::EndChild(); 

						ImGui::SetCursorPos(ImVec2(400, 10));
						ImGui::MenuChild(OBF("Others"), ImVec2(325, 200)); {
							SPACING2()
							if (ImGui::CustomButton(OBF("##reloadws"), OBF("Reload"), 100, 30)) {
								Features::Account::reloadws = true;
							} SPACING2()
							if (ImGui::CustomButton(OBF("##changenamee"), OBF("Change name"), 100, 30)) {
								Features::Account::changenickname = true;
							} ImGui::SameLine();
							ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8); SETCURSORPOSY10();
							ImGui::InputText(OBF("##changenameinput"), Features::Account::changenamebuf, IM_ARRAYSIZE(Features::Account::changenamebuf)); SPACING2()
							if (ImGui::CustomButton(OBF("##addbadge"), OBF("Add Badge"), 100, 30)) {
								Features::Account::addbadge = true;
							} 
							ImGui::SameLine(); SETCURSORPOSY10();
							ImGui::HoverItemText(OBF("If your account is new, it will show up as 0 year")); SPACING2()
							if (ImGui::CustomButton(OBF("##setlevel"), OBF("Set Level"), 100, 30)) {
								Features::Account::setlevel = true;
							} ImGui::SameLine(); SETCURSORPOSY10();
							ImGui::InputInt(OBF("##setlevelslider"), &Features::Account::setleveltarget); SPACING2()

							if (ImGui::CustomButton(OBF("##bugclan"), OBF("Bug Clan"), 100, 30)) {
								Features::Account::bugclan = true;
							} ImGui::SameLine(); SETCURSORPOSY10();
							ImGui::Text(OBF("ID: ")); ImGui::SameLine();
							ImGui::SetNextItemWidth(150); SETCURSORPOSY10();
							ImGui::InputText(OBF("##bugclaninput"), Features::Account::clanidBuf, IM_ARRAYSIZE(Features::Account::clanidBuf));
							ImGui::SameLine(); SETCURSORPOSY10();
							ImGui::HoverItemText(OBF("Causes the clan fort to bug and not be interacted with."));
							SPACING2();
							ImGui::Indent(10);
						}ImGui::EndChild(); 

						ImGui::SetCursorPos(ImVec2(400, 225));
						ImGui::MenuChild(OBF("Currency Adder"), ImVec2(325, 175)); {
							SPACING2()
							ImGui::Text(OBF("Amount: ")); ImGui::SameLine();
							ImGui::SetNextItemWidth(200);
							ImGui::InputInt(OBF("##currencyinputws"), &Features::Account::wscurrencyamount); SPACING2()
							ImGui::SetCursorPosY(ImGui::GetCursorPos().y - 25);
							ImGui::CustomCombo(OBF("Currency:"), &wscurrencytype[1], wscurrencyComboVisualName, IM_ARRAYSIZE(wscurrencyComboVisualName));
							if (ImGui::CustomButton(OBF("##addcurrencyws"), OBF("Add"), 100, 30)) {
								Features::Account::wsaddcurrency = true;
							} SPACING2()

							ImGui::Indent(10);
						}ImGui::EndChild(); 
						#endif
					}

					if (AccountSubTab == tab3) { // skin modder
						SPACING2();
						ImGui::Text(OBF("Skin Adder"));
						SPACING2();

						SPACING2();
						if (ImGui::CustomButton(OBF("##selectskinfile"), OBF("Select PNGs"), 100, 30)) {
							Features::Account::SkinModder::skinfiles = OpenFileDialog(L"PNG Files (*.png)\0*.png\0");
							Features::Account::SkinModder::skinpngpath = "";
							for (int i = 0; i < Features::Account::SkinModder::skinfiles.size(); i++) {
								std::string currentFile = Features::Account::SkinModder::skinfiles[i];
								if (isSkinImageValid(currentFile)) {
									Features::Account::SkinModder::skinpngpath += currentFile;
									Features::Account::SkinModder::skinpngpath += "\n";	
								} else {
									Features::Account::SkinModder::skinfiles.erase(Features::Account::SkinModder::skinfiles.begin() + i);
									ImGui::InsertNotification({ImGuiToastType::Error, 1500, OBF("Invalid skin: %s"), currentFile.c_str()});
								}
							}
						} ImGui::SameLine();
						ImGui::Text(Features::Account::SkinModder::skinpngpath.c_str());
						SPACING2(); SPACING2();

						ImGui::Text(OBF("Skin Name: ")); ImGui::SameLine();
						ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.3); 
						ImGui::InputText(OBF("##skinnamebuf"), Features::Account::SkinModder::skinnameBuf, IM_ARRAYSIZE(Features::Account::SkinModder::skinnameBuf));
						if (ImGui::CustomButton(OBF("##addskinws"), OBF("Add"), 100, 30)) {
							if (!Features::Account::SkinModder::skinpngpath.empty()) {
								Features::Account::SkinModder::addskin = true;
							} else {
								ImGui::InsertNotification({ImGuiToastType::Error, 1500, OBF("Please select a skin file first!")});
							}
						} 

						
					}
					break;

				case Misc:
					if (MiscSubTab == tab1) {
						ImGui::SetCursorPos(ImVec2(25, 10));
						ImGui::PushFont(Fonts::Medium);
						ImGui::MenuChild(OBF("Auth Info"), ImVec2(355, 275)); {
							SPACING2();
							ImGui::Indent(10);
							if (ImGui::CustomButton(OBF("##copyid"), OBF("Copy"), 50, 30)) {
								if (Variables::versionCompatible) { 
									copyToClipboard(get_AccountID()->ToString().c_str()); 
									ImGui::InsertNotification({ImGuiToastType::Success, 1500, OBF("Copied player ID to clipboard!")});
								}
							} ImGui::SameLine();
							ImGui::Text(Variables::accountID.c_str()); SPACING2();
							
							if (ImGui::CustomButton(OBF("##copyauth"), OBF("Copy"), 50, 30)) {
								if (Variables::versionCompatible) {
									 copyToClipboard(get_AccountAuth(get_AuthInstance())->ToString().c_str());
									 ImGui::InsertNotification({ImGuiToastType::Success, 1500, OBF("Copied auth secret to clipboard!")});
								}
							} ImGui::SameLine();
							ImGui::Text(Variables::accountAuth.c_str());

						} ImGui::EndChild(); 

						ImGui::SetCursorPos(ImVec2(405, 10));
						ImGui::PushFont(Fonts::Medium);
						ImGui::MenuChild(OBF("Menu Info"), ImVec2(355, 275)); {
							SPACING2();
							ImGui::Indent(10);
							std::string activeuserstxt = OBF("Active Free Users: ") + std::to_string(authVars::activeCount);;
							std::string activeuserspaidtxt = OBF("Active Paid Users: ");
							#ifdef PAIDVERSION
								activeuserspaidtxt += std::to_string(authVars::paidAtiveCount);
							#else
								activeuserspaidtxt += "Not Available";
							#endif

							std::string pgversiontxt = OBF("Pixel Gun 3D Version: ") + Application::get_Version()->ToString();

							ImGui::Text(activeuserstxt.c_str()); SPACING2();
							ImGui::Text(activeuserspaidtxt.c_str()); SPACING2();
							ImGui::Text(pgversiontxt.c_str());
							std::string versionText = OBF("Asteroid Version: ") + Variables::asteroidVersion;
							ImGui::Text(versionText.c_str());
						} ImGui::EndChild(); 
						ImGui::PopFont();
					}
					break;

				case Settings:
					if (SettingsSubTab == tab1) {
						ImGui::SetCursorPos(ImVec2(25, 10));
						ImGui::PushFont(Fonts::Medium);
						ImGui::MenuChild(OBF("Mod Settings"), ImVec2(355, 275)); {
							SPACING2();
							if (ImGui::CustomButton(OBF("##cursliderbutton"), OBF("Unlock Cur Slider"), 125, 35)) {
								Features::Account::maxCurSlider = 50000;
							}
							SPACING2();
							if (ImGui::CustomButton(OBF("##bruteforceitemrecord"), OBF("Dump Item Record"), 125, 35)) {
								Features::Settings::bruteforceitemrecord = true;
							}
							SPACING2();
							ImGui::Text(OBF("ESP Start: ")); ImGui::SameLine();
							ImGui::SetCursorPosY(ImGui::GetCursorPos().y - 30);
							ImGui::SetNextItemWidth(100);
							ImGui::CustomCombo(OBF("ESP Start"), &espStart[100], espStartcombo, IM_ARRAYSIZE(espStartcombo)); SPACING2();
							ImGui::CustomCheckbox(OBF("Allow DLC Weps/skins to be added"), &Features::Settings::adddlc);
							SPACING2();
							#ifdef PAIDVERSION
							ImGui::CustomCheckbox(OBF("Log WebSocket requests"), &Features::Settings::logwebsocket);
							SPACING2();
							ImGui::CustomCheckbox(OBF("Auto Reload Websocket"), &Features::Settings::autoreloadws);
							SPACING2();
							#endif
							ImGui::Indent(10);

						} ImGui::EndChild(); 

						ImGui::SetCursorPos(ImVec2(405, 10));
						ImGui::MenuChild(OBF("Menu Settings"), ImVec2(355, 200)); {
							SPACING2();
							ImGui::Text(OBF("Open Menu bind: ")); ImGui::SameLine();
							ImGui::SetCursorPosY(ImGui::GetCursorPos().y + - 5);
							if (ImGui::CustomButton(OBF("##menubind"), Variables::menuToggleBindKey.c_str(), 100, 25)) {
								Variables::listenforkeybind = true; Variables::listenforkeybindMenuToggle = true;
							} 
							SPACING2();
						} ImGui::EndChild(); 

						ImGui::SetCursorPos(ImVec2(25, 300));
						ImGui::MenuChild(OBF("Socials"), ImVec2(355, 275)); {
							SPACING2();
							if (ImGui::CustomButton(OBF("##discordbtn"), OBF("Discord"), 125, 35)) {
								ShellExecuteA(NULL, "open", OBF("https://discord.com/invite/3cnQwMWnFh"), NULL, NULL, SW_SHOWNORMAL);
							} SPACING2();
							if (ImGui::CustomButton(OBF("##youtubebtn"), OBF("YouTube"), 125, 35)) {
								ShellExecuteA(NULL, "open", OBF("https://www.youtube.com/@YeetDisDude"), NULL, NULL, SW_SHOWNORMAL);
							}
						} ImGui::EndChild(); 

						ImGui::SetCursorPos(ImVec2(405, 225));
						ImGui::MenuChild(OBF("Credits"), ImVec2(355, 300)); {
							ImGui::Text(OBF("YeetDisDude - Lead Developer"));
							ImGui::Text(OBF("Nullbit - Developer"));
							ImGui::Text(OBF("Pulsed - Backend work & developer"));
							ImGui::Text(OBF("modfs team"));
							SPACING2();
							ImGui::Text(OBF("Craze & Dsyq - Asteroid UI"));
							ImGui::Text(OBF("BoredKarma"));
							ImGui::Text(OBF("Soto sapi - pattern scanning"));
						} ImGui::EndChild(); 

						ImGui::PopFont();
						ImGui::EndChild(); 
					}

					if (SettingsSubTab == tab2) {
						SPACING2();
						ImGui::Text(OBF("User Info"));
						SPACING2(); SPACING2();
						std::string activeuserspaidtxt = OBF("Username: ");
						#ifdef PAIDVERSION
							activeuserspaidtxt += authVars::username;
						#else
							activeuserspaidtxt += "Free user";
						#endif
						std::string expiryTxt = OBF("Expiry: ");
						#ifdef PAIDVERSION
							expiryTxt += authVars::expirydate;
						#else
							expiryTxt += "Free user";
						#endif

						ImGui::Text(activeuserspaidtxt.c_str());
						ImGui::Text(expiryTxt.c_str());
					}
					break;
			}

		} ImGui::EndChild();
	} ImGui::End();
	
	ImGui::EndFrame();

	ImGui::Render();
	this->p_context->OMSetRenderTargets(1, &this->mainRenderTargetView, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

float timer = 0.0f;
float speed = 2.5f;
Vector3 fixW2Sout(Vector3 original) {
	return Vector3(original.X, (ImguiDX11Manager::instance().dxHeight - original.Y), original.Z);
}
void DrawESPBox(int x, int y, int w, int h, ImVec4 color) {
	auto background = ImGui::GetBackgroundDrawList();
	background->AddRectFilled(ImVec2(x, y - 1), ImVec2(w, h), ImColor(color.x, color.y, color.z, 0.07), 0, 0);
	background->AddRectFilled(ImVec2(x, y + 1), ImVec2(w, h), ImColor(color.x, color.y, color.z, 0.07), 0, 0);
	background->AddRectFilled(ImVec2(x - 1, y), ImVec2(w, h), ImColor(color.x, color.y, color.z, 0.07), 0, 0);
	background->AddRectFilled(ImVec2(x + 1, y), ImVec2(w, h), ImColor(color.x, color.y, color.z, 0.07), 0, 0);
	background->AddRectFilled(ImVec2(x, y), ImVec2(w, h), ImColor(color.x, color.y, color.z, 0.07), 0, 0);
	background->AddRect(ImVec2(x, y), ImVec2(w, h), ImColor(color.x, color.y, color.z, 1.0), 0, 0);
}
void Draw3DBox(Vector3 min, Vector3 max, ImVec4 Color, float thickness) {
    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
    Vector3 corners[8] = {
		Vector3(min.X,min.Y,min.Z),
		Vector3(min.X,max.Y,min.Z),
		Vector3(max.X,max.Y,min.Z),
		Vector3(max.X,min.Y,min.Z),
		Vector3(min.X,min.Y,max.Z),
		Vector3(min.X,max.Y,max.Z),
		Vector3(max.X,max.Y,max.Z),
		Vector3(max.X,min.Y,max.Z)
	};


    Vector3 _corners[8];
    for (int i = 0; i <= 7; i++) {
        _corners[i] = fixW2Sout(Camera::WorldToScreenPoint(localplayer.get_player_cam(), corners[i]));
    }

    for (int i = 1; i <= 4; i++) {
        if(_corners[i].X > 0.01 && _corners[i].X < ImguiDX11Manager::instance().dxWidth) {
            ImColor color2 = ImColor(Color.x, Color.y, Color.z, 1.0);
            draw_list->AddLine(ImVec2(_corners[i - 1].X, _corners[i - 1].Y), ImVec2(_corners[i % 4].X, _corners[i % 4].Y), color2, thickness);
            draw_list->AddLine(ImVec2(_corners[i - 1].X, _corners[i - 1].Y), ImVec2(_corners[i + 3].X, _corners[i + 3].Y), color2, thickness);
            draw_list->AddLine(ImVec2(_corners[i + 3].X, _corners[i + 3].Y), ImVec2(_corners[i % 4 + 4].X, _corners[i % 4 + 4].Y), color2, thickness);
        }
    }
}
using Features::GameplayAimbot::fovaimbotcolor;
using Features::GameplayESP::espEnemyColor;
using Features::GameplayESP::espTeamColor;
int random = 0;
void ImguiDX11Manager::render_overlays() {
	ImguiDX11Manager& manager = ImguiDX11Manager::instance();
	void* thread_ref = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

	if (Features::GameplayAimbot::aimbot && Features::GameplayAimbot::showfov && manager.dxWidth > 0 && manager.dxHeight > 0) {
		ImVec4 circleColor;
		if (Features::GameplayAimbot::colorchangingfov) {
			timer += ImGui::GetIO().DeltaTime * speed;
			float red = 0.0f;
			if (Features::GameplayAimbot::rgbfov) {
				red = (sin(timer + 4.0f * 3.1415f / 3.0f) + 1.0f) * 0.5f * (211 - 19) + 19;
			}
			float green = (sin(timer) + 1.0f) * 0.5f * (224 - 46) + 46;
			float blue = (sin(timer + 2.0f * 3.1415 / 3.0f) + 1.0f) * 0.5f * (230 - 37) + 37;
			circleColor = ImVec4(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
		} else {
			circleColor = ImVec4(fovaimbotcolor[0], fovaimbotcolor[1], fovaimbotcolor[2], fovaimbotcolor[3]);
		}
		if (Features::GameplayAimbot::customcolor) {
			circleColor = ImVec4(fovaimbotcolor[0], fovaimbotcolor[1], fovaimbotcolor[2], fovaimbotcolor[3]);
		}
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2((manager.dxWidth / 2), (manager.dxHeight / 2)), Features::GameplayAimbot::fovsize, ImGui::GetColorU32(circleColor), 200, 1.0f);
	}

	if (Features::GameplayESP::esp && (Features::GameplayESP::espbox || Features::GameplayESP::espline || Features::GameplayESP::esp3dbox || Features::GameplayESP::esphealth || Features::GameplayESP::espdistance || Features::GameplayESP::espbone)) {
		if (localplayer.get_ref() != nullptr && !playerList.empty() && InappBonusesController::isInMatch() && ticksSinceMatchStart > roundedfps) {
			for (int i = 1; i < playerList.size(); i++) {
				void* camera = localplayer.get_player_cam();
				if (camera) {
					Player player = playerList[i];
					void* pDamageable = player.get_playerdamagable();
					void* pTransform = player.get_transform();
					
					if (player.get_ref() != localplayer.get_ref() && pTransform != nullptr && pDamageable != nullptr && !PlayerDamageable::isDead(pDamageable)) {
						void* transform = Component::get_Transform(pTransform);
						if (transform != nullptr) {
							bool enemy = PlayerDamageable::isEnemyTo(pDamageable, localplayer.get_ref());
							Vector3 playerPos = Transform::get_Position(transform);
							Vector3 playerHeadPos = fixW2Sout(Camera::WorldToScreenPoint(camera, playerPos + Vector3(0, 1, 0)));
							Vector3 playerFeetPos = fixW2Sout(Camera::WorldToScreenPoint(camera, playerPos - Vector3(0, 1.1, 0)));

							if (playerHeadPos.Z > 0.1 && playerHeadPos.Y <= dxHeight - 1 && playerPos.Y >= -20) {
								ImVec4 espcolor = enemy ? ImVec4(espEnemyColor[0], espEnemyColor[1], espEnemyColor[2], espEnemyColor[3]) : ImVec4(espTeamColor[0], espTeamColor[1], espTeamColor[2], espTeamColor[3]);
								ImVec2 startPoint = ImVec2(dxWidth / 2, dxHeight / 2);
								if (espStart[100] == 0) {
									startPoint = ImVec2(dxWidth / 2, dxHeight / 2);
								} else if (espStart[100] == 1) {
									startPoint = ImVec2(dxWidth / 2, 5);
								} else if (espStart[100] == 2) {
									startPoint = ImVec2(dxWidth / 2, dxHeight);
								}
								
								if (Features::GameplayESP::espline) {
									if ((Features::GameplayESP::showenemy && enemy) || (Features::GameplayESP::showteam && !enemy)) {
										ImVec2 endPoint = ImVec2(playerHeadPos.X, playerHeadPos.Y);
										ImGui::GetBackgroundDrawList()->AddLine(startPoint, endPoint, ImGui::GetColorU32(espcolor), 1.5f);
									}
								}

								float boxHeight = abs(playerHeadPos.Y - playerFeetPos.Y);
								float boxWidth = boxHeight * 0.65f;
								Vector2 vBox = { playerHeadPos.X - (boxWidth / 2), playerHeadPos.Y };
								if (Features::GameplayESP::espbox) {
									if ((Features::GameplayESP::showenemy && enemy) || (Features::GameplayESP::showteam && !enemy)) {
										DrawESPBox(vBox.X, vBox.Y, vBox.X + boxWidth, vBox.Y + boxHeight, espcolor);
									}
								}
								if (Features::GameplayESP::esp3dbox) {
									if ((Features::GameplayESP::showenemy && enemy) || (Features::GameplayESP::showteam && !enemy)) {
										Vector3 extents = Vector3(0.45f, 1.09f, 0.45f);
										Draw3DBox(playerPos - extents, playerPos + extents, espcolor, 0.9f);
									}
									
								}
								if (Features::GameplayESP::espbone) {
									if ((Features::GameplayESP::showenemy && enemy) || (Features::GameplayESP::showteam && !enemy)) {
										void* player_ref = player.get_ref();
										
										void* bodyRenderer = *(void**)((uintptr_t)player_ref + fieldoffsets::playerBodyRenderer);
										void* headRenderer = *(void**)((uintptr_t)player_ref + fieldoffsets::playerHeadRenderer);
										void* armsRenderer = *(void**)((uintptr_t)player_ref + fieldoffsets::playerArmsRenderer);
										void* legsRenderer = *(void**)((uintptr_t)player_ref + fieldoffsets::playerLegsRenderer);
										
										std::vector<Vector3> bodyBonesSorted;
										std::vector<Vector3> legBones;
										Vector3 headBone;
										std::vector<Vector3> armBones;
										std::vector<Vector3> handBones;
										std::vector<Vector3> feetBones;
										
										monoArray<void**>* bones = Renderer::get_bones(bodyRenderer);
										for (int i = 0; i < bones->getLength(); ++i) {
											void* bone = bones->getPointer()[i];
											Vector3 bonePos = Transform::get_Position(Component::get_Transform(bone));
											Vector3 boneScreenPos = fixW2Sout(Camera::WorldToScreenPoint(camera, bonePos));
											bodyBonesSorted.push_back(boneScreenPos);
											std::string DispText = std::to_string(i);
										}
										
										
										bones = Renderer::get_bones(headRenderer);
										for (int i = 0; i < bones->getLength(); ++i) {
											void* bone = bones->getPointer()[i];
											Vector3 bonePos = Transform::get_Position(Component::get_Transform(bone));
											Vector3 boneScreenPos = fixW2Sout(Camera::WorldToScreenPoint(camera, bonePos));
											headBone = boneScreenPos;
											std::string DispText = std::to_string(i);
										}
										
										
										bones = Renderer::get_bones(armsRenderer);
										for (int i = 0; i < bones->getLength(); ++i) {
											void* bone = bones->getPointer()[i];
											Vector3 bonePos = Transform::get_Position(Component::get_Transform(bone));
											Vector3 boneScreenPos = fixW2Sout(Camera::WorldToScreenPoint(camera, bonePos));
											armBones.push_back(boneScreenPos);

											Quaternion boneRot = Transform::get_rotation(Component::get_Transform(pTransform));
											
											Vector3 localForward = boneRot * Vector3(0.f,0.f,1.f);
											
											Vector3 handPos = fixW2Sout(Camera::WorldToScreenPoint(camera, bonePos + localForward * 0.5f));
											handBones.push_back(handPos);
											std::string DispText = std::to_string(i);
										}

										
										
										bones = Renderer::get_bones(legsRenderer);
										for (int i = 0; i < bones->getLength(); ++i) {
											void* bone = bones->getPointer()[i];
											Vector3 bonePos = Transform::get_Position(Component::get_Transform(bone));
											Vector3 boneScreenPos = fixW2Sout(Camera::WorldToScreenPoint(camera, bonePos));
											legBones.push_back(boneScreenPos);
											Vector3 feetPos = fixW2Sout(Camera::WorldToScreenPoint(camera, bonePos - Vector3(0.f, 0.4f, 0.f)));
											feetBones.push_back(feetPos);
											std::string DispText = std::to_string(i);
										}
										
										std::sort(bodyBonesSorted.begin(), bodyBonesSorted.end(), cmpByHeight);
										legBones = customSort(legBones);

										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(legBones[0].X, legBones[0].Y), ImVec2(legBones[1].X, legBones[1].Y), ImColor(255, 255, 255), 1.5f);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(legBones[2].X, legBones[2].Y), ImVec2(legBones[3].X, legBones[3].Y), ImColor(255, 255, 255), 1.5f);

										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(legBones[1].X, legBones[1].Y), ImVec2(feetBones[1].X, feetBones[1].Y), ImColor(255, 255, 255), 1.5f);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(legBones[3].X, legBones[3].Y), ImVec2(feetBones[3].X, feetBones[3].Y), ImColor(255, 255, 255), 1.5f);


										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(legBones[0].X, legBones[0].Y), ImVec2(bodyBonesSorted[4].X, bodyBonesSorted[4].Y), ImColor(255, 255, 255), 1.5f);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(legBones[2].X, legBones[2].Y), ImVec2(bodyBonesSorted[4].X, bodyBonesSorted[4].Y), ImColor(255, 255, 255), 1.5f);

										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bodyBonesSorted[4].X, bodyBonesSorted[4].Y), ImVec2(bodyBonesSorted[3].X, bodyBonesSorted[3].Y), ImColor(255, 255, 255), 1.5f);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bodyBonesSorted[3].X, bodyBonesSorted[3].Y), ImVec2(bodyBonesSorted[2].X, bodyBonesSorted[2].Y), ImColor(255, 255, 255), 1.5f);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bodyBonesSorted[2].X, bodyBonesSorted[2].Y), ImVec2(bodyBonesSorted[1].X, bodyBonesSorted[1].Y), ImColor(255, 255, 255), 1.5f);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bodyBonesSorted[1].X, bodyBonesSorted[1].Y), ImVec2(bodyBonesSorted[0].X, bodyBonesSorted[0].Y), ImColor(255, 255, 255), 1.5f);
										
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bodyBonesSorted[1].X, bodyBonesSorted[1].Y), ImVec2(armBones[0].X, armBones[0].Y), ImColor(255, 255, 255), 1.5f);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bodyBonesSorted[1].X, bodyBonesSorted[1].Y), ImVec2(armBones[1].X, armBones[1].Y), ImColor(255, 255, 255), 1.5f);

										
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(armBones[0].X, armBones[0].Y), ImVec2(handBones[0].X, handBones[0].Y), ImColor(255, 255, 255), 1.5f);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(armBones[1].X, armBones[1].Y), ImVec2(handBones[1].X, handBones[1].Y), ImColor(255, 255, 255), 1.5f);

										Vector3 diameterHead = fixW2Sout(Camera::WorldToScreenPoint(camera, playerPos - Vector3(0,0.5f, 0))) - fixW2Sout(Camera::WorldToScreenPoint(camera, playerPos));
										float radius = diameterHead.Y / 2;
										ImVec2 center(headBone.X, headBone.Y - radius);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bodyBonesSorted[0].X, bodyBonesSorted[0].Y), ImVec2(headBone.X, headBone.Y), ImColor(255, 255, 255), 1.5f);
										ImGui::GetBackgroundDrawList()->AddCircle(center, radius, ImColor(255, 255, 255), 200, 1.f); 
									}

								}
								if (Features::GameplayESP::esphealth) {
									if ((Features::GameplayESP::showenemy && enemy) || (Features::GameplayESP::showteam && !enemy)) {
										float healthPercentage = player_move_c::get_Health(player.get_ref()) / 30.0f; 
										float healthBarHeight = (boxHeight * healthPercentage) * 0.60;
										float healthBarTopY = vBox.Y + boxHeight - healthBarHeight;
										
										DrawESPBox(vBox.X + boxWidth + 4, healthBarTopY, vBox.X + boxWidth + 8, vBox.Y + boxHeight, ImColor(7, 207, 0)); 
									}
								}
								if (Features::GameplayESP::espdistance) {
									if ((Features::GameplayESP::showenemy && enemy) || (Features::GameplayESP::showteam && !enemy)) {
										int distance = Vector3::Distance(Transform::get_Position(transform), localplayer.get_position());
										float baseSize = 20.f;

										std::string DispText = "[" + std::to_string(distance) + "m]";
										ImGui::GetBackgroundDrawList()->AddText(Fonts::Medium, baseSize, ImVec2(vBox.X, vBox.Y - baseSize), ImGui::GetColorU32(espcolor), DispText.c_str());
									}
								}
							}
						}
					} 
				} else {
					fslog::error(OBF("Invalid camera!"));
				}
			}	
		}
		
	}

	if (Features::GameplayESP::esporigin && InappBonusesController::isInMatch()) {
		if (localplayer.get_ref() != nullptr) {
			void* camera = localplayer.get_player_cam();
			if (camera != nullptr) {
				Vector3 worldPos = Vector3(0, 0, 0);
				Vector3 screenpos = fixW2Sout(Camera::WorldToScreenPoint(camera, worldPos));

				ImVec2 startPoint = ImVec2(manager.dxWidth / 2, manager.dxHeight / 2);
				if (manager.dxWidth && manager.dxHeight && screenpos.Z > 1.f) {
					ImVec2 endPoint = ImVec2(screenpos.X, screenpos.Y);
					ImGui::GetBackgroundDrawList()->AddLine(startPoint, endPoint, ImGui::GetColorU32(ImVec4(255, 255, 255, 255)), 1.5f);
				}
			} else {
				fslog::error(OBF("Camera is nullptr"));
			}
		}
	}

	if (!ImguiDX11Manager::instance().menuclosed) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(manager.dxWidth, manager.dxHeight), ImGui::GetColorU32(ImVec4(255, 255, 255, 0.05)));
	}

	if (Features::GameplayESP::showping) {
		int ping;
		if (InappBonusesController::isInMatch()) {
			ping = PhotonNetwork::get_Ping();
		} else {
			ping = 0;
		}
        std::stringstream ss; ss << ping << OBF("ms"); std::string pingStr = ss.str();
		// ImVec2 textSize = espFont->CalcTextSizeA(35, FLT_MAX, 0, pingStr.c_str());
		ImVec2 textPosition(20, manager.dxHeight - 50);
        ImGui::GetBackgroundDrawList()->AddText(Fonts::Medium, 35, textPosition, ImGui::GetColorU32(ImVec4(1, 1, 1, 1)), pingStr.c_str());
	}

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
	ImGui::RenderNotifications();
	ImGui::PopStyleColor(4);

	IL2CPP::Thread::Detach(thread_ref);
}


bool ImguiDX11Manager::get_present_pointer() {
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetForegroundWindow();
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGISwapChain * swap_chain;
	ID3D11Device* device;

	const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		feature_levels,
		2,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		nullptr,
		nullptr) == S_OK) {
		void** p_vtable = *reinterpret_cast<void***>(swap_chain);
		swap_chain->Release();
		device->Release();
		
		this->p_present_target = (present)p_vtable[8];
		return true;
	}
	return false;
}

void ImguiDX11Manager::cleanup() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	if (this->mainRenderTargetView) { this->mainRenderTargetView->Release(); this->mainRenderTargetView = nullptr; }
	if (this->p_context) { this->p_context->Release(); this->p_context = nullptr; }
	if (this->p_device) { this->p_device->Release(); this->p_device = nullptr; }
	SetWindowLongPtr(this->window, GWLP_WNDPROC, (LONG_PTR)this->oWndProc);
}

void ImguiDX11Manager::ProcessKeyInput() {
    if (Variables::listenforkeybind) {
        if (Variables::listenforkeybindMenuToggle) {
            Variables::menuToggleBindKey = OBF("Listening...");
        } else if (Variables::listenforkeybindAimbot) {
            Variables::aimbotbindkey = OBF("Listening...");
        }

        for (int key = 0x08; key <= 0xFF; key++) {
            if (GetAsyncKeyState(key) & 0x8000) {
                if (key == VK_CONTROL) {
                    if (GetKeyState(VK_LCONTROL) & 0x8000) { key = VK_LCONTROL; }
                    if (GetKeyState(VK_RCONTROL) & 0x8000) { key = VK_RCONTROL; }
                }
                if (key == VK_SHIFT) {
                    if (GetKeyState(VK_LSHIFT) & 0x8000) { key = VK_LSHIFT; }
                    if (GetKeyState(VK_RSHIFT) & 0x8000) { key = VK_RSHIFT; }
                }

                if (Variables::listenforkeybindAimbot) {
                    Variables::aimbotbind = key;
                    Variables::aimbotbindkey = GetKeyName(Variables::aimbotbind);
                    Variables::listenforkeybind = false; 
                    Variables::listenforkeybindAimbot = false;
                    config::SaveKeyToJson(OBF("pressedKey"), Variables::aimbotbind);
                } else if (Variables::listenforkeybindMenuToggle) {
                    Variables::menuToggleBind = key;
                    Variables::menuToggleBindKey = GetKeyName(Variables::menuToggleBind);
                    Variables::listenforkeybind = false; 
                    Variables::listenforkeybindMenuToggle = false;
                    config::SaveKeyToJson(OBF("menuToggleKey"), Variables::menuToggleBind);
                }
                break;
            }
        }
    }
}

bool loaded = false;
void saveconfigs() {
	while (true) {
		if (Variables::pixeltimehooked && !loaded && Variables::openMenuYet) {
			config::LoadConfigs();
			fslog::info(OBF("Loaded configs!"));
			ImGui::InsertNotification({ImGuiToastType::Success, 1500, OBF("Loaded configs!")});
			loaded = true;
		}
		if (loaded) {
			config::SaveConfigs();
		}
		Sleep(1000);
	}
}

void pingthread() {
	while (true) {
		auth::pingFREE(authVars::sessionID, authVars::activeCount);
		#ifdef PAIDVERSION
		if (authVars::Login) {
			auth::getActiveUsers(authVars::username, authVars::password, authVars::paidAtiveCount);
		}
		#endif
		Sleep(10000);
	}
}

void mainthread() {
	while (true) {
		auth::checkProxyStatus(authVars::isUsingProxy);
		if (authVars::initiatelogin) {
            #ifdef PAIDVERSION
			auth::niggas(authVars::username, authVars::password, authVars::Login, authVars::statusText, get_AccountID()->ToString().c_str(), get_AccountAuth(get_AuthInstance())->ToString().c_str());
			auth::getInfo(authVars::username, authVars::password, authVars::expirydate);
			authVars::initiatelogin = false;
            #endif
		}
		if (authVars::getnewsletter) {
			authVars::newsletter = auth::get_newsletter();
			std::cout << std::endl;
			fslog::info(OBF("Newsletter:\n  {}"), authVars::newsletter);
			authVars::getnewsletter = false;
		}

		#ifdef PAIDVERSION
		if (authVars::Login && !authVars::logincalled) {
			*(char*)(0) = 1;
		}

		if (authVars::isUsingProxy) {
			ImguiDX11Manager::instance().menuclosed = true;
			ImGui::InsertNotification({ImGuiToastType::Error, 1500, OBF("Disable your proxy to use Asteroid!")});
			// *(char*)(0) = 1;
		}
		#endif
		Sleep(500);
	}
}

long __stdcall detour_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags) {
	ImguiDX11Manager& manager = ImguiDX11Manager::instance();
	if (!manager.init) {
		if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&manager.p_device))) {
			manager.p_device->GetImmediateContext(&manager.p_context);
			DXGI_SWAP_CHAIN_DESC sd;
			p_swap_chain->GetDesc(&sd);
			manager.window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			manager.p_device->CreateRenderTargetView(pBackBuffer, NULL, &manager.mainRenderTargetView);
			pBackBuffer->Release();
			manager.oWndProc = (WNDPROC)SetWindowLongPtr(manager.window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			manager.dxWidth = io.DisplaySize.x;
			manager.dxHeight = io.DisplaySize.y;
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
			ImGui::StyleColorsAsteroid();
			ImGui_ImplWin32_Init(manager.window);
			ImGui_ImplDX11_Init(manager.p_device, manager.p_context);

			ImFontConfig FontConfig;
			FontConfig.PixelSnapH = false;
			FontConfig.OversampleH = 8;
			FontConfig.OversampleV = 8;
			FontConfig.RasterizerMultiply = 1.2f;

			static const ImWchar Ranges[] = {
				0x0020, 0x00FF, // Basic Latin + Latin Supplement
				0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
				0x2DE0, 0x2DFF, // Cyrillic Extended-A
				0xA640, 0xA69F, // Cyrillic Extended-B
				0xE000, 0xE226, // icons
				0,
			};
			FontConfig.GlyphRanges = Ranges;
			
			Fonts::Medium = io.Fonts->AddFontFromMemoryTTF(StolzlMedium, sizeof(StolzlMedium), 15.0f, &FontConfig, Ranges);
			Fonts::Bold = io.Fonts->AddFontFromMemoryTTF(StolzlBold, sizeof(StolzlBold), 17.0f, &FontConfig, Ranges);

			static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
			ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true; icons_config.OversampleH = 8; icons_config.OversampleV = 8;

			Fonts::FontAwesome = io.Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 16.0f, &icons_config, icons_ranges);
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.6f, 1.f);

			// init imgui notify
			float baseFontSize = 16.0f;
			float iconFontSize = baseFontSize * 2.0f / 3.0f;
			static constexpr ImWchar iconsRanges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
			ImFontConfig iconsConfig;
			iconsConfig.MergeMode = true;
			iconsConfig.PixelSnapH = true;
			iconsConfig.GlyphMinAdvanceX = iconFontSize;
			io.Fonts->AddFontFromMemoryCompressedTTF(fa_solid_900_compressed_data, fa_solid_900_compressed_size, iconFontSize, &iconsConfig, iconsRanges);

			boosters[1] = 4;
			manager.init = true;
			Variables::imguiinit = true;
			authVars::sessionID = std::to_string(generateRandomNumber(1, 214847483647));
			
			#ifdef PAIDVERSION
			auth::loadCreds(authVars::usernameBuf, authVars::passwordBuf, 64);
			if (authVars::usernameBuf[0] != '\0' && authVars::passwordBuf[0] != '\0') {
				authVars::username = authVars::usernameBuf;
				authVars::password = authVars::passwordBuf;

				std::string id = get_AccountID()->ToString();
				std::string auth = get_AccountAuth(get_AuthInstance())->ToString();
				
				authVars::initiatelogin = true;
				// auth::niggas(authVars::username, authVars::password, authVars::Login, authVars::statusText, get_AccountID()->ToString().c_str(), get_AccountAuth(get_AuthInstance())->ToString().c_str());
			}
			#endif

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)saveconfigs, 0, 0, 0);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pingthread, 0, 0, 0);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mainthread, 0, 0, 0);
			Variables::aimbotbindkey = GetKeyName(Variables::aimbotbind);
			Variables::menuToggleBindKey = GetKeyName(Variables::menuToggleBind);
		}
		else {
			return manager.p_present(p_swap_chain, sync_interval, flags);
		}
	}

	manager.render();

	return manager.p_present(p_swap_chain, sync_interval, flags);
}

inline void cursorfix::keep_mouse_inmiddle() {
	while (ImguiDX11Manager::instance().menuclosed) {
		HWND foreground_window = GetForegroundWindow();
		char window_title[256];
		GetWindowTextA(foreground_window, window_title, sizeof(window_title));
		if (strcmp(window_title, OBF("Pixel Gun 3D")) == 0) SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
		else ClipCursor(NULL);

		Sleep(50);
	}
}
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	ImguiDX11Manager& manager = ImguiDX11Manager::instance();
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		if (uMsg == WM_MOUSEMOVE || uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP || uMsg == WM_MOUSEWHEEL) {
			return true;
		}
		else {
			return CallWindowProc(manager.oWndProc, hWnd, uMsg, wParam, lParam);
		}
	}
#define ImGuiConfigFlags_NoKeyboard 0x0002
	switch(uMsg) {
	case WM_KEYDOWN:		
		if (((GetAsyncKeyState(VK_LCONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000))) {
			ClearConsole();
			ImGui::InsertNotification({ImGuiToastType::Success, 1500, OBF("Console cleared!")});
		}
		if (GetAsyncKeyState(Variables::aimbotbind) & 0x8000) {
			Features::GameplayAimbot::aimbot = !Features::GameplayAimbot::aimbot;
		}
		if (
			(GetAsyncKeyState(Variables::menuToggleBind) & 0x8000) || // main toggle, defaults to right ctrl
			((GetAsyncKeyState(VK_LCONTROL) & 0x8000) && (GetAsyncKeyState(VK_DELETE) & 0x8000)) || // l ctrl + insert
			((GetAsyncKeyState(VK_LCONTROL) & 0x8000) && (GetAsyncKeyState(VK_INSERT) & 0x8000)) || // l ctrl + insert
			(GetAsyncKeyState(VK_F11) & 0x8000) // f11
			&& !authVars::isUsingProxy
		) {
			Variables::openMenuYet = true;
			manager.menuclosed = !manager.menuclosed;
			ImGuiIO& io = ImGui::GetIO();
			manager.dxWidth = io.DisplaySize.x; Variables::dxwidth = io.DisplaySize.x;
			manager.dxHeight = io.DisplaySize.y; Variables::dxheight = io.DisplaySize.y;
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)cursorfix::keep_mouse_inmiddle, 0, 0, 0);
			if (!manager.menuclosed) {
				io.MouseDrawCursor = false;
				ShowCursor(TRUE);
				io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
				io.ConfigFlags &= ~ImGuiConfigFlags_NoKeyboard;
				ClipCursor(NULL);
			}
			else {
				ClipCursor(NULL);
				io.MouseDrawCursor = false;
				io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
				while (ShowCursor(false) >= 0);
				io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
				io.ConfigFlags |= ImGuiConfigFlags_NoKeyboard;
				ReleaseCapture();
			}
			return true;
		}
		break;
	}
	if (manager.menuclosed) return CallWindowProc(manager.oWndProc, hWnd, uMsg, wParam, lParam);
	else {
		ShowCursor(TRUE);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}