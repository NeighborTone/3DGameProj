#include "TitleComponent.h"
#include "../../GameController/Helper.hpp"

TitleComponent::TitleComponent()
{
	number[0].Create("3", size,font);
	number[1].Create("2", size, font);
	number[2].Create("1", size, font);
	destoryLogo.Create("DESTROY THE UFO!!!", size,font);
	sprite.Load("Resource/Texture/pause.png");
	logo.Load("Resource/Texture/logo.png");
	text.Create("Press Z key", size, font);
}

void TitleComponent::Initialize()
{
	for (auto& it : numData)
	{
		it.ease.Reset();
		it.trans.scale.Zero();
		it.trans.pos.y = 100;
		it.color = Float4(1,1,1,1);
	}
	destroyData.trans.scale.Zero();
	destroyData.trans.pos.y = 100;
	destroyData.color = Float4(1,1,1,1);
	destroyData.ease.Reset();
	logoData.ease.Reset();
	textData.ease.Reset();
	reduction.Reset();
	logoData.trans.pos.Zero();
	logoData.trans.scale.Zero();
	textData.trans.pos.Zero();
	textData.trans.pos.y = -100;
	textData.trans.scale.Zero();
	backColor = Float4(1, 1, 1, 0.f);
	textData.color = Float4(0.5f, 0.5f, 0.5f, 1);
	textData.colorDelta = Float4(0.002f, 0.005f, 0.009f, 1);
	isPlay = false;
}

void TitleComponent::UpDate()
{
	logoData.ease.Run(Easing::QuadIn, 40);
	logoData.trans.pos.y = logoData.ease.GetVolume(490,100 - 490);
	logoData.trans.scale = logoData.ease.GetVolume(0, 1);
	ComAssist::GradationColor(textData.color, textData.colorDelta);
	if (logoData.ease.IsEaseEnd())
	{
		textData.ease.Run(Easing::QuadIn, 40);
		textData.trans.scale = textData.ease.GetVolume(0, 1);
	}
	if (!(backColor.a >= 0.5f) && !isPlay)
	{
		backColor.a += 0.01f;
	}
	if (textData.ease.IsEaseEnd() && KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		isPlay = true;
	}
	//ÉçÉSìôÇà¯Ç¡çûÇﬂÇÈ
	if (isPlay)
	{
		reduction.Run(Easing::CubicOut, 60);
		logoData.trans.scale = reduction.GetVolume(1 , 0 - 1);
		textData.trans.scale = reduction.GetVolume(1, 0 - 1);
		backColor.a -= 0.01f;
	}
	//3
	if (reduction.IsEaseEnd())
	{
		numData[0].ease.Run(Easing::QuadIn, 80);
		numData[0].trans.scale = numData[0].ease.GetVolume(0,2);
	}
	//2
	if (numData[0].ease.IsEaseEnd())
	{
		numData[1].ease.Run(Easing::QuadIn, 80);
		numData[1].trans.scale = numData[1].ease.GetVolume(0, 2);
	}
	//1
	if (numData[1].ease.IsEaseEnd())
	{
		numData[2].ease.Run(Easing::QuadIn, 80);
		numData[2].trans.scale = numData[2].ease.GetVolume(0, 2);
	}
	//Destroy
	if (numData[2].ease.IsEaseEnd())
	{
		destroyData.ease.Run(Easing::QuadIn, 80);
		destroyData.trans.scale = destroyData.ease.GetVolume(0, 2);
	}
}

void TitleComponent::Draw2D()
{
	sprite.color = backColor;

	sprite.Draw();
	logo.pos = logoData.trans.pos;
	logo.scale = logoData.trans.scale;
	logo.Draw();
	if (logoData.ease.IsEaseEnd())
	{
		text.pos = textData.trans.pos;
		text.scale = textData.trans.scale;
		text.color = textData.color;
		text.Draw();
	}
	
	for (int i = 0; i < 3; ++i)
	{
		number[i].color = textData.color;
		number[i].scale = numData[i].trans.scale;
		number[i].pos = numData[i].trans.pos;
		if (!numData[i].ease.IsEaseEnd())
		{
			number[i].Draw();
		}
	}

	destoryLogo.pos = destroyData.trans.pos;
	destoryLogo.scale = destroyData.trans.scale;
	destoryLogo.color = textData.color;
	if (!destroyData.ease.IsEaseEnd())
	{
		destoryLogo.Draw();
	}
}

const bool TitleComponent::IsPlay() const
{
	return isPlay;
}

const GameState TitleComponent::GetState()
{
	if (isPlay && backColor.a <= 0 && destroyData.ease.IsEaseEnd())
	{
		return GameState::PLAY;
	}
	return GameState::TITLE;
}
