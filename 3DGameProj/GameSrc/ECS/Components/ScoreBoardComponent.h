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
	Float4 colorDelta;
	Text score;
	Text scoreEffect;
	ScoreData data;
	std::vector<std::unique_ptr<ScoreData>> effects;
	std::unique_ptr<ScoreData> AddData();
	void CreateEffect();
	const unsigned GetDigit(unsigned num) const;
public:
	ScoreBoardComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//�����ɓ��ꂽ�G���E���ꂽ��X�R�A�����Z�����
	void SetEntity(const Entity& enemy);
	//�Q�[���̏�Ԃ�End�Ȃ�A�j���[�V��������
	void CheckState(const GameState& state);
};