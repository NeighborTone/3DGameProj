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
#include "../ECS/Components/BGMComponent.h"

#include <iostream>

GameController::GameController() :
	player(entityManager.AddEntity()),
	shot(entityManager.AddEntity()),
	skyBox(entityManager.AddEntity()),
	enemy(entityManager.AddEntity()),
	field(entityManager.AddEntity()),
	alwaysCanvas(entityManager.AddEntity()),
	tomato(entityManager.AddEntity()),
	gameMaster(entityManager.AddEntity()),
	pauseController(entityManager.AddEntity()),
	titleController(entityManager.AddEntity()),
	endController(entityManager.AddEntity())
{
	AsetManager::LoadAset();

	gameMaster.AddComponent<GameStateComponent>();
	gameMaster.AddComponent<BGMComponent>();
	player.AddComponent<TransformComponent>(Pos(0, 15, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();
	player.AddComponent<CursorComponent>();
	shot.AddComponent<InputShotComponent>(50.0f, 20, 0.3f);
	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	enemy.AddComponent<UFOComponent>();
	alwaysCanvas.AddComponent<MiniMapComponent>();
	alwaysCanvas.AddComponent<ScoreBoardComponent>();
	pauseController.AddComponent<PauseComponent>();
	tomato.AddComponent<TomatoComponent>();
	titleController.AddComponent<TitleComponent>();
	titleController.AddComponent<HowToPlayComponent>();
	endController.AddComponent<EndComponent>();
	endController.AddComponent<RankingComponent>();
	
	//�O���[�v�ɓo�^
	titleController.AddGroup(GROUP::TITLE);
	gameMaster.AddGroup(GROUP::ALWAYS);
	skyBox.AddGroup(GROUP::ALWAYS);
	field.AddGroup(GROUP::ALWAYS);
	alwaysCanvas.AddGroup(GROUP::ALWAYS);
	tomato.AddGroup(GROUP::GAME);
	player.AddGroup(GROUP::GAME);
	shot.AddGroup(GROUP::GAME);
	enemy.AddGroup(GROUP::GAME);
	pauseController.AddGroup(GROUP::PAUSE);
	endController.AddGroup(GROUP::END);
	
}

void GameController::CollisionEvent()
{
	enemy.GetComponent<UFOComponent>().Damaged(shot);
	tomato.GetComponent<TomatoComponent>().ToBeKidnapped(enemy);
}

void GameController::Title(const GameState& state)
{
	if (state == GameState::TITLE)
	{
		auto& titleScene(entityManager.GetGroup(GROUP::TITLE));
		for (auto& it : titleScene)
		{
			it->UpDate();
		}
		//�^�C�g������҂���Q�[���̏�Ԃ��󂯎��
		gameMaster.GetComponent<GameStateComponent>().SetState(
			ComAssist::GetState<TitleComponent>(titleController));
		//BGM�̃��C�����������[�v�����邩�Ď�
		gameMaster.GetComponent<BGMComponent>().StartMain(
			titleController.GetComponent<TitleComponent>().IsPlay());
		
	}
}

void GameController::Play(const GameState& state)
{
	if (state == GameState::PLAY)
	{
		auto& gameScene(entityManager.GetGroup(GROUP::GAME));
		for (auto& it : gameScene)
		{
			it->UpDate();
		}
		//�Փ˂������̃C�x���g����
		CollisionEvent();
		//�v���C���[�̈ʒu�ƌ������甭�˂���
		shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
		//�g�}�g��0�ɂȂ�ƃQ�[���G���h
		gameMaster.GetComponent<GameStateComponent>().SetEntity(tomato);
		//�c�莞�Ԃɉ����ďo�����@���ω�����
		enemy.GetComponent<UFOComponent>().SetTimeLimit(
		gameMaster.GetComponent<TimerComponent>().GetTimeLimit());
	}
}

void GameController::Pause(const GameState& state)
{
	if (state == GameState::PAUSE)
	{
		auto& pause(entityManager.GetGroup(GROUP::PAUSE));
		for (auto& it : pause)
		{
			it->UpDate();
		}
		//�|�[�Y����҂���Q�[���̏�Ԃ��󂯎��
		gameMaster.GetComponent<GameStateComponent>().SetState(
			ComAssist::GetState<PauseComponent>(pauseController));
	}
}

void GameController::End(const GameState& state)
{
	if (state == GameState::END)
	{
		auto& end(entityManager.GetGroup(GROUP::END));
		for (auto& it : end)
		{
			it->UpDate();
		}
		//END��Ԃ̎���life0��UFO���c��ƃX�R�A�����Z���ꑱ����̂ŏ����Ă���
		enemy.DeleteComponent<UFOComponent>();
		//�g�}�g�̎c����ɂ���ă{�[�i�X��ǉ�����
		alwaysCanvas.GetComponent<ScoreBoardComponent>().CheckTomatoes(
			tomato.GetComponent<TomatoComponent>().GetData());
		//�����L���O�X�V
		endController.GetComponent<RankingComponent>().SetScore(
			alwaysCanvas.GetComponent<ScoreBoardComponent>().GetScore());
		//�Q�[���G���h����҂���Q�[���̏�Ԃ��󂯎��
		gameMaster.GetComponent<GameStateComponent>().SetState(
			ComAssist::GetState<EndComponent>(endController));
		
	}
}

void GameController::Always()
{
	auto& always(entityManager.GetGroup(GROUP::ALWAYS));
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
	const auto& state = ComAssist::GetGameState(gameMaster);
	if (state == GameState::RESET)
	{
		enemy.DeleteComponent<UFOComponent>();
		enemy.AddComponent<UFOComponent>();
		entityManager.Initialize();
	}

	//�G�����񂾂�X�R�A�𑝂₷
	alwaysCanvas.GetComponent<ScoreBoardComponent>().SetEntity(enemy);
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
	enemy.GetComponent<UFOComponent>().SetTrackingTarget(tomato);
	//�Q�[���̏�Ԃɉ����ăX�R�AUI������������
	alwaysCanvas.GetComponent<ScoreBoardComponent>().SetState(state);
	//�Q�[���I�����ɑS����
	tomato.GetComponent<TomatoComponent>().EndRefresh(state);
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
	auto& always(entityManager.GetGroup(GROUP::ALWAYS));
	auto& gameScene(entityManager.GetGroup(GROUP::GAME));
	//��ɏ����������̂���O�ɕ`�悳���
	if (state == GameState::END)
	{
		auto& end(entityManager.GetGroup(GROUP::END));
		for (auto& it : end)
		{
			it->Draw2D();
		}
	}
	for (auto& it : always)
	{
		it->Draw2D();
	}
	alwaysCanvas.GetComponent<MiniMapComponent>().DrawEntityes(tomato, player);
	alwaysCanvas.GetComponent<MiniMapComponent>().DrawEntityes(enemy, player);
	for (auto& it : gameScene)
	{
		it->Draw2D();
	}
	if (state == GameState::TITLE)
	{
		auto& title(entityManager.GetGroup(GROUP::TITLE));
		for (auto& it : title)
		{
			it->Draw2D();
		}
	}
	if(state == GameState::PAUSE)
	{
		auto& pause(entityManager.GetGroup(GROUP::PAUSE));
		for (auto& it : pause)
		{
			it->Draw2D();
		}
	}
	
}

void GameController::Finalize()
{

}
