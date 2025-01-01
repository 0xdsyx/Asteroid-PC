#include "Player.h"

Player::Player(void* instance) : ref(instance), is_inmatch(false){};

void* Player::get_ref() {
	return this->ref;
}

void Player::set_ref(void* ptr) {
	this->ref = ptr;
}

void* Player::get_transform() {
	if (this->ref) {
		return *(void**)((uintptr_t)this->ref + GET_FIELDOFFSET("Player_move_c", "myPlayerTransform"));
	}
	return nullptr;
}

void* Player::get_player_cam() {
	if (this->ref != nullptr) {
		return BaseCamera::get_Camera(player_move_c::get_BaseCamera(this->ref));
	}
	return nullptr;
}

void* Player::get_basecam_transform() {
	void* skinName = *(void**)((uintptr_t)this->ref + GET_FIELDOFFSET("Player_move_c", "mySkinName"));
	if (skinName != nullptr) {
		void* fpcs = *(void**)((uintptr_t)skinName + GET_FIELDOFFSET("SkinName", "firstPersonControl"));
		if (fpcs != nullptr) {
			void* baseCam = *(void**)((uintptr_t)fpcs + GET_FIELDOFFSET("FirstPersonControlSharp", "playerCamera"));
			if (baseCam != nullptr) {
				return *(void**)((uintptr_t)baseCam + fieldoffsets::basecamtransform);
			}
		}
	}
	return nullptr;
}

void* Player::get_playerdamagable() {
	if (this->ref != nullptr) {
		return *(void**)((uintptr_t)this->ref + fieldoffsets::pdamageable);
	}
	return nullptr;
}

bool Player::is_mine() {
	if (this->ref != nullptr) {
		void* skinName = *(void**)((uintptr_t)this->ref + GET_FIELDOFFSET("Player_move_c", "mySkinName"));
		if (skinName != nullptr) {
			return *(bool*)((uintptr_t)skinName + GET_FIELDOFFSET("SkinName", "isMine"));
		}
	}
	return false;
}

Vector3 Player::get_position() {
	void* p_transform = this->get_transform();
	if (p_transform) {
		void* transform = Component::get_Transform(p_transform);
		if (transform) {
			return Transform::get_Position(transform);
		}
	}
	return Vector3::Zero();
}

void Player::set_position(Vector3 pos) {
	void* p_transform = this->get_transform();
	if (p_transform) {
		void* transform = Component::get_Transform(p_transform);
		if (transform) {
			Transform::set_Position(transform, pos);
		}
	} else {
		fslog::error(OBF("transform is nullptr, cant set pos"));
	}
}

bool Player::get_inmatch() {
	return this->is_inmatch;
}

void Player::set_inmatch(bool inmatch) {
	this->is_inmatch = inmatch;
}