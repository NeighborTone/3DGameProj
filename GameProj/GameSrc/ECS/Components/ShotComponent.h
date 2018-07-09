#pragma once
#include "InputShotComponent.h"
#include <vector>
//�󂯂Ƃ����������ʂ����Ƃɒe��`�悷��R���|�[�l���g
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