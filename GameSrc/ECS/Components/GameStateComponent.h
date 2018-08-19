#pragma once
#include "../ECS.hpp"
#include "../../Utilitys/Counter.hpp"
#include "ComponentData/MetaData.hpp"
#include "TimerComponent.h"
//�Q�[���̏�Ԃ��Ď����܂�
//���̃R���|�[�l���g�����Ԃ��󂯎��AGameContoller�ɓ`���܂�
class GameStateComponent : public Component
{
private:
	TimerComponent* timer;
	GameState state;
	void GamePause();
	void GameEnd();
	void TimerRun();
public:
	//�ق��̃R���|�[�l���g�����Ԃ��󂯎��
	void SetState(const GameState& state_);
	//���݂̃Q�[���̏�Ԃ�Ԃ�
	[[nodiscard]] const GameState GetCurrentState() const;
	//Entity�̏�Ԃ����ԑJ��
	void SetEntity(const Entity& entity);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() STUB
};