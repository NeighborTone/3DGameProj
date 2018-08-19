#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"
#include "RankingComponent.h"

class EndComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 30;
	Float4 backColor;
	Sprite sprite;
	UIData textData;
	Text text;
	Counter cnt;
	RankingComponent* rank;
	bool isReset;
	Easing reduction;
public:
	EndComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//ƒQ[ƒ€‚Ìó‘Ô‚ğ•Ô‚·
	const GameState GetState() const;
};