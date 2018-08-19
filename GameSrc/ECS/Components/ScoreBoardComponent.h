#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "ComponentData/MetaData.hpp"
#include <vector>
class ScoreBoardComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 40;
	bool isAddTomatoesScore;
	size_t tomatoNum;
	std::unique_ptr<Text> scoreText;
	std::unique_ptr<Text> bonusText;
	//�X�R�A�i�[�p
	ScoreData scoreData;
	//�R���{�\���p
	ScoreData comboData;		
	//�g�}�g���̃X�R�A���Z���o�p
	ScoreData tomatoScoreData;	
	//���Z�����l�\���p
	std::vector<std::unique_ptr<ScoreData>> effects;
	//�R���{�\���p�̃f�[�^��ǉ�����
	std::unique_ptr<ScoreData> AddData();
	//�����ɓ��ꂽ�l�̌�����Ԃ��֐�
	const unsigned GetDigit(long long num) const;
	//�s�v�ɂȂ����X�R�A�G�t�F�N�g��j������
	void RefreshEffects();
	//�F���O���f�[�V����������
	void GradationColor();

	void EffectUpDate();
	void ComboUpDate();
	void BoardUpDate();

public:
	ScoreBoardComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//��ɓ��ꂽ���X�R�A���擾
	const long long GetScore() const;
	//�����ɓ��ꂽ�G���E���ꂽ��X�R�A�����Z�����
	void SetEntity(const Entity& enemy);
	//�g�}�g�̌��ɉ����ē��_�����Z
	void CheckTomatoes(const std::vector<TomatoData>& tomats);
	//�Q�[���̏�Ԃɉ���������������
	void SetState(const GameState& state);
};