#pragma once
#include "Transform.hpp"

//マウスと十字キーの入力に応じて座標と角度を動かします
//TransformComponentで初期値を設定する必要があります
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
	//旋回速度を引数に指定
	InuputMoveComponent(const float angleSpeed);
	void Initialize() override;

	void UpDate() override;
	
	void Draw3D() STUB

	void Draw2D() override;

};