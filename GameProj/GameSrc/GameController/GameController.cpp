#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/GroundComponent.hpp"


GameController::GameController():
	Player(entityManager.AddEntity()),
	ground(entityManager.AddEntity())
{
	Player.AddComponent<TransformComponent>(Pos(0, 5, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	Player.AddComponent<InuputMoveComponent>(0.1f);
	Player.AddComponent<CameraComponent>();

	ground.AddComponent<GroundComponent>(Pos(0, 0, 0), Angles(0, 0, 0), Scale(30, 2, 30));

	Mouse::SetMousePos(0, 0);
}

GameController::~GameController()
{

}

void GameController::Init()
{
	entityManager.Initialize();
}

void GameController::UpDate()
{
	entityManager.Refresh();
	entityManager.UpDate();
}

void GameController::Draw3D()
{
	Player.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
}

void GameController::Draw2D()
{
	Player.GetComponent<CameraComponent>().Project2D();
	entityManager.Draw2D();
}

void GameController::Finalize()
{

}
