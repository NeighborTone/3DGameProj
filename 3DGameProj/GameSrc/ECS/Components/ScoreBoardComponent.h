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
	Float4 colorDelta;	//色の変化量
	Text scoreText;
	ScoreData boardData;
	ScoreData comboData;
	std::vector<std::unique_ptr<ScoreData>> effects;
	std::unique_ptr<ScoreData> AddData();
	//引数に入れた値の桁数を返す関数
	const unsigned GetDigit(unsigned num) const;
	//不要になったスコアエフェクトを破棄する
	void RefreshEffedts();
	//色をグラデーションさせる
	void GradationColor();
public:
	ScoreBoardComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//引数に入れた敵が殺されたらスコアが加算される
	void SetEntity(const Entity& enemy);
	//ゲームの状態に応じてアニメーションする
	void CheckState(const GameState& state);
};