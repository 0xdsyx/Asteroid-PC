#pragma once

#include <iostream>
#include <random>
#include <fstream>

#include "obfusheader.h"
#include "IL2CPP_Resolver.hpp"
#include "utils.h"
#include "Pointers.h"
#include "List.h"
#include "imgui.h"
#include "../menu/ui/menufeatures.h"
#include "../menu/mods/Structs.h"
#include "Game/globvars.h"
#include "Game/Player.h"
#include "Fields.h"
#include "../imgui/ImGuiNotify.h"
#include "../helpers/vmp/VMProtectSDK.h"

namespace Hooks {
    extern void (*old_WeaponSounds)(void*);
    void WeaponSounds(void* instance);

    extern int random;
    extern void (*old_Player_move_c)(void*);
    void Player_move_c(void* instance);
    
    extern void* (*old_PMC)(void*);
    void* PMC(void* instance);

    extern void (*old_destructPMC)(void*);
    void destructPMC(void* instance);

    extern void (*old_PixelTime)(void*);
    void PixelTime(void* instance);

    extern void (*old_ApplyDamage)(void* instance, float dmg, void* n, void* nn, Vector3 nnn, void* a, void* b, il2cppString* c, int d, void* e);
    void ApplyDamage(void* instance, float dmg, void* n, void* nn, Vector3 nnn, void* a, void* b, il2cppString* c, int d, void* e);

    extern bool (*old_IsEnemyTo)(void*, void*);
    bool IsEnemyTo(void* instance, void* player);

    extern int (*old_MaxAmmo)(void* instance);
    int MaxAmmo(void* instance);

    extern int (*old_AmmoInClip)(void* instance);
    int AmmoInClip(void* instance);

    extern int (*old_InitialAmmo)(void* instance);
    int InitialAmmo(void* instance);

    extern il2cppString* (*old_filterChatMsg)(il2cppString* message);
    il2cppString* filterChatMsg(il2cppString* message);

    extern void (*old_Rocket)(void* instance);
    void Rocket(void* instance);

    extern void (*old_addCur)(void*, il2cppString*, int, int, bool, bool, AnalyticsParams2);
    void addCur(void* instance, il2cppString* currencyType, int value, int num, bool something, bool something2, AnalyticsParams2 params);

    extern int (*old_idknigga)();
    int idknigga();

    extern bool (*old_idknigga2)(void*, int);
    bool idknigga2(void* instance, int faggot);

    extern int (*old_WebsocketManagerSend)(void*, il2cppString*, void*);
    int WebsocketManagerSend(void* instance, il2cppString* clientEvent, void* data);

    extern void (*old_WebsocketRecieve)(void* instance, void* socket, void* packet, void* object);
    void WebsocketRecieve(void* instance, void* socket, void* packet, void* object);

    extern void* (*old_WebsocketRecieve2)(il2cppString* command, void* dict1, void* dict2, void* listbytearr);
    void* WebsocketRecieve2(il2cppString* command, void* dict1, void* dict2, void* listbytearr);

    extern void (*old_SetCrosshairColor)(void* instance, Vector4 color);
    void SetCrosshairColor(void* instance, Vector4 color);

    extern void (*old_WeaponManager)(void*);
    void WeaponManager(void* instance);

    extern int (*old_get_Parts)(void* instance, int idk);
    int get_Parts(void* instance, int idk);

    extern int (*old_get_UpgradeTime)(void* instance);
    int get_UpgradeTime(void* instance);

    extern void *(*old_encryptCommand)(void*, void*, bool);
    void *encryptCommand(void *instance, void *byteArr, bool idk);

    void init_hooks();
}