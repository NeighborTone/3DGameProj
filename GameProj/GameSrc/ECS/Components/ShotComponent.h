#pragma once
#include "InputShotComponent.h"
#include <vector>
//受けとった処理結果をもとに弾を描画するコンポーネント
class ShotComponent : public Component
{
private:
	TransformComponent* trans;
	InputShotComponent* shotMove;
	Texture tex;
	Mesh mesh;

public:
	ShotComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB

};