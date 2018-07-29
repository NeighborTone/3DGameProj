#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "ComponentData/MetaData.hpp"

class CursorComponent : public Component
{
private:
	TransForm trans;
	Sprite sprite;
public:
	CursorComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
};