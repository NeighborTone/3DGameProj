#pragma once
#include "../ECS.hpp"
#include "../../Utilitys/Counter.hpp"
#include "../../Sounds/SoundSource.h"
#include "ComponentData/MetaData.hpp"
#include "GameStateComponent.h"
class BGMComponent : public Component
{
private:
	GameStateComponent* pState;
	SoundEngine::SoundSource bgm;
	bool IsMainPlay;
	bool IsIntroPlay;
	void CheckState(const GameState& state);
public:
	BGMComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() STUB

};