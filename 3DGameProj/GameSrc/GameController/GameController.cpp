#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include "../ECS/Components/FieldComponent.h"
#include "../ECS/Components/ThiefComponent.h"
#include "../ECS/Components/MiniMapComponent.h"
#include "../ECS/Components/TomatoComponent.h"
#include "../ECS/Components/CursorComponent.h"
#include "../ECS/Components/ScoreBoardComponent.h"
#include "../ECS/Components/GameStateComponent.h"
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
	enemy(entityManager.AddEntity()),
	field(entityManager.AddEntity()),
	canvas(entityManager.AddEntity()),
	topping(entityManager.AddEntity()),
	gameMaster(entityManager.AddEntity())
{
	gameMaster.AddComponent<GameStateComponent>();
	player.AddComponent<TransformComponent>(Pos(0, 10, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();
	player.AddComponent<CursorComponent>();
	shot.AddComponent<InputShotComponent>(40.0f, 20, 0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	enemy.AddComponent<ThiefComponent>();
	canvas.AddComponent<MiniMapComponent>();
	canvas.AddComponent<ScoreBoardComponent>();
	topping.AddComponent<TomatoComponent>();
	//�O���[�v�ɓo�^
	gameMaster.AddGroup(ALWAYS);
	skyBox.AddGroup(ALWAYS);
	field.AddGroup(ALWAYS);
	topping.AddGroup(GAME);
	canvas.AddGroup(ALWAYS);
	player.AddGroup(GAME);
	shot.AddGroup(GAME);
	enemy.AddGroup(GAME);

}

void GameController::CollisionEvent()
{
	enemy.GetComponent<ThiefComponent>().Damaged(shot);
	topping.GetComponent<TomatoComponent>().ToBeKidnapped(enemy);
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
	//$Test$
	if (ComAssist::GetGameState(gameMaster) == GameState::RESET)
	{
		entityManager.Initialize();
	}
	entityManager.Refresh();	//Entity�̏�Ԃ̊Ď�

	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->UpDate();
	}

	if (ComAssist::GetGameState(gameMaster) == GameState::PLAY)
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
	enemy.GetComponent<ThiefComponent>().SetListenerPos(ComAssist::GetPos(player));
	//�ǐՑΏۂ��Z�b�g���Ώۂ�ǐՂ���
	enemy.GetComponent<ThiefComponent>().SetTrackingTarget(topping);
	//�G�����񂾂�X�R�A�𑝂₷
	canvas.GetComponent<ScoreBoardComponent>().SetEntity(enemy);
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
	//���ׂĂ�particle�ɃJ�����̃r���[�ƃv���W�F�N�V������n��
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

	canvas.GetComponent<MiniMapComponent>().DrawEntityes(topping, player);
	canvas.GetComponent<MiniMapComponent>().DrawEntityes(enemy, player);
}

void GameController::Finalize()
{

}
