#include "RankingComponent.h"
#include "../../Gamecontroller/Helper.hpp"
#include <fstream>
void RankingComponent::LoadScoreData()
{
	std::ifstream ifs;
	ifs.open("Resource/ScoreData/score.bin", std::ios::in);

	if (!ifs)
	{
		//読み込みに失敗したら新しくファイルを作成する
		WrightScoreData();
		return;
	}

	for (int i = 0; i < MAX; ++i)
	{
		long long scr;
		ifs >> std::hex >> scr;
		//読み込みは右に1シフト
		data[i].scoreData.score = scr >> 1;
	}
	ifs.close();
}

void RankingComponent::WrightScoreData()
{
	std::ofstream ofs;
	ofs.open("Resource/ScoreData/score.bin", std::ios::out);

	if (!ofs)
	{
		return;
	}

	for (int i = 0; i < MAX; ++i)
	{
		//改ざん防止のために左に1シフト
		auto scr = data[i].scoreData.score << 1;
		ofs << std::hex << scr << " ";
	}
	ofs.close();
}

void RankingComponent::Initialize()
{
	isUpDateRanking = false;
	isReset = false;
	isSetColor = false;
	reduction.Reset();
	for (size_t i = 0; i < MAX; ++i)
	{
		data[i].scoreData.score = 0;
		data[i].scoreData.color = Float4(0.9f, 0.9f, 0.9f, 1);
		data[i].scoreData.trans.scale = 1;
		data[i].isHighScore = false;
		data[i].scoreData.colorDelta = Float4(0, 0, 0, 1);
		data[i].scoreData.trans.pos.x = -Engine::GetWindowSize().x / 2.0f - 150;
		data[i].scoreData.ease.Reset();
	}
	//スコアの読み込み
	LoadScoreData();
}

void RankingComponent::UpDate()
{
	//小さい順に表示
	std::sort(data.begin(), data.end(),
		[](const RankData& left, const RankData& right)
	{
		return left.scoreData.score < right.scoreData.score;
	});

	for (size_t i = 0; i < MAX; ++i)
	{
		const float easeStartPos(-Engine::GetWindowSize().x / 2.0f - (i * 150));
		const float easeEndPos(-200);
		data[i].scoreData.trans.pos.y = (float)i * 100;
		data[i].scoreData.ease.Run(Easing::CubicOut,80);
		data[i].scoreData.trans.pos.x = data[i].scoreData.ease.GetVolume(easeStartPos, easeEndPos - easeStartPos);
		if (!isSetColor && data[i].isHighScore)
		{
			isSetColor = true;
			data[i].scoreData.colorDelta = Float4(0.02f, 0.05f, 0.09f, 1);
		}
		ComAssist::GradationColor(data[i].scoreData.color, data[i].scoreData.colorDelta);
	}
	if (data.back().scoreData.ease.IsEaseEnd() && KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		isReset = true;
	}
	//表示したものを縮小する
	if (isReset)
	{
		for (size_t i = 0; i < MAX; ++i)
		{
			reduction.Run(Easing::CubicOut, 80);
			data[i].scoreData.trans.scale = reduction.GetVolume(1, 0 - 1);
		}
	}
}

void RankingComponent::Draw2D()
{
	for (const auto& it : data)
	{
		text.Create(std::to_string(it.scoreData.score), size, font);
		text.pos.x = it.scoreData.trans.pos.x;
		text.pos.y = it.scoreData.trans.pos.y;
		text.scale = it.scoreData.trans.scale;
		text.color = it.scoreData.color;
		text.Draw();
	}
}

void RankingComponent::SetScore(const long long& score)
{
	//スコアが大きい順にソート
	std::sort(data.begin(), data.end(),
		[](const RankData& left, const RankData& right)
	{
		return left.scoreData.score > right.scoreData.score;
	});
	
	for (size_t i = 0; i < MAX; ++i)
	{
		if (!isUpDateRanking && score >= data[i].scoreData.score)
		{
			data.back().scoreData.score = score;
			data.back().isHighScore = true;
			isUpDateRanking = true;
			break;
		}
	}
	
	WrightScoreData();
}

const bool RankingComponent::IsMoveEnd()
{
	if (reduction.IsEaseEnd())
	{
		return true;
	}
	return false;
}