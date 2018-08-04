#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include "../ECS/Components/FieldComponent.h"
#include "../ECS/Components/UFOComponent.h"
#include "../ECS/Components/MiniMapComponent.h"
#include "../ECS/Components/TomatoComponent.h"
#include "../ECS/Components/CursorComponent.h"
#include "../ECS/Components/ScoreBoardComponent.h"
#include "../ECS/Components/GameStateComponent.h"
#include "../ECS/Components/PauseComponent.h"
#include "../ECS/Components/TitleComponent.h"
#include "../ECS/Components/EndComponent.h"
#include <iostream>

GameController::GameController() :
	player(entityManager.AddEntity()),
	shot(entityManager.AddEntity()),
	skyBox(entityManager.AddEntity()),
	enemy(entityManager.AddEntity()),
	field(entityManager.AddEntity()),
	gameCanvas(entityManager.AddEntity()),
	topping(entityManager.AddEntity()),
	gameMaster(entityManager.AddEntity()),
	pauseController(entityManager.AddEntity()),
	titleController(entityManager.AddEntity()),
	endController(entityManager.AddEntity())
{
	AsetManager::LoadAset();
	//$Test$
	bgm.Load("Resource/Sounds/spacewar.wav",false);
	bgm.PlayBGM(255,0.15f);

	gameMaster.AddComponent<GameStateComponent>();
	player.AddComponent<TransformComponent>(Pos(0, 15, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();
	player.AddComponent<CursorComponent>();
	shot.AddComponent<InputShotComponent>(40.0f, 20, 0.3f);

	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	enemy.AddComponent<UFOComponent>();
	gameCanvas.AddComponent<MiniMapComponent>();
	gameCanvas.AddComponent<ScoreBoardComponent>();
	pauseController.AddComponent<PauseComponent>();
	topping.AddComponent<TomatoComponent>();
	titleController.AddComponent<TitleComponent>();
	endController.AddComponent<EndComponent>();
	endController.AddComponent<RankingComponent>();
	//�O���[�v�ɓo�^
	titleController.AddGroup(TITLE);
	gameMaster.AddGroup(ALWAYS);
	skyBox.AddGroup(ALWAYS);
	field.AddGroup(ALWAYS);
	gameCanvas.AddGroup(ALWAYS);
	topping.AddGroup(GAME);
	player.AddGroup(GAME);
	shot.AddGroup(GAME);
	enemy.AddGroup(GAME);
	pauseController.AddGroup(PAUSE);
	endController.AddGroup(END);
}

void GameController::CollisionEvent()
{
	enemy.GetComponent<UFOComponent>().Damaged(shot);
	topping.GetComponent<TomatoComponent>().ToBeKidnapped(enemy);
}

const void GameController::Title(const GameState& state)
{
	if (state == GameState::TITLE)
	{
		auto& titleScene(entityManager.GetGroup(TITLE));
		for (auto& it : titleScene)
		{
			it->UpDate();
		}
		//�^�C�g������Q�[���̏�Ԃ��󂯎��
		gameMaster.GetComponent<GameStateComponent>().SetState(
			titleController.GetComponent<TitleComponent>().GetState());
	}
}

const void GameController::Play(const GameState& state)
{
	if (state == GameState::PLAY)
	{
		auto& gameScene(entityManager.GetGroup(GAME));
		for (auto& it : gameScene)
		{
			it->UpDate();
		}
		//�Փ˂������̃C�x���g����
		CollisionEvent();
		//�v���C���[�̈ʒu�ƌ������甭�˂���
		shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
		//�g�}�g��0�ɂȂ�ƃQ�[���G���h
		gameMaster.GetComponent<GameStateComponent>().SetEntity(topping);
	
	}
}

const void GameController::Pause(const GameState& state)
{
	if (state == GameState::PAUSE)
	{
		auto& pause(entityManager.GetGroup(PAUSE));
		for (auto& it : pause)
		{
			it->UpDate();
		}
		gameMaster.GetComponent<GameStateComponent>().SetState(
			pauseController.GetComponent<PauseComponent>().GetState());
	}
}

const void GameController::End(const GameState& state)
{
	if (state == GameState::END)
	{
		auto& end(entityManager.GetGroup(END));
		for (auto& it : end)
		{
			it->UpDate();
		}
		//END��Ԃ̎���life0��UFO���c��ƃX�R�A�����Z���ꑱ����̂ŏ����Ă���
		enemy.DeleteComponent<UFOComponent>();

		endController.GetComponent<RankingComponent>().SetScore(
			gameCanvas.GetComponent<ScoreBoardComponent>().GetScore());
		gameMaster.GetComponent<GameStateComponent>().SetState(
			endController.GetComponent<EndComponent>().GetState());
	}
	
}

const void GameController::Always()
{
	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->UpDate();
	}
}

void GameController::Initialize()
{
	entityManager.Initialize();
}

void GameController::UpDate()
{
	const auto&& state = ComAssist::GetGameState(gameMaster);
	if (state == GameState::RESET)
	{
		enemy.DeleteComponent<UFOComponent>();
		enemy.AddComponent<UFOComponent>();
		entityManager.Initialize();
	}

	//�G�����񂾂�X�R�A�𑝂₷
	gameCanvas.GetComponent<ScoreBoardComponent>().SetEntity(enemy);
	Always();
	Title(state);
	Play(state);
	Pause(state);
	End(state);
	//Entity�̏�Ԃ̊Ď�
	entityManager.Refresh();
	//�ʂĂ����Ă��܂��̂Ńv���C���[�ƈꏏ�ɓ�����
	skyBox.GetComponent<SkyBoxComponent>().SetPos(ComAssist::GetPos(player));
	//���ʉ���Listener���Z�b�g����B�������������Ȃ����Ƃ�����̂�Entity�̍X�V�̌�ɌĂ�
	enemy.GetComponent<UFOComponent>().SetListenerPos(ComAssist::GetPos(player));
	//�ǐՑΏۂ��Z�b�g���Ώۂ�ǐՂ���
	enemy.GetComponent<UFOComponent>().SetTrackingTarget(topping);
	//�Q�[���G���h�Ȃ�X�R�A�{�[�h�𓮂���
	gameCanvas.GetComponent<ScoreBoardComponent>().CheckState(state);
	//�}�E�X�͏�ɉ�ʒ���
	Mouse::SetMousePos(0, 0);

}

void GameController::Draw3D()
{
	player.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
	//���ׂĂ�particle�ɃJ�����̃r���[�ƃv���W�F�N�V������n��
	AsetManager::GetParticle().UpDate(Camera(player.GetComponent<CameraComponent>().GetCamera3D()));
}

void GameController::Draw2D()
{
	Mouse::DrawCursor(false);
	player.GetComponent<CameraComponent>().Project2D();

	const auto&& state = ComAssist::GetGameState(gameMaster);
	auto& always(entityManager.GetGroup(ALWAYS));
	auto& gameScene(entityManager.GetGroup(GAME));
	//��ɏ����������̂���O�ɕ`�悳���
	if (state == GameState::END)
	{
		auto& end(entityManager.GetGroup(END));
		for (auto& it : end)
		{
			it->Draw2D();
		}
	}
	for (auto& it : always)
	{
		it->Draw2D();
	}
	gameCanvas.GetComponent<MiniMapComponent>().DrawEntityes(topping, player);
	gameCanvas.GetComponent<MiniMapComponent>().DrawEntityes(enemy, player);
	for (auto& it : gameScene)
	{
		it->Draw2D();
	}
	if (state == GameState::TITLE)
	{
		auto& title(entityManager.GetGroup(TITLE));
		for (auto& it : title)
		{
			it->Draw2D();
		}
	}
	if(state == GameState::PAUSE)
	{
		auto& pause(entityManager.GetGroup(PAUSE));
		for (auto& it : pause)
		{
			it->Draw2D();
		}
	}
	
}

void GameController::Finalize()
{

}
