#include "ScoreBoardComponent.h"
#include "ThiefComponent.h"
#include <iostream>
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
	data.number.Create(std::to_string(0), size, font);
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
}

void ScoreBoardComponent::Draw2D()
{
	data.number.Create(std::to_string(data.score), size, font);
	data.number.pos.x = data.trans.pos.x;
	data.number.pos.y = data.trans.pos.y;
	data.number.color = data.color;
	data.number.Draw();
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
		if (it->lifeSpan == 0 && it->state == EnemyData::State::TRACKING)
		{
			data.score += 100;
		}
		if (it->lifeSpan == 0 && it->state == EnemyData::State::GETAWAY)
		{
			data.score += 50;
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
