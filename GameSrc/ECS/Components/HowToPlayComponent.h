#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"

class HowToPlayComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 30;
	//キー移動説明用
	Text moveText;
	//ショット説明用
	Text shotText;
	//HowToPlayの出し方の説明用
	Text howToText;
	UIData howToData;
	UIData moveData;
	UIData shotData;
	//隠しているか
	bool isHide;
	//テキストが出ているか
	bool isShow;
	//引っ込める用
	Easing drawIn;
public:
	HowToPlayComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	void Reduction(Easing& reduction);
};