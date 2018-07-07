#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#define STUB override {}
using Pos = Vec3;
using Velocity = Vec3;
using Angles = Vec3;
using Scale = Vec3;

class TransformComponent : public Component
{
public:
	Pos pos;
	Velocity velocity;
	Angles angle;
	Scale scale;
	TransformComponent() = default;
	TransformComponent(Pos&& pos, Velocity&& velocity, Angles&& angle, Scale&& scale) :
		pos(pos),
		velocity(velocity),
		angle(angle),
		scale(scale)
	{}
	void Initialize() STUB

	void UpDate() STUB

	void Draw3D() STUB

	void Draw2D() STUB
};
