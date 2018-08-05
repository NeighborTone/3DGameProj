#include "RankingComponent.h"
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
		int scr;
		ifs >> std::hex >> scr;
		//読み込みは右に1シフト
		data[i].score = scr >> 1;
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
		int scr = data[i].score << 1;
		ofs << std::hex << scr << " ";
	}
	ofs.close();
}

void RankingComponent::Initialize()
{
	isUpDateRanking = false;
	isReset = false;
	reduction.Reset();
	for (size_t i = 0; i < MAX; ++i)
	{
		data[i].score = 0;
		data[i].color = Float4(1, 1, 1, 1);
		data[i].trans.scale = 1;
		data[i].trans.pos.x = -Engine::GetWindowSize().x / 2.0f - 150;
		data[i].ease.Reset();
	}
	//スコアの読み込み
	LoadScoreData();
}

void RankingComponent::UpDate()
{
	//小さい順に表示
	std::sort(data.begin(), data.end(),
		[](const ScoreData& left, const ScoreData& right)
	{
		return left.score < right.score;
	});

	for (size_t i = 0; i < MAX; ++i)
	{
		const float easeStartPos(-Engine::GetWindowSize().x / 2.0f - (i * 150));
		const float easeEndPos(-200);
		data[i].trans.pos.y = (float)i * 100;
		data[i].ease.Run(Easing::CubicOut,80);
		data[i].trans.pos.x = data[i].ease.GetVolume(easeStartPos, easeEndPos - easeStartPos);
	}
	if (data.back().ease.IsEaseEnd() && KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		isReset = true;
	}
	//表示したものを縮小する
	if (isReset)
	{
		for (size_t i = 0; i < MAX; ++i)
		{
			reduction.Run(Easing::CubicOut, 60);
			data[i].trans.scale = reduction.GetVolume(1, 0 - 1);
		}
	}
}

void RankingComponent::Draw2D()
{
	for (const auto& it : data)
	{
		text.Create(std::to_string(it.score), size, font);
		text.pos.x = it.trans.pos.x;
		text.pos.y = it.trans.pos.y;
		text.scale = it.trans.scale;
		text.color = it.color;
		text.Draw();
	}
}

void RankingComponent::SetScore(const int& score)
{
	//スコアが大きい順にソート
	std::sort(data.begin(), data.end(),
		[](const ScoreData& left, const ScoreData& right)
	{
		return left.score > right.score;
	});
	
	for (size_t i = 0; i < MAX; ++i)
	{
		if (!isUpDateRanking && score >= data[i].score)
		{
			data.back().score = score;
			data.back().color = Float4(1, 0, 0, 1);
			isUpDateRanking = true;
			break;
		}
	}
	
	WrightScoreData();
}

bool RankingComponent::IsMoveEnd()
{
	if (reduction.IsEaseEnd())
	{
		return true;
	}
	return false;
}