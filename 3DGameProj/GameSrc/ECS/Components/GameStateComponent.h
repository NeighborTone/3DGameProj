#pragma once
#include "../ECS.hpp"
#include "../../Utilitys/Counter.hpp"
#include "ComponentData/MetaData.hpp"

class GameStateComponent : public Component
{
private:
	static constexpr int TimeLimit = 9000'000;
	Counter cnt;
	GameState state;
	const void GamePlay();
	const void GamePause();
	const void GameReset();
	const void GameEnd();
	void TimerRun();
	Text text;
public:
	GameStateComponent();
	const GameState GetCurrentState() const;
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
};