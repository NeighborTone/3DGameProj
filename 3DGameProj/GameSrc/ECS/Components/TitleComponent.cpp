#include "TitleComponent.h"

TitleComponent::TitleComponent()
{
	sprite.Load("Resource/Texture/pause.png");
	logo.Load("Resource/Texture/logo.png");
	text.Create("Press'Z'key", 40);
}

void TitleComponent::Initialize()
{
	logodata.ease.Reset();
	textdata.ease.Reset();
	logodata.trans.pos = 0;
	logodata.trans.scale = 0;
	textdata.trans.pos = 0;
	textdata.trans.scale = 0;
	isPlay = false;
}

void TitleComponent::UpDate()
{
	logodata.ease.Run(Easing::QuadIn, 40);
	logodata.trans.pos.y = logodata.ease.GetVolume(490,100 - 490);
	logodata.trans.scale = logodata.ease.GetVolume(0, 1);
	if (logodata.ease.IsEaseEnd())
	{
		textdata.ease.Run(Easing::QuadIn, 80);
		textdata.trans.scale = logodata.ease.GetVolume(0, 1);
	}
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		isPlay = true;
	}
}

void TitleComponent::Draw2D()
{
	sprite.color.a = 0.5f;
	sprite.Draw();
	logo.pos = logodata.trans.pos;
	logo.scale = logodata.trans.scale;
	logo.Draw();
	if (logodata.ease.IsEaseEnd())
	{
		text.pos = textdata.trans.pos;
		text.scale = textdata.trans.scale;
		text.color = Float4(1, 1, 1, 1);
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
