#pragma once

#include <vector>

#include "Player.h"
#include "WebsocketManager.h"

extern Player localplayer;
extern std::vector<Player> playerList;
extern int delayTime;
extern int roundedfps;
extern int ticksSinceMatchStart;
extern int ticksSinceInjected;
extern void* wepmanager;
extern WebsocketManager wsm;
