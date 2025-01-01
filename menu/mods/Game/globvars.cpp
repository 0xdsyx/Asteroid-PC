#include "globvars.h"

Player localplayer = Player(nullptr);
std::vector<Player> playerList = {};
int delayTime = 0;
int roundedfps = 0;
int ticksSinceMatchStart = 0;
int ticksSinceInjected = 0;
void* wepmanager = nullptr;
WebsocketManager wsm = WebsocketManager(nullptr);
