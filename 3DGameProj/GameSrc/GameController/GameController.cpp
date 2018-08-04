#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include "../ECS/Components/FieldComponent.h"
#include "../ECS/Components/UFOComponent.h"
#include "../ECS/Components/MiniMapComponent.h"
#include "../ECS/Components/TomatoComponent.h"
#include "../ECS/Components/CursorComponent.h"
#include "../ECS/Components/ScoreBoardComponent.h"
#include "../ECS/Components/GameStateComponent.h"
#include "../ECS/Components/PauseComponent.h"
#include "../ECS/Components/TitleComponent.h"
#include "../ECS/Components/EndComponent.h"
#include <iostream>

GameController::GameController() :
	player(entityManager.AddEntity()),
	shot(entityManager.AddEntity()),
	skyBox(entityManager.AddEntity()),
	enemy(entityManager.AddEntity()),
	field(entityManager.AddEntity()),
	gameCanvas(entityManager.AddEntity()),
	topping(entityManager.AddEntity()),
	gameMaster(entityManager.AddEntity()),
	pauseController(entityManager.AddEntity()),
	titleController(entityManager.AddEntity()),
	endController(entityManager.AddEntity())
{
	AsetManager::LoadAset();
	//$Test$
	bgm.Load("Resource/Sounds/spacewar.wav",false);
	bgm.PlayBGM(255,0.15f);

	gameMaster.AddComponent<GameStateComponent>();
	player.AddComponent<TransformComponent>(Pos(0, 15, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();
	player.AddComponent<CursorComponent>();
	shot.AddComponent<InputShotComponent>(40.0f, 20, 0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	enemy.AddComponent<UFOComponent>();
	gameCanvas.AddComponent<MiniMapComponent>();
	gameCanvas.AddComponent<ScoreBoardComponent>();
	pauseController.AddComponent<PauseComponent>();
	topping.AddComponent<TomatoComponent>();
	titleController.AddComponent<TitleComponent>();
	endController.AddComponent<EndComponent>();
	endController.AddComponent<RankingComponent>();
	//グループに登録
	titleController.AddGroup(TITLE);
	gameMaster.AddGroup(ALWAYS);
	skyBox.AddGroup(ALWAYS);
	field.AddGroup(ALWAYS);
	gameCanvas.AddGroup(ALWAYS);
	topping.AddGroup(GAME);
	player.AddGroup(GAME);
	shot.AddGroup(GAME);
	enemy.AddGroup(GAME);
	pauseController.AddGroup(PAUSE);
	endController.AddGroup(END);
}

void GameController::CollisionEvent()
{
	enemy.GetComponent<UFOComponent>().Damaged(shot);
	topping.GetComponent<TomatoComponent>().ToBeKidnapped(enemy);
}

const void GameController::Title(const GameState& state)
{
	if (state == GameState::TITLE)
	{
		auto& titleScene(entityManager.GetGroup(TITLE));
		for (auto& it : titleScene)
		{
			it->UpDate();
		}
		//タイトルからゲームの状態を受け取る
		gameMaster.GetComponent<GameStateComponent>().SetState(
			titleController.GetComponent<TitleComponent>().GetState());
	}
}

const void GameController::Play(const GameState& state)
{
	if (state == GameState::PLAY)
	{
		auto& gameScene(entityManager.GetGroup(GAME));
		for (auto& it : gameScene)
		{
			it->UpDate();
		}
		//衝突した時のイベント処理
		CollisionEvent();
		//プレイヤーの位置と向きから発射する
		shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
		//トマトが0個になるとゲームエンド
		gameMaster.GetComponent<GameStateComponent>().SetEntity(topping);
	
	}
}

const void GameController::Pause(const GameState& state)
{
	if (state == GameState::PAUSE)
	{
		auto& pause(entityManager.GetGroup(PAUSE));
		for (auto& it : pause)
		{
			it->UpDate();
		}
		gameMaster.GetComponent<GameStateComponent>().SetState(
			pauseController.GetComponent<PauseComponent>().GetState());
	}
}

const void GameController::End(const GameState& state)
{
	if (state == GameState::END)
	{
		auto& end(entityManager.GetGroup(END));
		for (auto& it : end)
		{
			it->UpDate();
		}
		//END状態の時にlife0のUFOが残るとスコアが加算され続けるので消しておく
		enemy.DeleteComponent<UFOComponent>();

		endController.GetComponent<RankingComponent>().SetScore(
			gameCanvas.GetComponent<ScoreBoardComponent>().GetScore());
		gameMaster.GetComponent<GameStateComponent>().SetState(
			endController.GetComponent<EndComponent>().GetState());
	}
	
}

const void GameController::Always()
{
	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->UpDate();
	}
}

void GameController::Initialize()
{
	entityManager.Initialize();
}

void GameController::UpDate()
{
	const auto&& state = ComAssist::GetGameState(gameMaster);
	if (state == GameState::RESET)
	{
		enemy.DeleteComponent<UFOComponent>();
		enemy.AddComponent<UFOComponent>();
		entityManager.Initialize();
	}

	//敵が死んだらスコアを増やす
	gameCanvas.GetComponent<ScoreBoardComponent>().SetEntity(enemy);
	Always();
	Title(state);
	Play(state);
	Pause(state);
	End(state);
	//Entityの状態の監視
	entityManager.Refresh();
	//果てが来てしまうのでプレイヤーと一緒に動かす
	skyBox.GetComponent<SkyBoxComponent>().SetPos(ComAssist::GetPos(player));
	//効果音のListenerをセットする。正しく聞こえないことがあるのでEntityの更新の後に呼ぶ
	enemy.GetComponent<UFOComponent>().SetListenerPos(ComAssist::GetPos(player));
	//追跡対象をセットし対象を追跡する
	enemy.GetComponent<UFOComponent>().SetTrackingTarget(topping);
	//ゲームエンドならスコアボードを動かす
	gameCanvas.GetComponent<ScoreBoardComponent>().CheckState(state);
	//マウスは常に画面中央
	Mouse::SetMousePos(0, 0);

}

void GameController::Draw3D()
{
	player.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
	//すべてのparticleにカメラのビューとプロジェクションを渡す
	AsetManager::GetParticle().UpDate(Camera(player.GetComponent<CameraComponent>().GetCamera3D()));
}

void GameController::Draw2D()
{
	Mouse::DrawCursor(false);
	player.GetComponent<CameraComponent>().Project2D();

	const auto&& state = ComAssist::GetGameState(gameMaster);
	auto& always(entityManager.GetGroup(ALWAYS));
	auto& gameScene(entityManager.GetGroup(GAME));
	//後に処理したものが手前に描画される
	if (state == GameState::END)
	{
		auto& end(entityManager.GetGroup(END));
		for (auto& it : end)
		{
			it->Draw2D();
		}
	}
	for (auto& it : always)
	{
		it->Draw2D();
	}
	gameCanvas.GetComponent<MiniMapComponent>().DrawEntityes(topping, player);
	gameCanvas.GetComponent<MiniMapComponent>().DrawEntityes(enemy, player);
	for (auto& it : gameScene)
	{
		it->Draw2D();
	}
	if (state == GameState::TITLE)
	{
		auto& title(entityManager.GetGroup(TITLE));
		for (auto& it : title)
		{
			it->Draw2D();
		}
	}
	if(state == GameState::PAUSE)
	{
		auto& pause(entityManager.GetGroup(PAUSE));
		for (auto& it : pause)
		{
			it->Draw2D();
		}
	}
	
}

void GameController::Finalize()
{

}
