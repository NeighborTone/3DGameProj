#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"

class EndComponent : public Component
{
private:
	UIData data;
	Sprite sprite;
	Text text;
public:
	EndComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() override;

};