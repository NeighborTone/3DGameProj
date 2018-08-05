#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"

class TitleComponent : public Component
{
private:
	UIData logodata;
	UIData textdata;
	Easing reduction;
	Float4 backColor;
	Float4 colorDelta;
	Sprite sprite;
	Sprite logo;
	Text text;
	bool isPlay;
public:

	TitleComponent();
	void Initialize() override;

	void UpDate() override;

	void Draw3D() STUB

	void Draw2D() override;

	//ÉQÅ[ÉÄÇäJénÇ∑ÇÈÇ©ï‘Ç∑
	const GameState GetState();
};