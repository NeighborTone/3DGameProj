#pragma once
#include "Transform.hpp"

//マウスと十字キーの入力に応じて座標と角度を動かします
//TransformComponentで初期値を設定する必要があります
class InuputMoveComponent : public Component
{
private:
	float speed_;
	TransformComponent* transform;
	Vec3 dir;
public:
	//旋回速度を引数に指定
	InuputMoveComponent(const float angleSpeed);
	void Initialize() override;

	void UpDate() override;
	
	void Draw3D() STUB

	void Draw2D() STUB

};