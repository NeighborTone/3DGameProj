#pragma once
#include "../ECS.hpp"
#include "../../Utilitys/Counter.hpp"
#include "ComponentData/MetaData.hpp"

//�Q�[���̏�Ԃ��Ď����܂�
//���̃R���|�[�l���g���烁�b�Z�[�W���󂯎��AGameContoller�ɓ`���܂�
class GameStateComponent : public Component
{
private:
	static constexpr int TimeLimit = 20'000;
	Counter cnt;
	GameState state;
	void GamePause();
	void GameEnd();
	void TimerRun();
	Text text;
public:
	GameStateComponent();
	//�ق��̃R���|�[�l���g���烁�b�Z�[�W���󂯎��
	void SetState(const GameState& state_);
	//���݂̃Q�[���̏�Ԃ�Ԃ�
	const GameState GetCurrentState() const;
	//�g�}�g��0�Ȃ狭���I��END
	void SetEntity(const Entity& tomato);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() STUB
};