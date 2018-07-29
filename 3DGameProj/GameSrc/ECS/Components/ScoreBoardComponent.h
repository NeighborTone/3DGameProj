#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "ComponentData/MetaData.hpp"
class ScoreBoardComponent : public Component
{
private:
	const std::string font = "���C���I";
	static constexpr float size = 30;
	Float4 colorDelta;
	struct Data
	{
		Float4 color;
		TransForm trans;
		Text number;
		int score;
	};
	Data data;
	const unsigned GetDigit(unsigned num) const;
public:
	ScoreBoardComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//�����ɓ��ꂽ�G���E������X�R�A�����Z�����
	const void SetEntity(const Entity& enemy);
};