#include "ScoreBoardComponent.h"
#include "ThiefComponent.h"
#include <iostream>

std::unique_ptr<ScoreData> ScoreBoardComponent::AddData()
{
	return std::make_unique<ScoreData>();
}

void ScoreBoardComponent::CreateEffect()
{
	

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

ScoreBoardComponent::ScoreBoardComponent()
{
	score.Create(std::to_string(0), size, font);
}

void ScoreBoardComponent::Initialize()
{
	data.ease.Reset();
	data.score = 0;
	data.color = Float4(0.5f, 0.5f, 0.5f,1);
	colorDelta = Float4(0.002f, 0.005f, 0.009f,1);
}

void ScoreBoardComponent::UpDate()
{
	data.color.r += colorDelta.r;
	data.color.g += colorDelta.g;
	data.color.b += colorDelta.b;
	if (data.color.r <= 0.2f || data.color.r >= 0.9f) colorDelta.r *= -1;
	if (data.color.b <= 0.2f || data.color.b >= 0.9f) colorDelta.b *= -1;
	if (data.color.g <= 0.2f || data.color.g >= 0.9f) colorDelta.g *= -1;
	const float posX = (float)(Engine::GetWindowSize().x / 2) - (size / 2) - (GetDigit(data.score) * size / 3);
	const float posY = (float)(Engine::GetWindowSize().y / 2) - (size * 0.8f);
	data.trans.pos.x = posX;
	data.trans.pos.y = posY;


	for (auto& it : effects)
	{
		const float SposY = (float)(Engine::GetWindowSize().y / 2);

		it->ease.Run(Easing::SineIn,40);
		it->trans.pos.x = posX;
		it->trans.pos.y = it->ease.GetVolume(0, SposY);
		it->color.a -= 0.03f;
		it->color.r = data.color.r;
		it->color.g = data.color.g;
		it->color.b = data.color.b;
	}

	effects.erase(std::remove_if(std::begin(effects), std::end(effects),
		[](const std::unique_ptr<ScoreData> &data)
	{
		return data->ease.IsEaseEnd();
	}),
		std::end(effects));
}

void ScoreBoardComponent::Draw2D()
{
	score.Create(std::to_string(data.score), size, font);
	score.pos.x = data.trans.pos.x;
	score.pos.y = data.trans.pos.y;
	score.color = data.color;
	score.Draw();
	for (auto& it : effects)
	{
		scoreEffect.Create("+" + std::to_string(it->score), size, font);
		scoreEffect.pos = it->trans.pos;
		scoreEffect.color = it->color;
		scoreEffect.Draw();
	}
}

void ScoreBoardComponent::SetEntity(const Entity& enemy)
{
	const auto& enemys = enemy.GetComponent<ThiefComponent>().GetData();
	if (enemys.empty())
	{
		return;
	}
	for (const auto& it : enemys)
	{
		if (it->lifeSpan == 0)
		{
			effects.emplace_back(AddData());
			effects.at(effects.size() - 1)->color = Float4(1, 1, 1, 1);
			if (it->state == EnemyData::State::TRACKING)
			{
				data.score += 100;
				effects.at(effects.size() - 1)->score = 100;
			}
			if (it->state == EnemyData::State::GETAWAY)
			{
				data.score += 50;
				effects.at(effects.size() - 1)->score = 50;
			}
		}
	}
}

void ScoreBoardComponent::CheckState(const GameState& state)
{

	if (state == GameState::END)
	{
		const float posX = (float)(Engine::GetWindowSize().x / 2) - (size / 2) - (GetDigit(data.score) * size / 3);
		const float posY = (float)(Engine::GetWindowSize().y / 2) - (size * 0.8f);
		data.ease.Run(Easing::CircIn,50);
		data.trans.pos.x = data.ease.GetVolume(posX, 0 - posX);
		data.trans.pos.y = data.ease.GetVolume(posY,100 - posY);
	}
}
