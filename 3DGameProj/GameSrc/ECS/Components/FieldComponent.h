#pragma once
#include "../../Engine.h"
#include "../ECS.hpp"
#include "../../GameController/AsetManager.h"
class FieldComponent : public Component
{
private:
	Texture tex;
	Mesh mesh;
	int efHandle;
public:
	FieldComponent();
	void Initialize() override;
	void UpDate() STUB
	void Draw3D() override;
	void Draw2D() STUB
};