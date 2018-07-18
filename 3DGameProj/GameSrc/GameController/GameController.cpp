#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include "../ECS/Components/FieldComponent.h"
#include "../ECS/Components/ThiefComponent.h"
#include "../ECS/Components/MiniMapComponent.h"
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
	thief(entityManager.AddEntity()),
	field(entityManager.AddEntity()),
	map(entityManager.AddEntity())
{
	player.AddComponent<TransformComponent>(Pos(0, 10, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();

	shot.AddComponent<InputShotComponent>(15.0f, 30, 0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	thief.AddComponent<ThiefComponent>(2.5f);
	map.AddComponent<MiniMapComponent>();
}

void GameController::CollisionEvent()
{
	thief.GetComponent<ThiefComponent>().Damaged(shot);
}

void GameController::Initialize()
{
	entityManager.Initialize();
}

void GameController::UpDate()
{
	//Test
	if (KeyBoard::Down(KeyBoard::Key::KEY_X))
	{
		entityManager.Initialize();
	}
	entityManager.Refresh();
	entityManager.UpDate();
	CollisionEvent();
	
	//プレイヤーの位置と向きから発射する
	shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
	//果てが来てしまうのでプレイヤーと一緒に動かす
	skyBox.GetComponent<SkyBoxComponent>().SetPos(ComAssist::GetPos(player));
	//効果音のListenerをセットする
	thief.GetComponent<ThiefComponent>().SetListenerPos(ComAssist::GetPos(player));
}

void GameController::Draw3D()
{
	player.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
	GetParticle().UpDate(Camera(player.GetComponent<CameraComponent>().GetCamera3D()));
}

void GameController::Draw2D()
{
	Mouse::DrawCursor(false);
	player.GetComponent<CameraComponent>().Project2D();
	entityManager.Draw2D();
}

void GameController::Finalize()
{

}
