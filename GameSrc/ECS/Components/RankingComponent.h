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
	//ハイスコアが更新されたか
	bool isUpDateRanking;
	//ランキング表示を終了させるか
	bool isReset;
	//ハイスコアがあった場合色を変えるためのフラグ
	bool isSetColor;
	//保存してあるスコアランキングの読み込み
	void LoadScoreData();
	//スコアランキングの書き込み
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
	//スコアのセット
	void SetScore(const long long& score);
	//ランキングのアニメーションが終了したか返す
	const bool IsMoveEnd();
};