#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/GroundComponent.hpp"
#include "../ECS/Components/ShotComponent.h"
#include "../ECS/Components/InputShotComponent.h"

GameController::GameController():
	player(entityManager.AddEntity()),
	ground(entityManager.AddEntity()),
	shot(entityManager.AddEntity())
{
	player.AddComponent<TransformComponent>(Pos(0, 5, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();

	shot.AddComponent<InputShotComponent>(5.0f);
	shot.AddComponent<ShotComponent>();
	
	

	ground.AddComponent<GroundComponent>(Pos(0, 0, 0), Angles(0, 0, 0), Scale(80, 2, 80));
}

GameController::~GameController()
{

}

void GameController::Initialize()
{
	entityManager.Initialize();
}

void GameController::UpDate()
{
	entityManager.Refresh();
	entityManager.UpDate();

	shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
}

void GameController::Draw3D()
{
	player.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
}

void GameController::Draw2D()
{
	player.GetComponent<CameraComponent>().Project2D();
	entityManager.Draw2D();
}

void GameController::Finalize()
{

}
