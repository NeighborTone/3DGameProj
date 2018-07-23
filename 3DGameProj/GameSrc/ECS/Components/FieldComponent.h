#pragma once
#include "../../Engine.h"
#include "../ECS.hpp"

class FieldComponent : public Component
{
private:
	Texture tex;
	Mesh mesh;

public:
	FieldComponent();
	void Initialize() STUB
	void UpDate() STUB
	void Draw3D() override;
	void Draw2D() STUB
};