#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"
#include "RankingComponent.h"
class EndComponent : public Component
{
private:
	UIData data;
	Sprite sprite;
	Text text;
	RankingComponent* rank;
	bool isTitle;
public:
	EndComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//ゲームの状態を返す
	const GameState GetState();
};