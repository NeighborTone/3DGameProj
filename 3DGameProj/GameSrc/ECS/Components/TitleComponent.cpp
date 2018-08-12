#include "TitleComponent.h"
#include "../../GameController/Helper.hpp"

TitleComponent::TitleComponent()
{
	number[0].Load("Resource/Texture/3.png");
	number[1].Load("Resource/Texture/2.png");
	number[2].Load("Resource/Texture/1.png");
	sprite.Load("Resource/Texture/pause.png");
	logo.Load("Resource/Texture/logo.png");
	text.Create("Press Z key", 40, font);
}

void TitleComponent::Initialize()
{
	for (auto& it : numEasings)
	{
		it.ease.Reset();
		it.trans.scale = 0;
		it.trans.pos.y = 100;
		it.color = Float4(1,1,1,1);
	}
	logodata.ease.Reset();
	textdata.ease.Reset();
	reduction.Reset();
	logodata.trans.pos = 0;
	logodata.trans.scale = 0;
	textdata.trans.pos = 0;
	textdata.trans.pos.y = -100;
	textdata.trans.scale = 0;
	backColor = Float4(1, 1, 1, 0.f);
	textdata.color = Float4(0.5f, 0.5f, 0.5f, 1);
	textdata.colorDelta = Float4(0.002f, 0.005f, 0.009f, 1);
	isPlay = false;
}

void TitleComponent::UpDate()
{
	logodata.ease.Run(Easing::QuadIn, 40);
	logodata.trans.pos.y = logodata.ease.GetVolume(490,100 - 490);
	logodata.trans.scale = logodata.ease.GetVolume(0, 1);
	ComAssist::GradationColor(textdata.color, textdata.colorDelta);
	if (logodata.ease.IsEaseEnd())
	{
		textdata.ease.Run(Easing::QuadIn, 40);
		textdata.trans.scale = textdata.ease.GetVolume(0, 1);
	}
	if (!(backColor.a >= 0.5f) && !isPlay)
	{
		backColor.a += 0.01f;
	}
	if (textdata.ease.IsEaseEnd() && KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		isPlay = true;
	}
	if (isPlay)
	{
		reduction.Run(Easing::CubicOut, 60);
		logodata.trans.scale = reduction.GetVolume(1 , 0 - 1);
		textdata.trans.scale = reduction.GetVolume(1, 0 - 1);
		backColor.a -= 0.01f;
	}
	if (reduction.IsEaseEnd())
	{
		numEasings[0].ease.Run(Easing::QuadIn, 80);
		numEasings[0].trans.scale = numEasings[0].ease.GetVolume(0,2);
	}
	if (numEasings[0].ease.IsEaseEnd())
	{
		numEasings[1].ease.Run(Easing::QuadIn, 80);
		numEasings[1].trans.scale = numEasings[1].ease.GetVolume(0, 2);
	}
	if (numEasings[1].ease.IsEaseEnd())
	{
		numEasings[2].ease.Run(Easing::QuadIn, 80);
		numEasings[2].trans.scale = numEasings[2].ease.GetVolume(0, 2);
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
	for (int i = 0; i < 3; ++i)
	{
		number[i].color = numEasings[i].color;
		number[i].scale = numEasings[i].trans.scale;
		number[i].pos = numEasings[i].trans.pos;
		if (!numEasings[i].ease.IsEaseEnd())
		{
			number[i].Draw();
		}
	}
}

const bool TitleComponent::IsPlay() const
{
	return isPlay;
}

const GameState TitleComponent::GetState()
{
	if (isPlay && backColor.a <= 0 && numEasings[2].ease.IsEaseEnd())
	{
		return GameState::PLAY;
	}
	return GameState::TITLE;
}
