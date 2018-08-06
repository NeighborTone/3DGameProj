#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"

class TitleComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	UIData logodata;
	UIData textdata;
	Easing reduction;
	Float4 backColor;
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