#include "Hooks.h"


void (*Hooks::old_WeaponSounds)(void*) = nullptr;
void Hooks::WeaponSounds(void* instance) {
	if (localplayer.get_ref() != nullptr) {
    if (Features::GameplayMain::polymorph) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "polymorpher")) = OBF(true);
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "polymorphDuarationTime")) = 999999.f;	
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "polymorphMaxHealth")) = 999999.f;
        *(int*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "polymorphType")) = 0;
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "harpoon")) = OBF(true);
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "harpoonMaxDistance")) = 99999.f;
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "harpoonMinDistance")) = 99999.f;
    }

    if (Features::GameplayMain::silentaim) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isRoundMelee")) = OBF(true);
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "radiusRoundMelee")) = INFINITY;
    }

    if (Features::GameplayMain::killpoints) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isBuffPoints")) = OBF(true);
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "buffPointsRevenge")) = 1000;
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "buffBonusPointsForKill")) = 1000;
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "buffBonusPointsForAssist")) = 1000;
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "buffPointsAssistDesigner")) = 1000;
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "buffPointsOther")) = 1000;
    }

    if (Features::GameplayMain::doublejump) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isDoubleJump")) = OBF(true);
    }

    if (Features::GameplayMain::jetpack) {
        if (localplayer.get_ref() != nullptr && delayTime % 120 == 0) {
            player_move_c::set_Jetpack(localplayer.get_ref(), true);
        }
    } else {	
        if (localplayer.get_ref() != nullptr && delayTime % 120 == 0) {
            player_move_c::set_Jetpack(localplayer.get_ref(), false);
        }
    }

    if (Features::GameplayMain::xray) {
        if (localplayer.get_ref() != nullptr && delayTime % 120 == 0) {
            player_move_c::set_Xray(localplayer.get_ref(), true);
        }
    } else {
        if (localplayer.get_ref() != nullptr && delayTime % 120 == 0) {
            player_move_c::set_Xray(localplayer.get_ref(), false);
        }
    }

    if (Features::GameplayBullet::shootlaser) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "railgun")) = OBF(true);
    }
    if (Features::GameplayBullet::shootrocket) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "bazooka")) = OBF(true);
    }
    if (Features::GameplayBullet::shootshotgun) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isShotgun")) = OBF(true);
    }
    if (Features::GameplayBullet::shootdash) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isDash")) = OBF(true);
    }
    if (Features::GameplayBullet::shootharpoon) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "harpoon")) = OBF(true);
    }
    if (Features::GameplayBullet::shootexplodingbullet) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "bulletExplode")) = OBF(true);
    }
    if (Features::GameplayWeapon::quickscope) {
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "scopeSpeed")) = 10000;
    }

    if (Features::GameplayEffects::stackingblindness) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isBlindEffect")) = OBF(true);
        *(int*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "blindEffect")) = generateRandomNumber(0, 60);
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isBlindEffectTime")) = 9999;
    }

	if (Features::GameplayEffects::charm) {
		*(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isCharm")) = OBF(true);
	}

	if (Features::GameplayEffects::electricshock) {
		*(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isElectricShock")) = OBF(true);
		*(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "electricShockCoeff")) = 9999;
		*(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "electricShockTime")) = 9999;
	}
	if (Features::GameplayMain::infammo) {
		*(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isUnlimitedAmmo")) = OBF(true);
	}
    if (Features::GameplayWeapon::nospread) {
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "maxKoofZoom")) = 0;//maxKoofZoom
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "upKoofFireZoom")) = 0;//upKoofFireZoom
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "downKoofFirstZoom")) = 0;//downKoofFirstZoom
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "downKoofZoom")) = 0;//downKoofZoom
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "maxKoof")) = 0;//maxKoof
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "tekKoof")) = 0;//tekKoof
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "upKoofFire")) = 0;//upKoofFire
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "downKoofFirst")) = 0;//downKoofFirst
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "downKoof")) = 0;//downKoof
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "timerForTekKoofVisual")) = 0;//timerForTekKoofVisual
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "timerForTekKoofVisualByFireRate")) = 0;//timerForTekKoofVisualByFireRate
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "timeForTekKoofVisual")) = 0;//timeForTekKoofVisual
        *(Vector2*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "startZone")) = Vector2(0, 0);//startZone
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "recoilCoeffZoom")) = 0;//recoilCoeffZoom
    }
	if (Features::GameplayBullet::ignoreshield) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "ignoreSlyWolf")) = true;
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "ignoreReflector")) = true;
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "ignoreBarrier")) = true;
	}
	if (Features::GameplayMain::headmagnify) {
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "isHeadMagnifier")) = true;
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "headMagnifierTime")) = 99999;
	}
	if (Features::GameplayMain::enemymarker) {
        *(float*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "enemyMarketChargeTime")) = 0;
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "enemyMarker")) = true;
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "enemyMarkerWhenShot")) = true;
        *(bool*)((uint64_t) instance + GET_FIELDOFFSET("WeaponSounds", "enemyMarkerWhenAiming")) = true;
	}

	}

    roundedfps = std::round(1.0f / get_DeltaTime());
	Variables::wepsoundshooked = true;
	delayTime++;
	if (delayTime >= 2147482640) {
		delayTime = 0;
	}
    Hooks::old_WeaponSounds(instance);
}

int Hooks::random = 0;
void (*Hooks::old_Player_move_c)(void*) = nullptr;
void Hooks::Player_move_c(void* instance) {
    if (Features::GameplayMain::emojispam && localplayer.get_ref() != nullptr) {
        static bool sent = false;
        static int counter = 0;
        if (delayTime % roundedfps == 0) {
            if (!sent) {
                player_move_c::SendChat(localplayer.get_ref(), NewIl2cppString(""), false, NewIl2cppString(emojiList[generateRandomNumber(1, IM_ARRAYSIZE(emojiList))]));
                sent = OBF(true);
            }
        } else {
            sent = false;
        }
        if (counter > 0 && delayTime % roundedfps != 0) {
            counter = 0;
        }
    }

    if (Features::GameplayTroll::chatspam && localplayer.get_ref() != nullptr) {
        static bool sent = false;
        static int counter = 0;
        std::string chatspamtxt = Features::GameplayTroll::chatspamBuf;
        if (chatspamtxt != "") {
            if (delayTime % roundedfps == 0) {
                if (!sent) {
                    player_move_c::SendChat(localplayer.get_ref(), NewIl2cppString(chatspamtxt.c_str()), false, NewIl2cppString(""));
                    sent = OBF(true);
                }
                counter++;
            } else {
                sent = false;
            }
        }
        if (counter > 0 && delayTime % roundedfps != 0) {
            counter = 0;
        }
    }

    if (Features::GameplayMain::killall) {
        if (localplayer.get_ref() != nullptr && !playerList.empty()) {
            for (int i = 1; i < playerList.size(); i++) {
                Player player = playerList[i];
                if (player.get_ref() != nullptr && !player.is_mine()) {
                    bool enemy = PlayerDamageable::isEnemyTo(player.get_playerdamagable(), localplayer.get_ref());
                    void* pDamageable = player.get_playerdamagable();
                    bool dead = PlayerDamageable::isDead(pDamageable);
                    if (enemy && !dead && pDamageable != nullptr) {
                        void* bodyAimCollider =  *(void**)((uint64_t) player.get_ref() + GET_FIELDOFFSET("Player_move_c", "_bodyAimCollider"));
                        Vector3 pos = player.get_position();
                        Hooks::ApplyDamage(pDamageable, 50.0f, nullptr, bodyAimCollider, pos, nullptr, nullptr, NewIl2cppString("ultimatum"), 3002, nullptr);
                        
                    }
                }
            }
        }
    }

    if (Features::GameplayTroll::masskill) {
        if (localplayer.get_ref() != nullptr && !playerList.empty()) {
            for (int i = 1; i < playerList.size(); i++) {
                Player player = playerList[i];
                if (player.get_ref() != nullptr && !player.is_mine()) {
                    bool enemy = PlayerDamageable::isEnemyTo(player.get_playerdamagable(), localplayer.get_ref());
                    bool meDead = PlayerDamageable::isDead(localplayer.get_playerdamagable());
                    if (enemy && !meDead) {
                        void* pTransform = player.get_transform();
                        void* transform = Component::get_Transform(pTransform);
                        Transform::set_Position(transform, localplayer.get_position() + Vector3(0, 0, 2));
                    }
                }
            }
        }
    }

    if (Features::GameplayTroll::telekill) {
        if (localplayer.get_ref() != nullptr && !playerList.empty()) {
            for (int i = 1; i < playerList.size(); i++) {
                Player player = playerList[i];
                if (player.get_ref() != nullptr && !player.is_mine()) {
                    bool enemy = PlayerDamageable::isEnemyTo(player.get_playerdamagable(), localplayer.get_ref());
                    bool dead = PlayerDamageable::isDead(player.get_playerdamagable());
                    if (enemy && !dead) {
                        void* pTransform = player.get_transform();
                        Transform::set_Position(localplayer.get_transform(), player.get_position() + Vector3(0, 0, 1));
                    }
                }
            }
        }
    }

    if (Features::GameplayTroll::middleclicktp) {
        if (UInput::GetMouseButtonDown(2) && localplayer.get_ref() != nullptr) {
            void* camera = localplayer.get_player_cam();
            void* baseCamTransform = localplayer.get_basecam_transform();
            if (camera != nullptr && baseCamTransform != nullptr) {
                Vector3 camPos = Transform::get_Position(baseCamTransform); 
                Vector3 dir = Transform::get_forward(baseCamTransform);
                void* hitInfo = new RaycastHit; 
                bool hit = Physics::Raycast(camPos, dir, hitInfo);
                bool dead = PlayerDamageable::isDead(localplayer.get_playerdamagable());
                if (hit && !dead) {
                    Vector3 hitPoint = *(Vector3*)((uintptr_t)hitInfo);
                    if (hitPoint.Y < 0.01) hitPoint.Y = 1;
                    if (hitPoint.Y > 10000) hitPoint.Y = localplayer.get_position().Y;
                    localplayer.set_position(hitPoint);
                }
                delete hitInfo;
            }
        }
    }

	if (Features::GameplayAimbot::aimbot) {
		if (localplayer.get_ref() != nullptr && !playerList.empty() && ticksSinceMatchStart > roundedfps) {
			for (int i = 1; i < playerList.size(); i++) {
				Player player = playerList.at(i);
				void* myDamageable = localplayer.get_playerdamagable();
				void* enemyDamageable = player.get_playerdamagable();
				void* _enemyTransform = player.get_transform();
				void* _myTransform = localplayer.get_transform();;
				if (!myDamageable && !enemyDamageable || !_enemyTransform || !_myTransform || !player.get_ref()) continue;
				if ((!PlayerDamageable::isEnemyTo(myDamageable, player.get_ref()) && !Features::GameplayMain::friendlyfire) || PlayerDamageable::isDead(enemyDamageable)) continue;
				ImGuiIO& io = ImGui::GetIO();
				void* myTransform = Component::get_Transform(_myTransform);
				void* enemyTransform = Component::get_Transform(_enemyTransform);

				Vector3 enemyPos;

				Vector3 myPos = localplayer.get_position(); // Transform::get_Position(myTransform);
				switch (aimatParts[100]) {
					case 0: enemyPos = Transform::get_Position(enemyTransform); break; // head
					case 1: enemyPos = Transform::get_Position(enemyTransform) - Vector3(0, 0.7, 0); break; // body
					case 2: enemyPos = Transform::get_Position(enemyTransform) - Vector3(0, 1.5, 0); break; // feet
					case 3: // random
						if (delayTime % (roundedfps * 2) == 0) {
							random = generateRandomNumber(0, 2);
						}
						if (random == 0) {
							enemyPos = Transform::get_Position(enemyTransform);
						} else if (random == 1) {
							enemyPos = Transform::get_Position(enemyTransform) - Vector3(0, 0.7, 0);
						} else if (random == 2) {
							enemyPos = Transform::get_Position(enemyTransform) - Vector3(0, 1.5, 0);
						}
						break;
					default: enemyPos = Transform::get_Position(enemyTransform); break; // head
				}
				Vector3 enemyHeadPos = enemyPos + Vector3(0, 1, 0);
						
				void* camera = localplayer.get_player_cam();
				if (!camera) continue;
				Vector3 enemyScreenPos = utilsFixW2Sout(Camera::WorldToScreenPoint(camera, enemyPos), Variables::dxheight);
							
				void* baseCamTransform = localplayer.get_basecam_transform();
				Quaternion myBCRot = Transform::get_rotation(baseCamTransform);
				Quaternion myTransRot = Transform::get_rotation(myTransform);
							
				Vector3 localEnemyVector = toLocalSpace(enemyPos-myPos, myBCRot);
							
				float distanceVec = std::sqrt(localEnemyVector.X * localEnemyVector.X + localEnemyVector.Z * localEnemyVector.Z);
							
				float deltaYaw = (std::atan2(localEnemyVector.X, localEnemyVector.Z));
				float deltaPitch = (std::atan2(localEnemyVector.Y, distanceVec));

				Vector3 newEulerBC = addRotationRad(Quaternion::ToEuler(myBCRot) , -(deltaPitch), 0.f, 0.f);
				Vector3 newEulerTrans = addRotationRad(Quaternion::ToEuler(myTransRot), 0.f, deltaYaw, 0.f);

				Quaternion newBCRot = Quaternion::FromEuler(newEulerBC);
				Quaternion newTransRot = Quaternion::FromEuler(newEulerTrans);
							
				float screenDistance2Middle = sqrt(pow((enemyScreenPos.X - (Variables::dxwidth / 2)), 2) + pow((enemyScreenPos.Y - (Variables::dxheight / 2)), 2));
							
				if (screenDistance2Middle <= Features::GameplayAimbot::fovsize && enemyScreenPos.Z >= 1) {
					if (!Features::GameplayAimbot::visibilitycheck) {
						if (Features::GameplayAimbot::smoothing) {
							Quaternion smoothedBCRot = Quaternion::Slerp(myBCRot, newBCRot, 1.0001f - Features::GameplayAimbot::smoothingamount);
							Quaternion smoothedTransRot = Quaternion::Slerp(myTransRot, newTransRot, 1.0001f - Features::GameplayAimbot::smoothingamount);
							if (Features::GameplayAimbot::leftclicktrigger && GetAsyncKeyState(VK_LBUTTON)) {
								Transform::set_rotation(baseCamTransform, smoothedBCRot);
								Transform::set_rotation(myTransform, smoothedTransRot);
							} else if (!Features::GameplayAimbot::leftclicktrigger) {
								Transform::set_rotation(baseCamTransform, smoothedBCRot);
								Transform::set_rotation(myTransform, smoothedTransRot);
							}
						} else {
							if (Features::GameplayAimbot::leftclicktrigger && GetAsyncKeyState(VK_LBUTTON)) {
								Transform::set_rotation(baseCamTransform, newBCRot);
								Transform::set_rotation(myTransform, newTransRot);
							} else if (!Features::GameplayAimbot::leftclicktrigger) {
								Transform::set_rotation(baseCamTransform, newBCRot);
								Transform::set_rotation(myTransform, newTransRot);
							}
						}
					} else {
						if (player_move_c::isVisible(localplayer.get_ref(), enemyPos)) {
							if (Features::GameplayAimbot::smoothing) {
								Quaternion smoothedBCRot = Quaternion::Slerp(myBCRot, newBCRot, 1.0001f - Features::GameplayAimbot::smoothingamount);
								Quaternion smoothedTransRot = Quaternion::Slerp(myTransRot, newTransRot, 1.0001f - Features::GameplayAimbot::smoothingamount);
								if (Features::GameplayAimbot::leftclicktrigger && GetAsyncKeyState(VK_LBUTTON)) {
									Transform::set_rotation(baseCamTransform, smoothedBCRot);
									Transform::set_rotation(myTransform, smoothedTransRot);
								} else if (!Features::GameplayAimbot::leftclicktrigger) {
									Transform::set_rotation(baseCamTransform, smoothedBCRot);
									Transform::set_rotation(myTransform, smoothedTransRot);
								}
							} else {
								if (Features::GameplayAimbot::leftclicktrigger && GetAsyncKeyState(VK_LBUTTON)) {
									Transform::set_rotation(baseCamTransform, newBCRot);
									Transform::set_rotation(myTransform, newTransRot);
								} else if (!Features::GameplayAimbot::leftclicktrigger) {
									Transform::set_rotation(baseCamTransform, newBCRot);
									Transform::set_rotation(myTransform, newTransRot);
								}
							}
						}
					}
				}
			}
		}
	}

    Player inst = Player(instance);
    if (inst.is_mine()) {
        localplayer = inst;
		if (Features::GameplayMain::godmode) {
			player_move_c::set_Health(localplayer.get_ref(), 99999.f);
		}
    }

    Hooks::old_Player_move_c(instance);
}

void* (*Hooks::old_PMC)(void*) = nullptr;
void* Hooks::PMC(void* instance) {
	bool found = false;
	for (int i = 0; i < playerList.size(); i++) {
		if (playerList[i].get_ref() == instance) {
			found = OBF(true); break; 
		}
	}
	if (!found) {
		playerList.push_back(Player(instance));
	}
    return Hooks::old_PMC(instance);
}

void (*Hooks::old_destructPMC)(void*) = nullptr;
void Hooks::destructPMC(void* instance) {
	for (int i = 0; i < playerList.size(); i++) {
		if (playerList[i].get_ref() == instance) {
			playerList.erase(playerList.begin() + i);
		}
	}
    Hooks::old_destructPMC(instance);
}

void (*Hooks::old_PixelTime)(void*) = nullptr;
void Hooks::PixelTime(void* instance) {
    AnalyticsParams2 emptyParams{ 0, 0,  0,  0, 0, 0, 0,  false, nullptr, 0, false, 1, nullptr, false, 0, NewIl2cppString(""), nullptr};
	AnalyticsParams2 pixelpassParams{ 0, 0x67, 0x7, 0, 0x2E, 0, 0xD,  false, nullptr, 0, false, 0, nullptr, false, 0, NewIl2cppString(""), nullptr };
	AnalyticsParams2 couponParams{ 0, 0x22, 0, 0, 0, 0, 0, false, nullptr, 0, false, 0, nullptr, false, 0, NewIl2cppString(""), nullptr };
	AnalyticsParams2 silverParams{ 0, 0x79, 0x6, 0, 0x16, 0, 0,  false, nullptr, 0, false, 0, nullptr, false, 0, NewIl2cppString(""), nullptr };
	AnalyticsParams2 clanscParams{ 0, 0x34, 0, 0, 0, 0, 0x5, false, nullptr, 0, false, 0, nullptr, false, 0, NewIl2cppString(""), nullptr };
	AnalyticsParams2 wearParams{ 0, 0, 0, 0, 0, 0x3, 0x12, false, nullptr, 0, false, 0, nullptr, false, 0, NewIl2cppString(""), nullptr };

	//fslog::debug("Adding coins: {}", Features::Account::isAddingCoins);
    if (Features::Account::isAddingCoins) {
		if (!Features::Account::collectibles)
			ProgressUpdater::addCurrency2(ProgressUpdater::get_Instance(), NewIl2cppString(OBF("Coins")), Features::Account::currencyAmount, 0x67, true, false, pixelpassParams);
		Features::Account::isAddingCoins = false;
    }

    if (Features::Account::isAddingGems) {
		if (!Features::Account::collectibles)
			ProgressUpdater::addCurrency2(ProgressUpdater::get_Instance(), NewIl2cppString(OBF("GemsCurrency")), Features::Account::currencyAmount, 0x67, true, false, pixelpassParams);
		Features::Account::isAddingGems = false;
    }
	if (Features::Account::isAddingPPTickets) {
		if (!Features::Account::collectibles)
			ProgressUpdater::addCurrency2(ProgressUpdater::get_Instance(), NewIl2cppString(OBF("PixelPassCurrency")), Features::Account::currencyAmount, 0x67, true, false, pixelpassParams);
		Features::Account::isAddingPPTickets = false;
	}
	if (Features::Account::isAddingSilver) {
		if (!Features::Account::collectibles)
			ProgressUpdater::addCurrency2(ProgressUpdater::get_Instance(), NewIl2cppString(OBF("ClanSilver")), Features::Account::currencyAmount, 0x79, true, false, silverParams);
		Features::Account::isAddingSilver = false;
	}
	if (Features::Account::isAddingKeys) {
		if (!Features::Account::collectibles)
			BankController::addKeys(Features::Account::currencyAmount, true, 0, NewIl2cppString(""), false, 0x3);
		Features::Account::isAddingKeys = false;	
	}
	if (Features::Account::isAddingCoupons) {
		if (!Features::Account::collectibles)
			ProgressUpdater::addCurrency2(ProgressUpdater::get_Instance(), NewIl2cppString(OBF("Coupons")), Features::Account::currencyAmount, 0x22, true, false, couponParams);
		Features::Account::isAddingCoupons = false;
	}
	if (Features::Account::isAddingNoviceChest) {
		ProgressUpdater::addChest(ProgressUpdater::get_Instance(), 1, 0, Features::Account::currencyAmount, 0, emptyParams);
		Features::Account::isAddingNoviceChest = false;
	}
	if (Features::Account::isAddingFighterChest) {
		ProgressUpdater::addChest(ProgressUpdater::get_Instance(), 2, 0, Features::Account::currencyAmount, 0, emptyParams);
		Features::Account::isAddingFighterChest = false;
	}
	if (Features::Account::isAddingWinnerChest) {
		ProgressUpdater::addChest(ProgressUpdater::get_Instance(), 3, 0, Features::Account::currencyAmount, 0, emptyParams);
		Features::Account::isAddingWinnerChest = false;
	}
	if (Features::Account::isAddingClanSCPoints) {
		if (!Features::Account::collectibles)
			ProgressUpdater::addCurrency2(ProgressUpdater::get_Instance(), NewIl2cppString(OBF("ClanLootBoxPoints")), Features::Account::currencyAmount, 0x34, true, false, clanscParams);
		Features::Account::isAddingClanSCPoints = false;
	}
    
    if (Features::Account::isAddingArmor) {
        fslog::debug("Adding armor");
		for (int i = 0; i < 29; i++) {
			ProgressUpdater::addArmor(ProgressUpdater::get_Instance(), ptrwearIndex(NewIl2cppString(armorList[i])), (int*)(ExperienceController::get_CurrentLevel()), NewIl2cppString(OBF("migr")), wearParams);
            //NewIl2cppString("test");
            fslog::info(OBF("Added {} / {} armor: {}"), i+1, IM_ARRAYSIZE(armorList), armorList[i]);
		}
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all armors!"), ICON_FA_PLUS});
        Features::Account::isAddingArmor = false;
    }

    if (Features::Account::isAddingHats) {
		for (int i = 0; i < IM_ARRAYSIZE(hatList); i++) {
			addWear((int *) (6), NewIl2cppString(hatList[i]));
			fslog::info(OBF("Added {} / {} hats: {}"), i+1, IM_ARRAYSIZE(hatList), hatList[i]);
		}
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all hats!"), ICON_FA_PLUS});
        Features::Account::isAddingHats = false;
    }

    if (Features::Account::isAddingMasks) {
        for (int i = 0; i < 39; i++) {
            addWear((int *) (12), NewIl2cppString(maskList[i]));
			fslog::info(OBF("Added {} / {} masks: {}"), i+1, IM_ARRAYSIZE(maskList), maskList[i]);
        }
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all masks!"), ICON_FA_PLUS});
		Features::Account::isAddingMasks = false;
    }

    if (Features::Account::isAddingSkins) {
		for (int i = 0; i < IM_ARRAYSIZE(skinList); i++) {
			addRoyaleItem(NewIl2cppString(skinList[i]), (bool *) (true), wearParams);
			fslog::info(OBF("Added {} / {} skins: {}"), i+1, IM_ARRAYSIZE(skinList), skinList[i]);
		}
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all skins!"), ICON_FA_PLUS});
        Features::Account::isAddingSkins = false;
    }

    if (Features::Account::isAddingCapes) {
    	for (int i = 0; i < IM_ARRAYSIZE(capeList); i++) {
    	    addWear((int *) (9), NewIl2cppString(capeList[i]));
			fslog::info(OBF("Added {} / {} capes: {}"), i+1, IM_ARRAYSIZE(capeList), capeList[i]);
    	}
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all capes!"), ICON_FA_PLUS});
        Features::Account::isAddingCapes = false;
    }

    if (Features::Account::isAddingBoots) {
        for (int i = 0; i < IM_ARRAYSIZE(bootsList); i++) {
            addWear((int *) (10), NewIl2cppString(bootsList[i]));
			fslog::info(OBF("Added {} / {} boots: {}"), i+1, IM_ARRAYSIZE(bootsList), bootsList[i]);
        }
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all boots!"), ICON_FA_PLUS});
        Features::Account::isAddingBoots = false;
    }

    if (Features::Account::isAddingGadgets) {
		for (int i = 0; i < IM_ARRAYSIZE(gadgetList); i++) {
			GadgetClass::addGadget(NewIl2cppString(gadgetList[i]), (int*)(ExperienceController::get_CurrentLevel()));
			fslog::info(OBF("Added {} / {} gadgets: {}"), i+1, IM_ARRAYSIZE(gadgetList), gadgetList[i]);
		}
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all gadgets!"), ICON_FA_PLUS});
        Features::Account::isAddingGadgets = false;
    }

	if (Features::Account::isAddingPets) {
		for (int i = 0; i < IM_ARRAYSIZE(petsList); i++) {
			InappBonusesController::addPet(NewIl2cppString(petsList[i]), (int*)(500));
			fslog::info(OBF("Added {} / {} pets: {}"), i+1, IM_ARRAYSIZE(petsList), petsList[i]);
		}
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all pets!"), ICON_FA_PLUS});
		Features::Account::isAddingPets = false;
	}
	if (Features::Account::isAddingCars) {
		for (int i = 0; i < 45; i++) {
			 addRoyaleItem(NewIl2cppString(carList[i]), (bool *) (true), wearParams);
			fslog::info(OBF("Added {} / {} cars"), i+1, IM_ARRAYSIZE(carList));
		}
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all cars!"), ICON_FA_PLUS});
		Features::Account::isAddingCars = false;
	}
	if (Features::Account::isAddingGliders) {
		for (int i = 0; i < 105; i++) {
			addRoyaleItem(NewIl2cppString(gliderList[i]), (bool *) (true), wearParams);
			fslog::info(OBF("Added {} / {} gliders"), i+1, IM_ARRAYSIZE(gliderList));
		}
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all gliders!"), ICON_FA_PLUS});
		Features::Account::isAddingGliders = false;
	}
	if (Features::Account::isAddingLobbyItems) {
		for (int i = 0; i <= IM_ARRAYSIZE(lobbyItemList); i++) {
			InappBonusesController::addLobbyItem(NewIl2cppString(lobbyItemList[i]));
			fslog::info(OBF("Added: {} / {} lobby items"), i + 1, IM_ARRAYSIZE(lobbyItemList));
		}
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all lobby items!"), ICON_FA_PLUS});
		Features::Account::isAddingLobbyItems = false;
	}
	if (Features::Account::isAddingVeterenSet) {
		ProgressUpdater::addArmor(ProgressUpdater::get_Instance(), ptrwearIndex(NewIl2cppString(OBF("armor_veteran"))), (int*)(ExperienceController::get_CurrentLevel()), NewIl2cppString(OBF("migr")), wearParams);
		addWear((int *) (12), NewIl2cppString(OBF("mask_veteran")));
		addWear((int *) (9), NewIl2cppString(OBF("cape_veteran")));
		addWear((int *) (10), NewIl2cppString(OBF("boots_veteran")));
		addWear((int *) (6), NewIl2cppString(OBF("hat_veteran")));
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all veteren wear!"), ICON_FA_PLUS});
		Features::Account::isAddingVeterenSet = OBF(false);
	}
	if (Features::Account::isAddingUnknownSkin) {
		addRoyaleItem(NewIl2cppString(OBF("avatar_unknown")), (bool *) (true), wearParams);
		ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added unknown skin!"), ICON_FA_PLUS});
		Features::Account::isAddingUnknownSkin = false;
	}

	if (Features::Account::isAddingIndividual) {
		if (selectedAdderTypeIndex == 0) { // wear
			if (wearTypeIndex == 0) { // Hat
				addWear((int *) (6), NewIl2cppString(hatList[selectedItemIndex]));
				ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added hat: %s",ICON_FA_PLUS , hatList[selectedItemIndex]});
			} else if (wearTypeIndex == 1) { // mask
				addWear((int *) (12), NewIl2cppString(maskList[selectedItemIndex]));
				ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added mask: %s",ICON_FA_PLUS , maskList[selectedItemIndex]});
			} else if (wearTypeIndex == 2) { /// cape
				addWear((int *) (9), NewIl2cppString(capeList[selectedItemIndex]));
				ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added cape: %s",ICON_FA_PLUS , capeList[selectedItemIndex]});
			} else if (wearTypeIndex == 3) { // boots
				addWear((int *) (10), NewIl2cppString(bootsList[selectedItemIndex]));
				ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added boot: %s",ICON_FA_PLUS , bootsList[selectedItemIndex]});
			}
		} else if (selectedAdderTypeIndex == 1) {// armor
			ProgressUpdater::addArmor(ProgressUpdater::get_Instance(), ptrwearIndex(NewIl2cppString(armorList[selectedItemIndex])), (int*)(ExperienceController::get_CurrentLevel()), NewIl2cppString(OBF("migr")), wearParams);
			ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added armor: %s",ICON_FA_PLUS , armorList[selectedItemIndex]});
		} else if (selectedAdderTypeIndex == 2) { // skin
			addRoyaleItem(NewIl2cppString(skinList[selectedSkinIndex]), (bool *) (true), wearParams);
			ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added skin: %s",ICON_FA_PLUS , skinList[selectedSkinIndex]});
		} else if (selectedAdderTypeIndex == 3) { // gadget
			GadgetClass::addGadget(NewIl2cppString(gadgetList[selectedItemIndex]), (int*)(ExperienceController::get_CurrentLevel())); 
			ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added gadget: %s",ICON_FA_PLUS , gadgetList[selectedItemIndex]});
		} else if (selectedAdderTypeIndex == 4) { // pet
			InappBonusesController::addPet(NewIl2cppString(petsList[selectedPetIndex]), (int*)(500)); 
			ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added pet: %s",ICON_FA_PLUS , petsList[selectedPetIndex]});
		} else if (selectedAdderTypeIndex == 5) { // lobby
			InappBonusesController::addLobbyItem(NewIl2cppString(lobbyItemList[selectedLobbyIndex]));
			ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added lobby item: %s",ICON_FA_PLUS , lobbyItemList[selectedLobbyIndex]});
		}
		Features::Account::isAddingIndividual = false;
	}

	if (Features::Account::addCustomWepRange) { 
		// #ifdef PAIDVERSION
		// wsm.add_weapons_ranged(Features::Account::addWeaponStartRange, Features::Account::addWeaponEndRange, ExperienceController::get_CurrentLevel());
		// wsm.reloadws();
		// ImGui::InsertNotification({ImGuiToastType::Success, 1500, OBF("%s [WebSocket] Added weapons from %d-%d"), ICON_FA_PLUS, Features::Account::addWeaponStartRange, Features::Account::addWeaponEndRange});
		// #else
		for (int i = Features::Account::addWeaponStartRange; i <= Features::Account::addWeaponEndRange; i++) {
			void* itemrecord = getItemRecord(NewIl2cppString(weaponList[i]));
			if (itemrecord != nullptr) {
				InappBonusesController::AddWeapon(NewIl2cppString(weaponList[i]), true, true);
				fslog::info(OBF("added: {} / {} - {}"), i, Features::Account::addWeaponEndRange, weaponList[i]);
			} else {
				fslog::error(OBF("Failed to add: {}"), weaponList[i]);
			}
		}
		ImGui::InsertNotification({ImGuiToastType::Success, 1500, OBF("%s Added weapons from %d-%d"), ICON_FA_PLUS, Features::Account::addWeaponStartRange, Features::Account::addWeaponEndRange});
		// #endif
		Features::Account::addCustomWepRange = false;
	}

    if (Features::Account::addCustomWep) {
		std::string nigga = Features::Account::addwepBuf;
		void* itemrecord = getItemRecord(NewIl2cppString(nigga.c_str()));
		if (itemrecord != nullptr) {
			// #ifdef PAIDVERSION
			// wsm.add_weapon(ItemRecord::get_Index(itemrecord), ExperienceController::get_CurrentLevel());
			// wsm.reloadws();
			// ImGui::InsertNotification({ImGuiToastType::Success, 1500, OBF("%s [WebSocket] Added weapon: %s"), ICON_FA_PLUS , nigga.c_str()});
			// #else
			InappBonusesController::AddWeapon(NewIl2cppString(nigga.c_str()), true, true);
			ImGui::InsertNotification({ImGuiToastType::Success, 1500, "%s Added weapon: %s",ICON_FA_PLUS , nigga.c_str()});
			// #endif
		} else {
			ImGui::InsertNotification({ ImGuiToastType::Success, 2000, OBF("Sent Request: %s", "Get Player Info by ID")});
			ImGui::InsertNotification({ImGuiToastType::Error, 1500, OBF("%s Invalid weapon: %s!"),ICON_FA_TRIANGLE_EXCLAMATION , nigga.c_str()});
		}
        Features::Account::addCustomWep = false;
    }



	if (wsm.get_wsmi()) {
		if (Features::Account::addwepskins) {
			wsm.add_wepskins(0);
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all weapon skins!"), ICON_FA_PLUS});
			Features::Account::addwepskins = false;
		}

		if (Features::Account::addallmodules) {
			wsm.add_modules(0);
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all modules!"), ICON_FA_PLUS});
			Features::Account::addallmodules = false;
		}
		if (Features::Account::upgradeallmodules) {
			wsm.upgrade_modules(0);
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Upgraded all modules!"), ICON_FA_ARROW_UP});
			Features::Account::upgradeallmodules = false;
		}
		if (Features::Account::addboosters) {
			wsm.add_boosters(Features::Account::boostersAmount, boosters[1]);
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added %d %s"), ICON_FA_PLUS, Features::Account::boostersAmount, boosterscombo[boosters[1]]});
			Features::Account::addboosters = false;
		}

		if (Features::Account::addgrafiti) {
			wsm.add_grafitis(0);
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all grafitis!"), ICON_FA_PLUS});
			Features::Account::addgrafiti = false;
		}

		if (Features::Account::addallwepparts) {
			wsm.add_parts(0, 250, 1);
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all weapon parts!"), ICON_FA_PLUS});
			Features::Account::addallwepparts = false;
		}

		if (Features::Account::adddlcweps) {
			wsm.add_dlcweps(ExperienceController::get_CurrentLevel());
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added DLC Weapons!"), ICON_FA_PLUS});
			Features::Account::adddlcweps = false;
		}

		if (Features::Account::addallwear) {
			wsm.add_all_wear(ExperienceController::get_CurrentLevel());
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all wear!"), ICON_FA_PLUS});
			Features::Account::addallwear = false;
		}

		if (Features::Account::addallgadgets) {
			wsm.add_gadget(0, ExperienceController::get_CurrentLevel());
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all gadgets!"), ICON_FA_PLUS});
			Features::Account::addallgadgets = false;
		}

		if (Features::Account::addallroyale) {
			wsm.add_all_royale();
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all royale items!"), ICON_FA_PLUS});
			Features::Account::addallroyale = false;
		}

		if (Features::Account::addallweapons) {
			wsm.add_weapons_ranged(1, 2000, ExperienceController::get_CurrentLevel());;
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added all weapons!"), ICON_FA_PLUS});
			Features::Account::addallweapons = false;
		}

		if (Features::Account::getslot) {
			wsm.fetch_slot(13);
			Features::Account::getslot = false;
		}
		
		if (Features::Account::reloadws) {
			wsm._reloadws();// force reload
			// wsm.fetch_slot(37);
			ImGui::InsertNotification({ImGuiToastType::Success, 1500, OBF("%s Reloaded!"), ICON_FA_ROTATE_RIGHT});
			Features::Account::reloadws = false;
		}
		
		if (Features::Account::changenickname) {
			wsm.change_nickname(Features::Account::changenamebuf);
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Changed nickname!"), ICON_FA_PENCIL});
			Features::Account::changenickname = false;
		}

		if (Features::Account::addbadge) {
			wsm.add_badge();
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added badge!"), ICON_FA_PLUS});
			Features::Account::addbadge = false;
		}

		if (Features::Account::setlevel) {
			if (Features::Account::setleveltarget <= ExperienceController::get_CurrentLevel()) {
				ImGui::InsertNotification({ImGuiToastType::Error, 1500, OBF("You can't set your level to a lower level than your current level!")});
			} else {
				wsm.set_level(Features::Account::setleveltarget);
				wsm.reloadws();
				ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Set level to %d successfully!"), ICON_FA_ARROW_UP, Features::Account::setleveltarget});
			}
			Features::Account::setlevel = false;
		}

		if (Features::Account::bugclan) {
			std::string clanid = Features::Account::clanidBuf;
			wsm.bug_clan(clanid, 0, generateRandomNumber(10000, 50000));
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Bugged clan: %s!"), ICON_FA_PLUS, clanid.c_str()});
			Features::Account::bugclan = false;
		}

		if (Features::Account::windeathmatch) {
			wsm.win_deathmatch();
			wsm.reloadws();
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added a deathmatch win!"), ICON_FA_PLUS});
			Features::Account::windeathmatch = false;
		}

		if (Features::Account::wsaddcurrency) {
			wsm.add_currency(Features::Account::wscurrencyamount, wscurrencyCombo[wscurrencytype[1]], OBF("PixelPassTask"));
			// fslog::info(OBF("Added {} {}"), Features::Account::wscurrencyamount, wscurrencyComboVisualName[wscurrencytype[1]]);
			ImGui::InsertNotification({ImGuiToastType::Info, 1500, OBF("%s Added %d %s"),ICON_FA_PLUS, Features::Account::wscurrencyamount, wscurrencyComboVisualName[wscurrencytype[1]]});
			Features::Account::wsaddcurrency = false;
		}

	} else {
		if (Tab == Account && AccountSubTab == tab2 && Variables::imguiinit == true && Variables::wepsoundshooked == true) {
			if (ticksSinceInjected % roundedfps == 0) {
				ImGui::InsertNotification({ImGuiToastType::Warning, 1500, OBF("WebsocketManager is null! Please play the game a bit and try again!")});
			}
		}
	}

	if (Features::Account::SkinModder::addskin) {
		nlohmann::json userSkins;
		nlohmann::json userNameSkins;
		int startIndex = generateRandomNumber(1000, 9999);
		for (int i = 0; i < Features::Account::SkinModder::skinfiles.size(); i++) {
			std::string path = Features::Account::SkinModder::skinfiles.at(i);
			std::string base64 = encodeFileToBase64(path);
			if (base64.length() > 0) {
				std::string base64Str(base64);
				std::string skinNameStr = std::string(Features::Account::SkinModder::skinnameBuf) + std::to_string(i);

				userSkins[std::to_string(startIndex + i)] = base64Str;
				userNameSkins[std::to_string(startIndex + i)] = skinNameStr + std::to_string(startIndex + i);
			} else {
				ImGui::InsertNotification({ImGuiToastType::Error, 1500, OBF("Failed to read skin file!")});
			}
		}
		fslog::info("user skins value: {}", userSkins.dump());
		fslog::info("user name skins value: {}", userNameSkins.dump());

		PlayerPrefs::setString(NewIl2cppString(OBF("User Skins")), NewIl2cppString(userSkins.dump().c_str()));
		PlayerPrefs::setString(NewIl2cppString(OBF("User Name Skins")), NewIl2cppString(userNameSkins.dump().c_str()));
		PlayerPrefs::setString(NewIl2cppString(OBF("Name Current Skin")), NewIl2cppString(std::to_string(startIndex + 1).c_str()));

		ImGui::InsertNotification({ImGuiToastType::Success, 3000, OBF("Added skins! Reload to apply skins!")});
		Features::Account::SkinModder::addskin = false;
	}

	if (Features::Settings::bruteforceitemrecord) {
		if (wepmanager != nullptr) {
			monoList<void**>* itemrecordlist = *(monoList<void**>**)((uint64_t) wepmanager + fieldoffsets::itemrecordlist);
			json jsonArray = json::array();
			for (int i = 0; i < itemrecordlist->getSize(); i++) {
				void* itemrecord = itemrecordlist->getItems()[i];
				if (itemrecord != nullptr) {
					int index = ItemRecord::get_Index(itemrecord);
					int rarity = ItemRecord::get_Rarity(itemrecord);
					std::string rarityname = rarityNameFromEnum(rarity);
					int galleryNum = ItemRecord::get_WeaponNumber(itemrecord);
					std::string tag = ItemRecord::get_Tag(itemrecord)->ToString();
					std::string wepname = ItemRecord::get_shopName(itemrecord)->ToString();

					json weaponObject = {
						{OBF("gallery_number"), galleryNum},
						{OBF("codeName"), tag.c_str()},
						{OBF("wepName"), wepname.c_str()},
						{OBF("index"), index},
						{OBF("rarity"), rarityname},
					};

					jsonArray.push_back(weaponObject);
				}
			}
			std::string jsonString = jsonArray.dump(4); 
			printf("%s\n", jsonString.c_str());
			ImGui::InsertNotification({ImGuiToastType::Success, 5000, OBF("Successfully dumped item records! Check the console for the output.")});

			std::string currentPath = std::filesystem::current_path().string();
			std::ofstream outputFile(currentPath + OBF("/itemrecords.json"), std::ios::binary);

			if (outputFile.is_open()) {
				outputFile << jsonString;
				outputFile.close();
				ImGui::InsertNotification({ImGuiToastType::Success, 5000, OBF("Saved dump to itemrecords.json to Pixel Gun 3D folder!!")});
			}
		} else {
			ImGui::InsertNotification({ImGuiToastType::Error, 1500, OBF("Unable to dump because WeaponManager is null!")});
		}
		Features::Settings::bruteforceitemrecord = false;
	}

    localplayer.set_inmatch(InappBonusesController::isInMatch());
    if (!localplayer.get_inmatch()) {
        ticksSinceMatchStart = 0;
        localplayer.set_ref(nullptr);
    } else {
        if (ticksSinceMatchStart >= (int)(INT_MAX / 2)) {
            ticksSinceMatchStart = (int)(INT_MAX / 4);
        }
        ticksSinceMatchStart++;
    }
    Variables::accountID = std::string(OBF("ID:\n")) + get_AccountID()->ToString();
    Variables::accountAuth = std::string(OBF("Auth:\n")) + get_AccountAuth(get_AuthInstance())->ToString();
	
    if (ticksSinceInjected >= (int)(INT_MAX / 2)) {
        ticksSinceInjected = (int)(INT_MAX / 4);
    }
    ticksSinceInjected++;
	Variables::pixeltimehooked = true;

    Hooks::old_PixelTime(instance);
}

void (*Hooks::old_Rocket)(void* instance) = nullptr;
void Hooks::Rocket(void* instance) {
	if (instance != nullptr) {
		void* rocketSettings = *(void**)((uint64_t) instance + fieldoffsets::rocketsettings);
		if (rocketSettings != nullptr) {
			if (Features::GameplayBullet::RickochetRocket) {
				*(bool*)((uint64_t) rocketSettings + GET_FIELDOFFSET("RocketSettings", "isRickochet")) = OBF(true);
				*(int*)((uint64_t) rocketSettings + GET_FIELDOFFSET("RocketSettings", "rickochetsCount")) = 99999;
			}
		}
	}
	Hooks::old_Rocket(instance);
}

void (*Hooks::old_ApplyDamage)(void* instance, float dmg, void* n, void* nn, Vector3 nnn, void* a, void* b, il2cppString* c, int d, void* e) = nullptr;
void Hooks::ApplyDamage(void* instance, float dmg, void* n, void* nn, Vector3 nnn, void* a, void* b, il2cppString* c, int d, void* e) {
	if (Features::GameplayWeapon::multiplydamage) {
		return Hooks::old_ApplyDamage(instance, dmg * Features::GameplayWeapon::damagemultiplier, n, nn, nnn, a, b, c, d, e);
	}
	if (Features::GameplayWeapon::maxdamage) {
		return Hooks::old_ApplyDamage(instance, 50.0f, n, nn, nnn, a, b, c, d, e);
	}
	if (Features::GameplayWeapon::lowdamage) {
		return Hooks::old_ApplyDamage(instance, 0.1f, n, nn, nnn, a, b, c, d, e);
	}
	return Hooks::old_ApplyDamage(instance, dmg, n, nn, nnn, a, b, c, d, e);
}

bool (*Hooks::old_IsEnemyTo)(void*, void*) = nullptr;
bool Hooks::IsEnemyTo(void* instance, void* player) {
	if (Features::GameplayMain::friendlyfire) {
		return true;
	}
    return Hooks::old_IsEnemyTo(instance, player);
}

int (*Hooks::old_MaxAmmo)(void* instance) = nullptr;
int Hooks::MaxAmmo(void* instance) {
	if (Features::GameplayMain::infammo) {
		return 9999;
	} 
	return Hooks::old_MaxAmmo(instance);
}

int (*Hooks::old_AmmoInClip)(void* instance) = nullptr;
int Hooks::AmmoInClip(void* instance) {
	if (Features::GameplayMain::infammo) {
		return 9999;
	}
	return Hooks::old_AmmoInClip(instance);
}

int (*Hooks::old_InitialAmmo)(void* instance) = nullptr;
int Hooks::InitialAmmo(void* instance) {
	if (Features::GameplayMain::infammo) {
		return 9999;
	}
	return Hooks::old_InitialAmmo(instance);
}


il2cppString* (*Hooks::old_filterChatMsg)(il2cppString* message) = nullptr;
il2cppString* Hooks::filterChatMsg(il2cppString* message) {
	if (Features::GameplayMain::chatbypass) {
		return message;
	}
	return Hooks::old_filterChatMsg(message);
} 

void (*Hooks::old_addCur)(void*, il2cppString*, int, int, bool, bool, AnalyticsParams2) = nullptr;
void Hooks::addCur(void* instance, il2cppString* currencyType, int value, int num, bool something, bool something2, AnalyticsParams2 params) {	
	if (Features::Account::collectibles) {
		int origamount = value;
		for (int i = 0; i < Features::Account::collectiblesLoop; i++) {
			old_addCur(instance, currencyType, value * Features::Account::collectiblesMultiplier, num, something, something2, params);
		}
		fslog::info(OBF("Added {} {}! ({} x {})"), (value * Features::Account::collectiblesLoop) * Features::Account::collectiblesMultiplier, currencyType->ToString().c_str(), (Features::Account::collectiblesMultiplier * Features::Account::collectiblesLoop), origamount);
	}
	else {
		Hooks::old_addCur(instance, currencyType, value, num, something, something2, params);
	}
}

int (*Hooks::old_idknigga)() = nullptr;
int Hooks::idknigga() {
	if (Features::Account::expmultiplier) {
		return Features::Account::expmultiplierAmount;
	}
	return Hooks::old_idknigga();
}

bool (*Hooks::old_idknigga2)(void*, int) = nullptr;
bool Hooks::idknigga2(void* instance, int faggot) {
	if (Features::Account::expmultiplier) {
		return true;
	}
	return Hooks::old_idknigga2(instance, faggot);
}

int (*Hooks::old_WebsocketManagerSend)(void*, il2cppString*, void*) = nullptr;
int Hooks::WebsocketManagerSend(void* instance, il2cppString* clientEvent, void* data) {
    if (!wsm.get_wsmi() || wsm.get_wsmi() != instance) {
        wsm = WebsocketManager(instance);
		wsm.setversion(Application::get_Version()->ToString().c_str());
		wsm.set_playerid(get_AccountID()->ToString().c_str());
    }
	
	if (Features::Settings::logwebsocket) {
		// fslog::debug("[SEND] {} | {}", clientEvent->ToString().c_str(), serializeObject(data)->ToString());
	}
	return Hooks::old_WebsocketManagerSend((void*) instance, clientEvent, data);
}

void (*Hooks::old_WebsocketRecieve)(void* instance, void* socket, void* packet, void* object) = nullptr;
void Hooks::WebsocketRecieve(void* instance, void* socket, void* packet, void* object) {
	#ifdef PAIDVERSION
	std::string pkt = PacketToString(packet)->ToString().c_str();
	json jpkt = json::parse(pkt);
	const char* event = stripQuotes(jpkt[0].dump().c_str()).c_str();
	bool eventIsNone = std::strlen(event) == 0;
	int reqid = jpkt[1].contains(OBF("req_id")) ? jpkt[1][OBF("req_id")].get<int>() : 0;

	if (eventIsNone) { event = OBF("None"); }
	if (reqid != 0) {
		auto it = response_callbacks.find(reqid);
		if (it != response_callbacks.end()) {
			it->second(jpkt[1]);
		}
	}
	
	if (Features::Settings::logwebsocket) {
		fslog::info(OBF("[RECV] {} | {}"), event, jpkt[1].dump().c_str());
	}
	#endif
	Hooks::old_WebsocketRecieve(instance, socket, packet, object);
} 

void* (*Hooks::old_WebsocketRecieve2)(il2cppString* command, void* dict1, void* dict2, void* listbytearr) = nullptr;
void* Hooks::WebsocketRecieve2(il2cppString* command, void* dict1, void* dict2, void* listbytearr) {
	std::string response = serializeObject(dict1)->ToString().c_str();
	std::string commnd_str = command->ToString().c_str();

	fslog::info(OBF("[RECV2] {} | {}"), commnd_str, response);

	return Hooks::old_WebsocketRecieve2(command, dict1, dict2, listbytearr);
}

void (*Hooks::old_SetCrosshairColor)(void* instance, Vector4 color) = nullptr;
void Hooks::SetCrosshairColor(void* instance, Vector4 color) {
	if (Features::GameplayAimbot::triggerbot && localplayer.get_ref() != nullptr) {
		if (color == Vector4(1, 0, 0, 1)) {
			player_move_c::ShotPressed(localplayer.get_ref(), false);
		}
	}
	Hooks::old_SetCrosshairColor(instance, color);
}

void (*Hooks::old_WeaponManager)(void*) = nullptr;
void Hooks::WeaponManager(void* instance) {
	if (instance != nullptr) {
		wepmanager = instance;
	}
	Hooks::old_WeaponManager(instance);
}


int (*Hooks::old_get_Parts)(void* instance, int idk) = nullptr;
int Hooks::get_Parts(void* instance, int idk) {
	if (Features::Account::freeclanupgrade) {
		return 0;
	}
	return Hooks::old_get_Parts(instance, idk);
}

int (*Hooks::old_get_UpgradeTime)(void* instance) = nullptr;
int Hooks::get_UpgradeTime(void* instance) {
	if (Features::Account::freeclanupgrade) {
		return 1;
	}
	return Hooks::old_get_UpgradeTime(instance);
}

void* (*Hooks::old_encryptCommand)(void*, void*, bool) = nullptr;
void *Hooks::encryptCommand(void *instance, void *byteArr, bool idk) {
	/* if (instance != nullptr && !command_params.empty()) {
		std::string currentCommand = Encoding::GetString(Encoding::get_UTF8(), byteArr)->ToString();
        bool commandFound = false;

        for (const auto &param: command_params) {
            if (currentCommand == (*param.second)[0]) {
                commandFound = true;
                break;
		        }
        }

        if (!commandFound) {
            json parsedJson;
            try {
                parsedJson = json::parse(currentCommand);
                fslog::debug("Parsed JSON successfully");

                auto requestIdIterator = parsedJson.find("req_id");
                if (requestIdIterator == parsedJson.end()) {
                    fslog::warn("No req_id found in request!");
                    return old_encryptCommand(instance, byteArr, idk);
                }

                int requestId = *requestIdIterator;
                fslog::info("Found req_id: {} in {}", requestId, parsedJson.dump().c_str());

                auto commandIterator = command_params.find(requestId);
                if (commandIterator == command_params.end()) {
                    fslog::warn(OBF("No request with id %i"), requestId);
                    return old_encryptCommand(instance, byteArr, idk);
                }

                (*commandIterator->second)[1]["req_id"] = requestId;
                std::string newParamsStr = nullToArray((*commandIterator->second)[1].dump());
                fslog::info(OBF("Sending request with id {}"), requestId);

                command_params.erase(commandIterator);
                return old_encryptCommand(instance, Encoding::GetBytes(Encoding::get_UTF8(), NewIl2cppString(newParamsStr.c_str())), idk);
            } catch (nlohmann::json::parse_error &e) {
                fslog::error(OBF("Failed to parse JSON: {}"), currentCommand.c_str());
            }
        }

	} */
	
	return Hooks::old_encryptCommand(instance, byteArr, idk);
}


void Hooks::init_hooks() {
	int totalHooks = 23;
	int currentProgress = 0;
	fslog::info(OBF("Initializing hooks..."));
	MINHOOK_IL2CPP("WeaponSounds", "Update", WeaponSounds, "1"); 											showLoadingBar(++currentProgress, totalHooks);
	MINHOOK_IL2CPP("Player_move_c", "Update", Player_move_c, "2"); 											showLoadingBar(++currentProgress, totalHooks);
    MINHOOK_IL2CPP("Player_move_c", ".ctor", PMC, "3"); 													showLoadingBar(++currentProgress, totalHooks);
    MINHOOK_IL2CPP("Player_move_c", "OnDestroy", destructPMC, "4"); 										showLoadingBar(++currentProgress, totalHooks);
    MINHOOK_IL2CPP("PixelTime", "Update", PixelTime, "5"); 													showLoadingBar(++currentProgress, totalHooks);
    MINHOOK_IL2CPP("PlayerDamageable", "ApplyDamage", ApplyDamage, "6"); 									showLoadingBar(++currentProgress, totalHooks);
    MINHOOK_IL2CPP("PlayerDamageable", "IsEnemyTo", IsEnemyTo, "7"); 										showLoadingBar(++currentProgress, totalHooks);
	MINHOOK_IL2CPP("ItemRecord", "get_MaxAmmo", MaxAmmo, "8"); 												showLoadingBar(++currentProgress, totalHooks);
	MINHOOK_IL2CPP("ItemRecord", "get_AmmoInClip", AmmoInClip, "9"); 										showLoadingBar(++currentProgress, totalHooks);
	MINHOOK_IL2CPP("ItemRecord", "get_InitialAmmo", InitialAmmo, "10");										showLoadingBar(++currentProgress, totalHooks);
    MINHOOK2(GetMethodPointerPattern(klass_filterChat, Sigs::FilterChatMessageC), filterChatMsg, "11"); 	showLoadingBar(++currentProgress, totalHooks);
    MINHOOK_IL2CPP("Rocket", "Update", Rocket, "12"); 														showLoadingBar(++currentProgress, totalHooks);
    MINHOOK2(GetMethodPointerPattern(klass_ProgressUpdater, Sigs::PU_addCurrency), addCur, "13");			showLoadingBar(++currentProgress, totalHooks);
	MINHOOK("0xcd4f40", idknigga, "14");																	showLoadingBar(++currentProgress, totalHooks);
	MINHOOK("0xcd5000", idknigga2, "15");																	showLoadingBar(++currentProgress, totalHooks);
	MINHOOK2(GetMethodPointerPattern(klass_WebsocketManager, Sigs::WSMSendC), WebsocketManagerSend, "16"); 	showLoadingBar(++currentProgress, totalHooks);
	MINHOOK2(GetMethodPointerPattern(klass_WebsocketManager, Sigs::WSRecvC), WebsocketRecieve, "17"); 		showLoadingBar(++currentProgress, totalHooks);
	MINHOOK2(GetMethodPointerPattern(klass_RecvClass, Sigs::RecvC), WebsocketRecieve2, "18"); 				showLoadingBar(++currentProgress, totalHooks);
	MINHOOK_IL2CPP("AimCrosshairController", "SetCrosshairColor", SetCrosshairColor, "19");					showLoadingBar(++currentProgress, totalHooks);
	MINHOOK_IL2CPP("WeaponManager", "Update", WeaponManager, "20");											showLoadingBar(++currentProgress, totalHooks);
	MINHOOK2(GetMethodPointerPattern(klass_PlaceableItemSettings, Sigs::GetPartsC), get_Parts, "21"); 		showLoadingBar(++currentProgress, totalHooks);
	MINHOOK_IL2CPP("PlaceableItemSettings", "get_UpgradeTime", get_UpgradeTime, "22"); 						showLoadingBar(++currentProgress, totalHooks);
	MINHOOK2(GetMethodPointerPattern(klass_EncryptCommand, Sigs::EncryptCommandC), encryptCommand, "23"); 	showLoadingBar(++currentProgress, totalHooks); std::cout << std::endl;

    fslog::info(OBF("Hooks initialized!"));
}