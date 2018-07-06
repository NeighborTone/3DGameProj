#include "GameController.h"

GameController::GameController():
	Player(entityManager.AddEntity()),
	ground(entityManager.AddEntity())
{
	Player.AddComponent<TransformComponent>(Pos(0, 5, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	Player.AddComponent<InuputComponent>(0.1f);
	Player.AddComponent<CameraComponent>();

	ground.AddComponent<TransformComponent>(Pos(0, 0, 0), Velocity(0, 0, 0), Angles(0, 0, 0), Scale(30, 2, 30));
	ground.AddComponent<MeshComponent>("Resource/Texture/stonewall_diff.jpg", "Resource/Shader/hoge.hlsl").CreateSphere();

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
