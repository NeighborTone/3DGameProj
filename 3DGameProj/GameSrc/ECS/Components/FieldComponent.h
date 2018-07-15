#pragma once
#include "../../Engine./Graphics/Mesh.h"
#include "../ECS.hpp"

class FieldComponent : public Component
{
private:
	Texture tex;
	Mesh mesh;

public:
	FieldComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() override;
};