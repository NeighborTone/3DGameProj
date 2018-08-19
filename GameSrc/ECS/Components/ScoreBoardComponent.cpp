#include "ScoreBoardComponent.h"
#include "UFOComponent.h"
#include <iostream>
#include "../../GameController/Helper.hpp"
std::unique_ptr<ScoreData> ScoreBoardComponent::AddData()
{
	return std::make_unique<ScoreData>();
}

const unsigned ScoreBoardComponent::GetDigit(long long num) const
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
	ComAssist::GradationColor(scoreData.color, scoreData.colorDelta);
	ComAssist::GradationColor(comboData.color, comboData.colorDelta);
}

void ScoreBoardComponent::EffectUpDate()
{
	for (auto& it : effects)
	{
		const Vec2 ScoreEffectPos(
			0,
			-(Engine::GetWindowSize().y / 2.f));
		it->ease.Run(Easing::QuintIn, 80);
		it->trans.pos.x = ScoreEffectPos.x;
		it->trans.pos.y = it->ease.GetVolume(-50, ScoreEffectPos.y - (-50));
		it->color.a -= 0.008f;
		it->color.r = comboData.color.r;
		it->color.g = comboData.color.g;
		it->color.b = comboData.color.b;
	}
}

void ScoreBoardComponent::ComboUpDate()
{
	comboData.trans.pos.x = 0;
	comboData.trans.pos.y = -100;
	comboData.color.r = comboData.color.r;
	comboData.color.g = comboData.color.g;
	comboData.color.b = comboData.color.b;
	if (comboData.color.a <= 0)
	{
		comboData.score = 0;
	}
	
}

void ScoreBoardComponent::BoardUpDate()
{
	const Vec2 ScoreBoardPos(
		(Engine::GetWindowSize().x / 2.f) - (size / 2) - (GetDigit(scoreData.score) * size / 3),
		(Engine::GetWindowSize().y / 2.f) - (size * 0.8f));
	scoreData.trans.pos.x = ScoreBoardPos.x;
	scoreData.trans.pos.y = ScoreBoardPos.y;
	
}

ScoreBoardComponent::ScoreBoardComponent()
{
	scoreText = std::make_unique<Text>();
	bonusText = std::make_unique<Text>();
	scoreText->Create(std::to_string(0), size, font);
}

void ScoreBoardComponent::Initialize()
{
	isAddTomatoesScore = false;
	tomatoNum = 0u;
	{
		scoreData.ease.Reset();
		scoreData.score = 0;
		scoreData.color = Float4(0.5f, 0.5f, 0.5f, 1);
		scoreData.colorDelta = Float4(0.002f, 0.005f, 0.009f, 1);
	}

	{
		comboData.score = 0;
		comboData.color = Float4(0.5f, 0.5f, 0.5f, 0);
		comboData.colorDelta = Float4(0.002f, 0.005f, 0.009f, 1);
	}

	{
		tomatoScoreData.ease.Reset();
		tomatoScoreData.score = 0;
	}
}

void ScoreBoardComponent::UpDate()
{
	GradationColor();
	BoardUpDate();
	ComboUpDate();
	EffectUpDate();
	RefreshEffects();
}

void ScoreBoardComponent::Draw2D()
{
	{
		scoreText->Create(std::to_string(scoreData.score), size, font);
		scoreText->pos = scoreData.trans.pos;
		scoreText->scale = scoreData.trans.scale;
		scoreText->angle = scoreData.trans.angles;
		scoreText->color = scoreData.color;
		scoreText->Draw();
	}


	{
		scoreText->Create(std::to_string(comboData.score) + "Combo!!", size -10, font);
		scoreText->pos = comboData.trans.pos;
		scoreText->scale = comboData.trans.scale;
		scoreText->angle = comboData.trans.angles;
		scoreText->color = comboData.color;
		scoreText->Draw();
	}

	for (auto& it : effects)
	{
		scoreText->Create("+" + std::to_string(it->score), size, font);
		scoreText->pos = it->trans.pos;
		scoreText->scale = it->trans.scale;
		scoreText->angle = it->trans.angles;
		scoreText->color = it->color;
		scoreText->Draw();
	}

	if(isAddTomatoesScore)
	{
		bonusText->pos = tomatoScoreData.trans.pos;
		bonusText->scale = tomatoScoreData.trans.scale;
		bonusText->angle = tomatoScoreData.trans.angles;
		bonusText->color = scoreData.color;
		bonusText->Draw();
	}

}

const long long ScoreBoardComponent::GetScore() const
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
			comboData.color.a = 1;
			comboData.trans.scale = 1.5f;
			++comboData.score;

			if (it->state == EnemyData::State::TRACKING)
			{
				scoreData.score += 50 * (comboData.score);
				effects.back()->score = 50 * (comboData.score);
			}
			if (it->state == EnemyData::State::GETAWAY)
			{
				scoreData.score += 25 * (comboData.score);
				effects.back()->score = 25 * (comboData.score);
			}
		}
	}
}

void ScoreBoardComponent::CheckTomatoes(const std::vector<TomatoData>& tomats)
{
	if (!isAddTomatoesScore)
	{
		isAddTomatoesScore = true;
		tomatoScoreData.score = scoreData.score;
		tomatoNum = tomats.size();
		scoreData.score += tomatoNum * 1000u;
		bonusText->Create("The Remaining Tomatoes : " + std::to_string(tomatoNum) + "\n" +
			"AddBonus : " + std::to_string(tomatoNum * 1000) + " Points!!", size, font);
	}
	
}

void ScoreBoardComponent::SetState(const GameState& state)
{
	//ポーズ中は止めておく
	if (state != GameState::PAUSE)
	{
		comboData.color.a -= 0.008f;
		comboData.trans.scale -= 0.008f;
	}
	if (state == GameState::END)
	{
		//画面の中央付近にイージングで移動
		const float posX = (float)(Engine::GetWindowSize().x / 2) - (size / 2) - (GetDigit(scoreData.score) * size / 3);
		const float posY = (float)(Engine::GetWindowSize().y / 2) - (size * 0.8f);
		scoreData.ease.Run(Easing::CubicOut, 60);
		scoreData.trans.pos.x = scoreData.ease.GetVolume(posX, 0 - posX);
		scoreData.trans.pos.y = scoreData.ease.GetVolume(posY, 100 - posY);

		//トマトのボーナス表示
		const float TomatoposY = (float)(-Engine::GetWindowSize().y / 2) - (size * 0.8f);
		tomatoScoreData.ease.Run(Easing::CubicOut, 60);
		tomatoScoreData.trans.pos.x = 0;
		tomatoScoreData.trans.pos.y = tomatoScoreData.ease.GetVolume(TomatoposY, -100 - TomatoposY);
	}
}
