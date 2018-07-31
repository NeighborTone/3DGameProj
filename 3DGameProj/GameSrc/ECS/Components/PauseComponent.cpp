#include "PauseComponent.h"

PauseComponent::PauseComponent()
{
	sprite.Load("Resource/Texture/pause.png");
	text.Create("PAUSE", 40);
}

void PauseComponent::Initialize()
{
	ease.Reset();
	trans.pos = 0;
	trans.scale = 0;
}

void PauseComponent::UpDate()
{
	ease.Run(Easing::QuadIn, 20);
	trans.scale = ease.GetVolume(0, 1);

}

void PauseComponent::Draw2D()
{
	text.pos = trans.pos;
	text.scale = trans.scale;
	text.color = Float4(1, 1, 1, 1);
	text.Draw();
	
	sprite.color.a = 0.5f;
	sprite.Draw();
}
