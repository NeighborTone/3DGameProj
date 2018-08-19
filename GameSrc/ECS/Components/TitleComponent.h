#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"
#include "HowToPlayComponent.h"
class TitleComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 40;
	HowToPlayComponent* howto;
	UIData logoData;
	UIData textData;
	Easing reduction;
	Float4 backColor;
	Sprite sprite;
	Sprite logo;

	UIData numData[3];
	Text number[3];
	UIData destroyData;
	Text destoryLogo;
	Text text;
	bool isPlay;
public:

	TitleComponent();
	void Initialize() override;

	void UpDate() override;

	void Draw3D() STUB

	void Draw2D() override;
	//ゲームを開始したか返す
	const bool IsPlay() const;
	//ゲームを開始するか返す
	const GameState GetState();
};