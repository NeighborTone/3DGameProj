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
	static constexpr int MAX = 5;
	bool isUpDateRanking;
	bool isReset;
	bool isSetColor;
	//�ۑ����Ă���X�R�A�����L���O�̓ǂݍ���
	void LoadScoreData();
	//�X�R�A�����L���O�̏�������
	void WrightScoreData();
	std::array<RankData,MAX> data;
	Text text;
	Easing reduction;
public:
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//�X�R�A�̃Z�b�g
	void SetScore(const long long& score);
	//�����L���O�̃A�j���[�V�������I���������Ԃ�
	const bool IsMoveEnd();
};