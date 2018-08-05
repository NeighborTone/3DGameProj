#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "ComponentData/MetaData.hpp"
#include <vector>
class ScoreBoardComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 30;
	Float4 colorDelta;	//�F�̕ω���
	Text scoreText;
	ScoreData scoreData;		//�X�R�A�i�[�p
	ScoreData comboData;	//�R���{�\���p
	std::vector<std::unique_ptr<ScoreData>> effects;	//���Z�����l�\���p
	std::unique_ptr<ScoreData> AddData();
	//�����ɓ��ꂽ�l�̌�����Ԃ��֐�
	const unsigned GetDigit(unsigned num) const;
	//�s�v�ɂȂ����X�R�A�G�t�F�N�g��j������
	void RefreshEffects();
	//�F���O���f�[�V����������
	void GradationColor();
public:
	ScoreBoardComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//��ɓ��ꂽ���X�R�A���擾
	const int GetScore() const;
	//�����ɓ��ꂽ�G���E���ꂽ��X�R�A�����Z�����
	void SetEntity(const Entity& enemy);
	//�Q�[���̏�Ԃɉ���������������
	void CheckState(const GameState& state);
};