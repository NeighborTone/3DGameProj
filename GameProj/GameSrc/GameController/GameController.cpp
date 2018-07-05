#include "GameController.h"

GameController::GameController():
	cameraMan(entityManager.AddEntity()),
	me(entityManager.AddEntity())
{
	cameraMan.AddComponent<CameraComponent>();
	me.AddComponent<SpriteComponent>("Resource/Texture/cursor.png");
	me.AddComponent<MeshComponent>("Resource/Texture/stonewall_diff.jpg");
	me.AddComponent<ParticleComponent>("Resource/Effect/testEf.efk");
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
	me.GetComponent<ParticleComponent>().Play();
}

void GameController::Draw3D()
{
	cameraMan.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
	entityManager.UpDate3DParticle(cameraMan.GetComponent<CameraComponent>().GetCamera3D());
}

void GameController::Draw2D()
{
	cameraMan.GetComponent<CameraComponent>().Project2D();
	entityManager.Draw2D();
}

void GameController::Finalize()
{

}
