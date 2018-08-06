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
	//保存してあるスコアランキングの読み込み
	void LoadScoreData();
	//スコアランキングの書き込み
	void WrightScoreData();
	std::array<RankData,MAX> data;
	Text text;
	Easing reduction;
public:
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	//スコアのセット
	void SetScore(const long long& score);
	//ランキングのアニメーションが終了したか返す
	const bool IsMoveEnd();
};