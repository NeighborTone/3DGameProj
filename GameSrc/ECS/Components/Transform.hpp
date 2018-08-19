#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"

//���̃N���X�͊m���Ɏ��s������(�z������Ȃ�)�B�f�[�^�͕ʘg�ō�邱�Ƃɂ���
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
