#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include "../ECS/Components/FieldComponent.h"
#include "../ECS/Components/ThiefComponent.h"
#include "../ECS/Components/MiniMapComponent.h"
#include <iostream>


void GameController::StateMachine()
{
	GameStart();
	GameStop();
}
//$Test$
void GameController::GameStart()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_C))
	{
		gameState = GameState::PLAY;
	}
}
//$Test$
void GameController::GameStop()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_V))
	{
		gameState = GameState::STOP;
	}
}

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
	field(entityManager.AddEntity()),
	map(entityManager.AddEntity())
{
	gameState = GameState::STOP;
	player.AddComponent<TransformComponent>(Pos(0, 10, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();

	shot.AddComponent<InputShotComponent>(28.0f, 30, 0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	thief.AddComponent<ThiefComponent>(2.5f);
	map.AddComponent<MiniMapComponent>();

	//�O���[�v�ɓo�^
	player.AddGroup(GAME);
	skyBox.AddGroup(ALWAYS);
	field.AddGroup(ALWAYS);
	map.AddGroup(ALWAYS);
	shot.AddGroup(GAME);
	thief.AddGroup(GAME);

}

void GameController::CollisionEvent()
{
	thief.GetComponent<ThiefComponent>().Damaged(shot);
}

void GameController::Initialize()
{
	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->Initialize();
	}
	auto& gameScene(entityManager.GetGroup(GAME));
	for (auto& it : gameScene)
	{
		it->Initialize();
	}
}

void GameController::UpDate()
{
	StateMachine();	//�Q�[���̏�Ԃ̊Ď�
	//$Test$
	if (KeyBoard::Down(KeyBoard::Key::KEY_X))
	{
		entityManager.Initialize();
	}

	entityManager.Refresh();	//Entity�̏�Ԃ̊Ď�

	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->UpDate();
	}

	if (gameState == GameState::PLAY)
	{
		auto& gameScene(entityManager.GetGroup(GAME));
		for (auto& it : gameScene)
		{
			it->UpDate();
		}
		CollisionEvent();
		//�v���C���[�̈ʒu�ƌ������甭�˂���
		shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
	}

	//�ʂĂ����Ă��܂��̂Ńv���C���[�ƈꏏ�ɓ�����
	skyBox.GetComponent<SkyBoxComponent>().SetPos(ComAssist::GetPos(player));
	//���ʉ���Listener���Z�b�g����
	thief.GetComponent<ThiefComponent>().SetListenerPos(ComAssist::GetPos(player));
	//�}�E�X�͏�ɉ�ʒ���
	Mouse::SetMousePos(0, 0);
}

void GameController::Draw3D()
{
	player.GetComponent<CameraComponent>().Project3D();

	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->Draw3D();
	}

	auto& gameScene(entityManager.GetGroup(GAME));
	for (auto& it : gameScene)
	{
		it->Draw3D();
	}


	GetParticle().UpDate(Camera(player.GetComponent<CameraComponent>().GetCamera3D()));
}

void GameController::Draw2D()
{
	Mouse::DrawCursor(false);
	player.GetComponent<CameraComponent>().Project2D();

	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->Draw2D();
	}

	auto& gameScene(entityManager.GetGroup(GAME));
	for (auto& it : gameScene)
	{
		it->Draw2D();
	}


	map.GetComponent<MiniMapComponent>().DrawEnemys(thief, player);
}

void GameController::Finalize()
{

}
