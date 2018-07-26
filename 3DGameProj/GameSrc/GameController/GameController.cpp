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
#include <iostream>

void GameController::StateMachine()
{
	GameStart();
	GameStop();
}
//$Test$
void GameController::GameStart()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		gameState = GameState::PLAY;
	}
}
//$Test$
void GameController::GameStop()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_X))
	{
		gameState = GameState::STOP;
	}
}

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
	canvas(entityManager.AddEntity()),
	topping(entityManager.AddEntity())
{
	gameState = GameState::STOP;
	player.AddComponent<TransformComponent>(Pos(0, 10, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();
	player.AddComponent<CursorComponent>();

	shot.AddComponent<InputShotComponent>(28.0f, 30, 0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	enemy.AddComponent<ThiefComponent>();
	canvas.AddComponent<MiniMapComponent>();
	topping.AddComponent<TomatoComponent>();
	//グループに登録
	skyBox.AddGroup(ALWAYS);
	field.AddGroup(ALWAYS);
	topping.AddGroup(GAME);
	canvas.AddGroup(ALWAYS);
	player.AddGroup(GAME);
	shot.AddGroup(GAME);
	enemy.AddGroup(GAME);

}

void GameController::CollisionEvent()
{
	enemy.GetComponent<ThiefComponent>().Damaged(shot);
	topping.GetComponent<TomatoComponent>().ToBeKidnapped(enemy);
}

void GameController::Initialize()
{
	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->Initialize();
	}
	auto& gameScene(entityManager.GetGroup(GAME));
	for (auto& it : gameScene)
	{
		it->Initialize();
	}
}

void GameController::UpDate()
{
	StateMachine();	//ゲームの状態の監視
	//$Test$
	if (KeyBoard::Down(KeyBoard::Key::KEY_C))
	{
		entityManager.Initialize();
	}

	entityManager.Refresh();	//Entityの状態の監視


	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->UpDate();
	}

	if (gameState == GameState::PLAY)
	{
		auto& gameScene(entityManager.GetGroup(GAME));
		for (auto& it : gameScene)
		{
			it->UpDate();
		}
		CollisionEvent();
		//プレイヤーの位置と向きから発射する
		shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
	}

	//果てが来てしまうのでプレイヤーと一緒に動かす
	skyBox.GetComponent<SkyBoxComponent>().SetPos(ComAssist::GetPos(player));
	//効果音のListenerをセットする
	enemy.GetComponent<ThiefComponent>().SetListenerPos(ComAssist::GetPos(player));
	//追跡対象をセットし対象を追跡する
	enemy.GetComponent<ThiefComponent>().SetTrackingTarget(topping);

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
	GetParticle().UpDate(Camera(player.GetComponent<CameraComponent>().GetCamera3D()));
}

void GameController::Draw2D()
{
	Mouse::DrawCursor(false);
	player.GetComponent<CameraComponent>().Project2D();

	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->Draw2D();
	}

	auto& gameScene(entityManager.GetGroup(GAME));
	for (auto& it : gameScene)
	{
		it->Draw2D();
	}

	canvas.GetComponent<MiniMapComponent>().DrawEntityes(topping, player);
	canvas.GetComponent<MiniMapComponent>().DrawEntityes(enemy, player);
	
}

void GameController::Finalize()
{

}
