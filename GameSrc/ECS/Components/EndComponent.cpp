#include "EndComponent.h"
#include "../../GameController/Helper.hpp"
EndComponent::EndComponent()
{
	sprite.Load("Resource/Texture/pause.png");
	text.Create("Press Z key Return to Title",size,font);
}

void EndComponent::Initialize()
{
	cnt.Reset();
	rank = &entity->GetComponent<RankingComponent>();
	isReset = false;
	backColor = Float4(1, 1, 1, 0.7f);
	textData.ease.Reset();
	textData.trans.scale = 1;
	textData.trans.pos.Zero();
	textData.trans.pos.y = 99999;
	textData.trans.angles.Zero();
	textData.color = Float4(0.9f, 0.9f, 0.9f, 1);
	textData.colorDelta = Float4(0.02f, 0.05f, 0.09f, 1);
	reduction.Reset();
}

void EndComponent::UpDate()
{
	ComAssist::GradationColor(textData.color, textData.colorDelta);
	textData.ease.Run(Easing::CubicOut, 80);
	const float End_PosY = (float)(-Engine::GetWindowSize().y / 2) - (size * 0.8f);
	textData.trans.pos.y = textData.ease.GetVolume(End_PosY, -200 - End_PosY);

	if (rank->IsMoveEnd())
	{
		isReset = true;
		reduction.Run(Easing::SineIn, 20);
		textData.trans.scale = reduction.GetVolume(1, 0 -1);
	}
	if (isReset && reduction.IsEaseEnd())
	{
		backColor.a -= 0.1f;
	}
	if (backColor.a <= 0)
	{
		cnt.Add();
	}
}

void EndComponent::Draw2D()
{
	sprite.color = backColor;
	sprite.Draw();
	text.color = textData.color;
	text.scale = textData.trans.scale;
	text.pos = textData.trans.pos;
	text.Draw();
}

const GameState EndComponent::GetState() const
{
	if (cnt.GetCurrentCount() >= 30)
	{
		return GameState::RESET;
	}
	return GameState::END;
}
