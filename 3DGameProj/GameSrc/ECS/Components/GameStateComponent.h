#pragma once
#include "../ECS.hpp"
#include "ComponentData/MetaData.hpp"

class GameStateComponent : public Component
{
private:
	GameState state;
	const void GameTitle();
	const void GamePlay();
	const void GamePause();
	const void GameReset();
public:
	const GameState GetCurrentState() const;
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() STUB
};