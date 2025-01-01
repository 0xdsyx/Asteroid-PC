#pragma once
#include "utils.h"
#include "Unity/Vector3.h"
#include "../Pointers.h"
#include "../Fields.h"

class Player {
public:
	Player(void* instance);
	void* get_ref();
	void set_ref(void* ptr);
	void* get_transform();
	void* get_player_cam();
	void* get_basecam_transform();
	void* get_playerdamagable();
	bool is_mine();
	Vector3 get_position();
	void set_position(Vector3 pos);
	void set_inmatch(bool inmatch);
	bool get_inmatch();
private:
	void* ref;
	bool is_inmatch;
};