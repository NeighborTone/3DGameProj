#pragma once
#include "Transform.hpp"

//�}�E�X�Ə\���L�[�̓��͂ɉ����č��W�Ɗp�x�𓮂����܂�
//TransformComponent�ŏ����l��ݒ肷��K�v������܂�
class InuputMoveComponent : public Component
{
private:
	float speed_;
	TransformComponent* transform;
	Vec3 dir;
public:
	//���񑬓x�������Ɏw��
	InuputMoveComponent(const float angleSpeed);
	void Initialize() override;

	void UpDate() override;
	
	void Draw3D() STUB

	void Draw2D() STUB

};