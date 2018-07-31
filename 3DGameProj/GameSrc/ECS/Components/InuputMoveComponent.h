#pragma once
#include "Transform.hpp"

//�}�E�X�Ə\���L�[�̓��͂ɉ����č��W�Ɗp�x�𓮂����܂�
//TransformComponent�ŏ����l��ݒ肷��K�v������܂�
class InuputMoveComponent : public Component
{
private:
	static constexpr float UpMax = -90;
	static constexpr float DownMax = 20;
	static constexpr float DirOffSet = 90;
	float speed_;
	TransformComponent* transform;
	Vec3 dir;
	Pos prePos;
	Pos initPos;
	float eyeHeight;
	void MoveForwardAndBack();
	void MoveLeftAndRight();
	void FixedMovableAngle();
	void ManipulationOfView();
	void ForwardAndBackwardDirection();
	void LeftAndRightDirection();
	Text t;
public:
	//���񑬓x�������Ɏw��
	InuputMoveComponent(const float angleSpeed);
	void Initialize() override;

	void UpDate() override;
	
	void Draw3D() STUB

	void Draw2D() override;

};