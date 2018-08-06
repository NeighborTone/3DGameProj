#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"

//このクラスは確実に失敗だった(配列を作れない)。データは別枠で作ることにする
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
