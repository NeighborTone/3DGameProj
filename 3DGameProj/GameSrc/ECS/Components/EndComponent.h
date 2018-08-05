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
	Counter cnt;
	RankingComponent* rank;
	bool isTitle;
public:
	EndComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//ƒQ[ƒ€‚Ìó‘Ô‚ğ•Ô‚·
	const GameState GetState() const;
};