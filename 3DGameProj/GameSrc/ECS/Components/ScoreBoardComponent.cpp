#include "ScoreBoardComponent.h"
#include "ThiefComponent.h"
#include <iostream>

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

void ScoreBoardComponent::RefreshEffedts()
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
	boardData.color.r += colorDelta.r;
	boardData.color.g += colorDelta.g;
	boardData.color.b += colorDelta.b;
	if (boardData.color.r <= 0.2f || boardData.color.r >= 0.9f) colorDelta.r *= -1;
	if (boardData.color.b <= 0.2f || boardData.color.b >= 0.9f) colorDelta.b *= -1;
	if (boardData.color.g <= 0.2f || boardData.color.g >= 0.9f) colorDelta.g *= -1;
}

ScoreBoardComponent::ScoreBoardComponent()
{
	scoreText.Create(std::to_string(0), size, font);
}

void ScoreBoardComponent::Initialize()
{
	boardData.ease.Reset();
	boardData.score = 0;
	boardData.color = Float4(0.5f, 0.5f, 0.5f,1);
	colorDelta = Float4(0.002f, 0.005f, 0.009f,1);
}

void ScoreBoardComponent::UpDate()
{
	GradationColor();
	const Vec2 ScoreBoardPos(
		(float)(Engine::GetWindowSize().x / 2) - (size / 2) - (GetDigit(boardData.score) * size / 3), 
		(float)(Engine::GetWindowSize().y / 2) - (size * 0.8f));
	boardData.trans.pos.x = ScoreBoardPos.x;
	boardData.trans.pos.y = ScoreBoardPos.y;

	const Vec2 ComboPos(Engine::GetWindowSize().x / 2.f - 128, (float)(Engine::GetWindowSize().y / 2));
	comboData.trans.pos.x = ComboPos.x;
	comboData.trans.pos.y = ScoreBoardPos.y - 100;
	comboData.color.a -= 0.008f;
	comboData.color.r = boardData.color.r;
	comboData.color.g = boardData.color.g;
	comboData.color.b = boardData.color.b;
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
		it->color.r = boardData.color.r;
		it->color.g = boardData.color.g;
		it->color.b = boardData.color.b;
	}

	RefreshEffedts();
}

void ScoreBoardComponent::Draw2D()
{
	scoreText.Create(std::to_string(boardData.score), size, font);
	scoreText.pos.x = boardData.trans.pos.x;
	scoreText.pos.y = boardData.trans.pos.y;
	scoreText.color = boardData.color;
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

void ScoreBoardComponent::SetEntity(const Entity& enemy)
{
	if (!enemy.HasComponent<ThiefComponent>())
	{
		return;
	}
	const auto& enemys = enemy.GetComponent<ThiefComponent>().GetData();
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
				boardData.score += 100 * (comboData.score);
				effects.back()->score = 100 * (comboData.score);
			}
			if (it->state == EnemyData::State::GETAWAY)
			{
				boardData.score += 50 * (comboData.score);
				effects.back()->score = 50 * (comboData.score);
			}
		}
	}
}

void ScoreBoardComponent::CheckState(const GameState& state)
{
	if (state == GameState::END)
	{
		//画面の中央付近にイージングで移動
		const float posX = (float)(Engine::GetWindowSize().x / 2) - (size / 2) - (GetDigit(boardData.score) * size / 3);
		const float posY = (float)(Engine::GetWindowSize().y / 2) - (size * 0.8f);
		boardData.ease.Run(Easing::CircIn,50);
		boardData.trans.pos.x = boardData.ease.GetVolume(posX, 0 - posX);
		boardData.trans.pos.y = boardData.ease.GetVolume(posY,100 - posY);
	}
}
