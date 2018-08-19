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
	//スコア格納用
	ScoreData scoreData;
	//コンボ表示用
	ScoreData comboData;		
	//トマト分のスコア加算演出用
	ScoreData tomatoScoreData;	
	//加算した値表示用
	std::vector<std::unique_ptr<ScoreData>> effects;
	//コンボ表示用のデータを追加する
	std::unique_ptr<ScoreData> AddData();
	//引数に入れた値の桁数を返す関数
	const unsigned GetDigit(long long num) const;
	//不要になったスコアエフェクトを破棄する
	void RefreshEffects();
	//色をグラデーションさせる
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
	//手に入れた総スコアを取得
	const long long GetScore() const;
	//引数に入れた敵が殺されたらスコアが加算される
	void SetEntity(const Entity& enemy);
	//トマトの個数に応じて得点を加算
	void CheckTomatoes(const std::vector<TomatoData>& tomats);
	//ゲームの状態に応じた処理をする
	void SetState(const GameState& state);
};