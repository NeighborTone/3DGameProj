#include "GameController.h"

GameController::GameController():
	cameraMan(entityManager.AddEntity())
{
	cameraMan.AddComponent<TransformComponent>(Vec3(0, 5, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(1, 1, 1));
	cameraMan.AddComponent<InuputComponent>();
	cameraMan.AddComponent<CameraComponent>();
	tex.Load("Resource/Texture/stonewall_diff.jpg");
	me.scale = 30;
	me.scale.y = 1;
	me.CreateCube();
	me.GetMaterial().SetTexture(0, &tex);

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
	cameraMan.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
	me.Draw();
}

void GameController::Draw2D()
{
	cameraMan.GetComponent<CameraComponent>().Project2D();
	entityManager.Draw2D();
}

void GameController::Finalize()
{

}
