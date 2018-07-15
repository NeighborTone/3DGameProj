#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/MeshComponent.h"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include "../ECS/Components/FieldComponent.h"
#include "../ECS/Components/ThiefComponent.h"
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
	field(entityManager.AddEntity())
{
	GetParticle().AddEffect("expro", "Resource/Effect/testEf.efk");
	GetParticle().AddEffect("sky", "Resource/Effect/stars.efk");
	GetParticle().AddEffect("app", "Resource/Effect/Appear.efk");
	player.AddComponent<TransformComponent>(Pos(0, 10, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();

	shot.AddComponent<InputShotComponent>(15.0f, 30, 0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	thief.AddComponent<ThiefComponent>(2.5f);
	//Testコード
	sound.Load("Resource/Sounds/se.ogg", true);
	
}

GameController::~GameController()
{

}

void GameController::CollisionEvent()
{
	for (auto& it : thief.GetComponent<ThiefComponent>().Get())
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
			GetParticle().Play("expro", Pos(it->mesh.pos));
			sound.UpDate3DSound(Pos(it->mesh.pos), ComAssist::GetPos(player));
			sound.PlaySE();
			//これは今後エネミーの内部で行う
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
	//Test
	if (KeyBoard::Down(KeyBoard::Key::KEY_X))
	{
		entityManager.Initialize();
	}
	//
	entityManager.Refresh();
	entityManager.UpDate();
	shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
	CollisionEvent();
	//Test
	skyBox.GetComponent<SkyBoxComponent>().SetPos(ComAssist::GetPos(player));
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
