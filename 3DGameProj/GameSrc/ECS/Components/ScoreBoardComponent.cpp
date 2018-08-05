#include "ScoreBoardComponent.h"
#include "UFOComponent.h"
#include <iostream>
#include "../../GameController/Helper.hpp"
std::unique_ptr<ScoreData> ScoreBoardComponent::AddData()
{
	return std::make_unique<ScoreData>();
}

const unsigned ScoreBoardComponent::GetDigit(unsigned num) const
{
	unsigned digit = 0;
	while (num != 0) 
	{
		num /= 10;
		digit++;
	}
	return digit;
}

void ScoreBoardComponent::RefreshEffects()
{
	effects.erase(std::remove_if(std::begin(effects), std::end(effects),
		[](const std::unique_ptr<ScoreData> &data)
	{
		return data->ease.IsEaseEnd();
	}),
		std::end(effects));

}

void ScoreBoardComponent::GradationColor()
{
	ComAssist::GradationColor(scoreData.color,colorDelta);

}

ScoreBoardComponent::ScoreBoardComponent()
{
	scoreText.Create(std::to_string(0), size, font);
}

void ScoreBoardComponent::Initialize()
{
	scoreData.ease.Reset();
	scoreData.score = 0;
	scoreData.color = Float4(0.5f, 0.5f, 0.5f,1);
	colorDelta = Float4(0.002f, 0.005f, 0.009f,1);
}

void ScoreBoardComponent::UpDate()
{
	GradationColor();
	const Vec2 ScoreBoardPos(
		(float)(Engine::GetWindowSize().x / 2) - (size / 2) - (GetDigit(scoreData.score) * size / 3), 
		(float)(Engine::GetWindowSize().y / 2) - (size * 0.8f));
	scoreData.trans.pos.x = ScoreBoardPos.x;
	scoreData.trans.pos.y = ScoreBoardPos.y;

	const Vec2 ComboPos(Engine::GetWindowSize().x / 2.f - 128, (float)(Engine::GetWindowSize().y / 2));
	comboData.trans.pos.x = ComboPos.x;
	comboData.trans.pos.y = ScoreBoardPos.y - 100;
	comboData.color.r = scoreData.color.r;
	comboData.color.g = scoreData.color.g;
	comboData.color.b = scoreData.color.b;
	if (comboData.color.a <= 0)
	{
		comboData.score = 0;
	}

	for (auto& it : effects)
	{
		const Vec2 ScoreEffectPos(Engine::GetWindowSize().x / 2.f - 128,(float)(Engine::GetWindowSize().y / 2));
		it->ease.Run(Easing::ExpoIn,80);
		it->trans.pos.x = ScoreEffectPos.x;
		it->trans.pos.y = it->ease.GetVolume(0, ScoreEffectPos.y);
		it->color.a -= 0.008f;
		it->color.r = scoreData.color.r;
		it->color.g = scoreData.color.g;
		it->color.b = scoreData.color.b;
	}

	RefreshEffects();
}

void ScoreBoardComponent::Draw2D()
{
	scoreText.Create(std::to_string(scoreData.score), size, font);
	scoreText.pos.x = scoreData.trans.pos.x;
	scoreText.pos.y = scoreData.trans.pos.y;
	scoreText.color = scoreData.color;
	scoreText.Draw();

	scoreText.Create(std::to_string(comboData.score) + "Combo!!", size, font);
	scoreText.pos.x = comboData.trans.pos.x;
	scoreText.pos.y = comboData.trans.pos.y;
	scoreText.color = comboData.color;
	scoreText.Draw();
	
	for (auto& it : effects)
	{
		scoreText.Create("+" + std::to_string(it->score), size, font);
		scoreText.pos = it->trans.pos;
		scoreText.color = it->color;
		scoreText.Draw();
	}
}

const int ScoreBoardComponent::GetScore() const
{
	return scoreData.score;
}

void ScoreBoardComponent::SetEntity(const Entity& enemy)
{
	if (!enemy.HasComponent<UFOComponent>())
	{
		return;
	}
	const auto& enemys = enemy.GetComponent<UFOComponent>().GetData();
	if (enemys.empty() || enemys.data() == nullptr)
	{
		return;
	}
	for (const auto& it : enemys)
	{
		if (it->lifeSpan == 0)
		{
			//スコアエフェクトを新規追加
			effects.emplace_back(AddData());
			effects.back()->color = Float4(1, 1, 1, 1);
			//コンボテキストを新規追加
			comboData.color = Float4(1, 1, 1, 1);
			++comboData.score;

			if (it->state == EnemyData::State::TRACKING)
			{
				scoreData.score += 100 * (comboData.score);
				effects.back()->score = 100 * (comboData.score);
			}
			if (it->state == EnemyData::State::GETAWAY)
			{
				scoreData.score += 50 * (comboData.score);
				effects.back()->score = 50 * (comboData.score);
			}
		}
	}
}

void ScoreBoardComponent::CheckState(const GameState& state)
{
	//ポーズ中は止めておく
	if (state != GameState::PAUSE)
	{
		comboData.color.a -= 0.008f;
	}
	if (state == GameState::END)
	{
		//画面の中央付近にイージングで移動
		const float posX = (float)(Engine::GetWindowSize().x / 2) - (size / 2) - (GetDigit(scoreData.score) * size / 3);
		const float posY = (float)(Engine::GetWindowSize().y / 2) - (size * 0.8f);
		scoreData.ease.Run(Easing::CubicOut,60);
		scoreData.trans.pos.x = scoreData.ease.GetVolume(posX, 0 - posX);
		scoreData.trans.pos.y = scoreData.ease.GetVolume(posY,100 - posY);
	}
}
