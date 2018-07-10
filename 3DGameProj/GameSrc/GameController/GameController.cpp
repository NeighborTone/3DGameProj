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
	player.AddComponent<TransformComponent>(Pos(0, 5, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();

	shot.AddComponent<InputShotComponent>(5.0f,30,0.5f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky.png");

	hoge.AddComponent<MeshComponent>("Resource/Texture/stonewall_diff.jpg", "Resource/Shader/hoge.hlsl").CreateSphere();
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

	for (const auto& it : shot.GetComponent<InputShotComponent>().GetShots())
	{
		if (!it.isActive)
		{
			continue;
		}
		if (Collison::SphereCollision(Sphere(Pos(it.mesh.pos), it.radius_), Sphere(ComAssist::GetPos(hoge), 0.5f)))
		{
			static int a = 0;
			++a;
			std::cout << "hoge!!!!!!!!!!!!!!!!!!!!!" << a << std::endl;
		}
	}
	
}

void GameController::Draw3D()
{
	player.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
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
