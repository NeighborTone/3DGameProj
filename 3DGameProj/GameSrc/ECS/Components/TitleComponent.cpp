#include "TitleComponent.h"
#include "../../GameController/Helper.hpp"

TitleComponent::TitleComponent()
{
	sprite.Load("Resource/Texture/pause.png");
	logo.Load("Resource/Texture/logo.png");
	text.Create("Press Z key", 40);
}

void TitleComponent::Initialize()
{
	logodata.ease.Reset();
	textdata.ease.Reset();
	logodata.trans.pos = 0;
	logodata.trans.scale = 0;
	textdata.trans.pos = 0;
	textdata.trans.scale = 0;
	backColor = Float4(1, 1, 1, 0.f);
	textdata.color = Float4(0.5f, 0.5f, 0.5f, 1);
	colorDelta = Float4(0.002f, 0.005f, 0.009f, 1);
	isPlay = false;
}

void TitleComponent::UpDate()
{
	logodata.ease.Run(Easing::QuadIn, 40);
	logodata.trans.pos.y = logodata.ease.GetVolume(490,100 - 490);
	logodata.trans.scale = logodata.ease.GetVolume(0, 1);
	ComAssist::GradationColor(textdata.color,colorDelta);
	if (logodata.ease.IsEaseEnd())
	{
		textdata.ease.Run(Easing::QuadIn, 40);
		textdata.trans.scale = textdata.ease.GetVolume(0, 1);
	}
	if (!(backColor.a >= 0.5f))
	{
		backColor.a += 0.01f;
	}
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		isPlay = true;
	}
}

void TitleComponent::Draw2D()
{
	sprite.color = backColor;

	sprite.Draw();
	logo.pos = logodata.trans.pos;
	logo.scale = logodata.trans.scale;
	logo.Draw();
	if (logodata.ease.IsEaseEnd())
	{
		text.pos = textdata.trans.pos;
		text.scale = textdata.trans.scale;
		text.color = textdata.color;
		text.Draw();
	}
}

const GameState TitleComponent::GetState()
{
	if (isPlay)
	{
		return GameState::PLAY;
	}
	return GameState::TITLE;
}
