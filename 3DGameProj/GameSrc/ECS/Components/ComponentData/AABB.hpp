#pragma once
#include "../../../Engine/Engine.h"
#include "../Transform.hpp"

//AABBの定義
class AABB
{
public:
	// 中心位置
	Vec3 pos;
	// 中心からの距離
	Scale radius;

	AABB() = default;
	AABB(const Pos&& pos_, const Scale&& r)
	{
		pos = pos_;
		radius = r;
	}
	AABB(const AABB& aabb)
	{
		pos = aabb.pos;
		radius = aabb.radius;
	}
	AABB(const AABB&& aabb)
	{
		pos = aabb.pos;
		radius = aabb.radius;
	}
	
};

