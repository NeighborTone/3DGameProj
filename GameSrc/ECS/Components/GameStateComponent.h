#pragma once
#include "../ECS.hpp"
#include "../../Utilitys/Counter.hpp"
#include "ComponentData/MetaData.hpp"
#include "TimerComponent.h"
//ゲームの状態を監視します
//他のコンポーネントから状態を受け取り、GameContollerに伝えます
class GameStateComponent : public Component
{
private:
	TimerComponent* timer;
	GameState state;
	void GamePause();
	void GameEnd();
	void TimerRun();
public:
	//ほかのコンポーネントから状態を受け取る
	void SetState(const GameState& state_);
	//現在のゲームの状態を返す
	[[nodiscard]] const GameState GetCurrentState() const;
	//Entityの状態から状態遷移
	void SetEntity(const Entity& entity);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() STUB
};