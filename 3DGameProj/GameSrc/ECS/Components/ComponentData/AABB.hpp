#pragma once
#include "../../../Engine/Engine.h"
#include "../Transform.hpp"

//AABB�̒�`
class AABB
{
public:
	// ���S�ʒu
	Vec3 pos;
	// ���S����̋���
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

