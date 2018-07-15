#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/MeshComponent.h"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include "../ECS/Components/FieldComponent.h"
#include "../ECS/Components/ThiefComponent.h"
#include <iostream>

GameController::GameController() :
	player(entityManager.AddEntity()),
	shot(entityManager.AddEntity()),
	skyBox(entityManager.AddEntity()),
	enemy(entityManager.AddEntity()),
	hoge(entityManager.AddEntity()),
	field(entityManager.AddEntity())
{
	player.AddComponent<TransformComponent>(Pos(0, 10, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();

	shot.AddComponent<InputShotComponent>(15.0f, 30, 0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	enemy.AddComponent<ThiefComponent>(1, 2.5f);
	//Testコード

	ef.AddEffect("test", "Resource/Effect/testEf.efk");
	ef.AddEffect("sky", "Resource/Effect/stars.efk");
	sound.Load("Resource/Sounds/se.ogg", true);
	handle = ef.Play("sky", Vec3(0, 0, 0));
}

GameController::~GameController()
{

}

void GameController::CollisionEvent()
{
	for (auto& it : enemy.GetComponent<ThiefComponent>().Get())
	{
		if (!it->isActive)
		{
			continue;
		}
		if (shot.GetComponent<InputShotComponent>().IsHit
		(
			AABB(Pos(it->mesh.pos),
			Scale(it->mesh.scale /2)))
		)
		{
			//Testコード
			ef.Play("test", Pos(it->mesh.pos));
			sound.UpDate3DSound(Pos(it->mesh.pos), ComAssist::GetPos(player));
			sound.PlaySE();
			--it->life;
		}
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
