#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/GroundComponent.hpp"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include <iostream>

GameController::GameController():
	player(entityManager.AddEntity()),
	shot(entityManager.AddEntity()),
	skyBox(entityManager.AddEntity()),
	hoge(entityManager.AddEntity())
{
	player.AddComponent<TransformComponent>(Pos(0, 10, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();

	shot.AddComponent<InputShotComponent>(2.2f,30,0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");

	//Testコード
	t.Load("Resource/Texture/w.png");
	ground.GetMaterial().SetTexture(0,&t);
	ground.CreateSphere();
	ground.scale = 1000;
	ground.scale.y = 1;
	hoge.AddComponent<MeshComponent>("Resource/Texture/stonewall_diff.jpg", "Resource/Shader/hoge.hlsl").CreateSphere();
	hoge.GetComponent<TransformComponent>().pos.y = 10;
	hoge.GetComponent<TransformComponent>().pos.z = 10;

	ef.AddEffect("test","Resource/Effect/testEf.efk");
	ef.AddEffect("sky", "Resource/Effect/stars.efk");
	sound.Load("Resource/Sounds/se.ogg",true);
	handle = ef.Play("sky", Vec3(0, 0, 0));
}

GameController::~GameController()
{

}

void GameController::CollisionEvent()
{
	if (shot.GetComponent<InputShotComponent>().IsHit(Sphere(ComAssist::GetPos(hoge), 0.8f)))
	{
		//Testコード
		ef.Play("test", ComAssist::GetPos(hoge));
		sound.UpDate3DSound(ComAssist::GetPos(hoge), ComAssist::GetPos(player));
		sound.PlaySE();
		
	}
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
	CollisionEvent();
	//Test
	skyBox.GetComponent<SkyBoxComponent>().SetPos(ComAssist::GetPos(player));
	ef.SetPos(handle, Vec3(ComAssist::GetPos(player)));

}

void GameController::Draw3D()
{
	player.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
	//Testコード
	ground.Draw();
	ef.UpDate(Camera(player.GetComponent<CameraComponent>().GetCamera3D()));
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
