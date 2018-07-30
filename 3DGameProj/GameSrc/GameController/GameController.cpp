#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include "../ECS/Components/FieldComponent.h"
#include "../ECS/Components/ThiefComponent.h"
#include "../ECS/Components/MiniMapComponent.h"
#include "../ECS/Components/TomatoComponent.h"
#include "../ECS/Components/CursorComponent.h"
#include "../ECS/Components/ScoreBoardComponent.h"
#include "../ECS/Components/GameStateComponent.h"
#include "../ECS/Components/PauseComponent.h"
#include <iostream>

Particle& GameController::GetParticle()
{
	static std::unique_ptr<Particle> ef = std::make_unique<Particle>();
	return *ef;
}

GameController::GameController() :
	player(entityManager.AddEntity()),
	shot(entityManager.AddEntity()),
	skyBox(entityManager.AddEntity()),
	enemy(entityManager.AddEntity()),
	field(entityManager.AddEntity()),
	gameUIcanvas(entityManager.AddEntity()),
	topping(entityManager.AddEntity()),
	gameMaster(entityManager.AddEntity()),
	pauseUIcanvas(entityManager.AddEntity())
{
	gameMaster.AddComponent<GameStateComponent>();
	player.AddComponent<TransformComponent>(Pos(0, 10, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();
	player.AddComponent<CursorComponent>();
	shot.AddComponent<InputShotComponent>(40.0f, 20, 0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	enemy.AddComponent<ThiefComponent>();
	gameUIcanvas.AddComponent<MiniMapComponent>();
	gameUIcanvas.AddComponent<ScoreBoardComponent>();
	pauseUIcanvas.AddComponent<PauseComponent>();
	topping.AddComponent<TomatoComponent>();
	//グループに登録
	gameMaster.AddGroup(ALWAYS);
	skyBox.AddGroup(ALWAYS);
	field.AddGroup(ALWAYS);
	gameUIcanvas.AddGroup(ALWAYS);
	topping.AddGroup(GAME);
	player.AddGroup(GAME);
	shot.AddGroup(GAME);
	enemy.AddGroup(GAME);
	pauseUIcanvas.AddGroup(STOP);

}

void GameController::CollisionEvent()
{
	enemy.GetComponent<ThiefComponent>().Damaged(shot);
	topping.GetComponent<TomatoComponent>().ToBeKidnapped(enemy);
}

void GameController::Initialize()
{
	entityManager.Initialize();
}

void GameController::UpDate()
{
	auto& always(entityManager.GetGroup(ALWAYS));
	auto& gameScene(entityManager.GetGroup(GAME));
	auto& pause(entityManager.GetGroup(STOP));
	switch (ComAssist::GetGameState(gameMaster))
	{
	case GameState::RESET:
		entityManager.Initialize();
	case GameState::PLAY:
		for (auto& it : gameScene)
		{
			it->UpDate();
		}
		//衝突した時のイベント処理
		CollisionEvent();
		//プレイヤーの位置と向きから発射する
		shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
	case GameState::STOP:
		for (auto& it : pause)
		{
			it->UpDate();
		}
	}
	//Entityの状態の監視
	entityManager.Refresh();
	for (auto& it : always)
	{
		it->UpDate();
	}
	//果てが来てしまうのでプレイヤーと一緒に動かす
	skyBox.GetComponent<SkyBoxComponent>().SetPos(ComAssist::GetPos(player));
	//効果音のListenerをセットする
	enemy.GetComponent<ThiefComponent>().SetListenerPos(ComAssist::GetPos(player));
	//追跡対象をセットし対象を追跡する
	enemy.GetComponent<ThiefComponent>().SetTrackingTarget(topping);
	//敵が死んだらスコアを増やす
	gameUIcanvas.GetComponent<ScoreBoardComponent>().SetEntity(enemy);
	//マウスは常に画面中央
	Mouse::SetMousePos(0, 0);
}

void GameController::Draw3D()
{
	player.GetComponent<CameraComponent>().Project3D();

	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->Draw3D();
	}
	auto& gameScene(entityManager.GetGroup(GAME));
	for (auto& it : gameScene)
	{
		it->Draw3D();
	}
	auto& pause(entityManager.GetGroup(STOP));
	for (auto& it : pause)
	{
		it->Draw3D();
	}
	//すべてのparticleにカメラのビューとプロジェクションを渡す
	GetParticle().UpDate(Camera(player.GetComponent<CameraComponent>().GetCamera3D()));
}

void GameController::Draw2D()
{
	Mouse::DrawCursor(false);
	player.GetComponent<CameraComponent>().Project2D();

	auto& always(entityManager.GetGroup(ALWAYS));
	auto& gameScene(entityManager.GetGroup(GAME));
	auto& pause(entityManager.GetGroup(STOP));

	//後に処理したものが手前に描画される
	for (auto& it : always)
	{
		it->Draw2D();
	}
	gameUIcanvas.GetComponent<MiniMapComponent>().DrawEntityes(topping, player);
	gameUIcanvas.GetComponent<MiniMapComponent>().DrawEntityes(enemy, player);
	for (auto& it : gameScene)
	{
		it->Draw2D();
	}
	switch (ComAssist::GetGameState(gameMaster))
	{
	case GameState::STOP:
		for (auto& it : pause)
		{
			it->Draw2D();
		}
	}

}

void GameController::Finalize()
{

}
