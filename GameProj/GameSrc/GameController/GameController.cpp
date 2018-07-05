#include "GameController.h"

GameController::GameController():
	cameraMan(entMane.AddEntity()),
	me(entMane.AddEntity())

{
	cameraMan.AddComponent<CameraComponent>();
	me.AddComponent<SpriteComponent>("Resource/Texture/cursor.png");
	me.AddComponent<MeshComponent>("Resource/Texture/stonewall_diff.jpg");
}

GameController::~GameController()
{

}

void GameController::Init()
{
	entMane.Init();

}

void GameController::UpDate()
{
	entMane.Refresh();
	entMane.UpDate();
}

void GameController::Draw3D()
{
	cameraMan.GetComponent<CameraComponent>().Project3D();
	entMane.Draw3D();
}

void GameController::Draw2D()
{
	cameraMan.GetComponent<CameraComponent>().Project2D();
	entMane.Draw2D();
}

void GameController::Finalize()
{
}
