#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "ComponentData/MetaData.hpp"
#include <array>

class RankingComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 30;
	bool isUpDateRanking;
	bool isReset;
	//�ۑ����Ă���X�R�A�����L���O�̓ǂݍ���
	void LoadScoreData();
	//�X�R�A�����L���O�̏�������
	void WrightScoreData();
	static constexpr int MAX = 5;
	std::array<ScoreData,MAX> data;
	Text text;
	Easing reduction;
public:
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//�X�R�A�̃Z�b�g
	void SetScore(const int& score);
	//�����L���O�̃A�j���[�V�������I���������Ԃ�
	bool IsMoveEnd();
};