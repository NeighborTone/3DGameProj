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
	//�n�C�X�R�A���X�V���ꂽ��
	bool isUpDateRanking;
	//�����L���O�\�����I�������邩
	bool isReset;
	//�n�C�X�R�A���������ꍇ�F��ς��邽�߂̃t���O
	bool isSetColor;
	//�ۑ����Ă���X�R�A�����L���O�̓ǂݍ���
	void LoadScoreData();
	//�X�R�A�����L���O�̏�������
	void WrightScoreData();
	std::array<RankData,MAX> data;
	std::unique_ptr<Text> text;
	Easing reduction;
public:
	RankingComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//�X�R�A�̃Z�b�g
	void SetScore(const long long& score);
	//�����L���O�̃A�j���[�V�������I���������Ԃ�
	const bool IsMoveEnd();
};