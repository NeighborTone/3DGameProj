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
	ScoreData boardData;
	ScoreData comboData;
	std::vector<std::unique_ptr<ScoreData>> effects;
	std::unique_ptr<ScoreData> AddData();
	//�����ɓ��ꂽ�l�̌�����Ԃ��֐�
	const unsigned GetDigit(unsigned num) const;
	//�s�v�ɂȂ����X�R�A�G�t�F�N�g��j������
	void RefreshEffedts();
	//�F���O���f�[�V����������
	void GradationColor();
public:
	ScoreBoardComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//�����ɓ��ꂽ�G���E���ꂽ��X�R�A�����Z�����
	void SetEntity(const Entity& enemy);
	//�Q�[���̏�Ԃɉ����ăA�j���[�V��������
	void CheckState(const GameState& state);
};