#include "TitleComponent.h"

TitleComponent::TitleComponent()
{
	sprite.Load("Resource/Texture/pause.png");
	text.Create("TITLE", 40);
}

void TitleComponent::Initialize()
{
	ease.Reset();
	trans.pos = 0;
	trans.scale = 0;
}

void TitleComponent::UpDate()
{
	ease.Run(Easing::QuadIn, 40);
	trans.pos.y = ease.GetVolume(490,100 - 490);
	trans.scale = ease.GetVolume(0, 1);
}

void TitleComponent::Draw2D()
{
	sprite.color.a = 0.5f;
	sprite.Draw();
	text.pos = trans.pos;
	text.scale = trans.scale;
	text.color = Float4(0, 1, 1, 1);
	text.Draw();
}
