#include "EndComponent.h"

EndComponent::EndComponent()
{
	sprite.Load("Resource/Texture/pause.png");
}

void EndComponent::Initialize()
{
	rank = &entity->GetComponent<RankingComponent>();
	isTitle = false;
	data.ease.Reset();
	data.trans.pos = 0;
	data.color = Float4(1, 1, 1, 0.7f);
	data.trans.scale = 0;
}

void EndComponent::UpDate()
{
	if (rank->IsMoveEnd())
	{
		isTitle = true;
	}
	if (isTitle)
	{
		data.color.a -= 0.1f;
	}
}

void EndComponent::Draw2D()
{
	sprite.color = data.color;
	sprite.Draw();
}

const GameState EndComponent::GetState()
{
	if (data.color.a <= 0)
	{
		return GameState::RESET;
	}
	return GameState::END;
}
