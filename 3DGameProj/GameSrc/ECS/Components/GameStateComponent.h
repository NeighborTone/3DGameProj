#pragma once
#include "../ECS.hpp"
#include "../../Utilitys/Counter.hpp"
#include "ComponentData/MetaData.hpp"

//ゲームの状態を監視します
//他のコンポーネントからメッセージを受け取り、GameContollerに伝えます
class GameStateComponent : public Component
{
private:
	static constexpr int TimeLimit = 20'000;
	Counter cnt;
	GameState state;
	void GamePause();
	void GameEnd();
	void TimerRun();
	Text text;
public:
	GameStateComponent();
	//ほかのコンポーネントからメッセージを受け取る
	void SetState(const GameState& state_);
	//現在のゲームの状態を返す
	const GameState GetCurrentState() const;
	//Entityの状態から状態遷移
	void SetEntity(const Entity& entity);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() STUB
};