#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"
class PauseComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 40;
	UIData data;
	Sprite sprite;
	Text text;
public:
	PauseComponent();
	void Initialize() override;

	void UpDate() override;

	void Draw3D() STUB

	void Draw2D() override;
	//ÉQÅ[ÉÄÇäJénÇ∑ÇÈÇ©ï‘Ç∑
	const GameState GetState();
};