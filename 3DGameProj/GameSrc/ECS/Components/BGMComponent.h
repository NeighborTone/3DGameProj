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
	bool isMainPlay;
	bool isIntroPlay;
public:
	BGMComponent();
	void StartMain(const bool isPlay);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() STUB

};