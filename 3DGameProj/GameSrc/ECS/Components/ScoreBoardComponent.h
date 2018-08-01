#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "ComponentData/MetaData.hpp"

class ScoreBoardComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 30;
	Float4 colorDelta;
	struct Data
	{
		Easing ease;
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
	//引数に入れた敵が殺されたらスコアが加算される
	void SetEntity(const Entity& enemy);
	//ゲームの状態がEndならアニメーションする
	void CheckState(const GameState& state);
};