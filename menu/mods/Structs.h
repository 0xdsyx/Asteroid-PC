#pragma once

#include "unity/Unity.h"
#include "unity/Vector2.h"
#include "unity/Vector3.h"
#include "unity/Quaternion.h"
#include "utils.h"


struct AnalyticsParams2 {
	int enum1;
	int enum2;
	int enum3;
	int enum4;
	int enum5;
	int enum6;
	int enum7;
	bool bool1;
	void* klass1;
	int enum8;
	bool bool2;
	int enum9;
	void* klass2;
	bool bool3;
	int enum10;
	il2cppString* string;
	void* struct1;
};


struct RaycastHit {
	Vector3 point;
	Vector3 normal;
	uint32_t faceid;
	float distance;
	Vector2 uv;
	int collider;
};

struct Ray {
	Vector3 m_vOrigin;
	Vector3 m_vDirection;
};

struct U_Bounds {
	Vector3 center;
	Vector3 extents;
};

struct spendCurStruct {
	int enum1;
	int enum2;
	int enum3;
	void* klass;
};