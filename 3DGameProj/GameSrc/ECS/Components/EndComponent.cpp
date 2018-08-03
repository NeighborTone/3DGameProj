#include "EndComponent.h"

EndComponent::EndComponent()
{
	sprite.Load("Resource/Texture/pause.png");
}

void EndComponent::Initialize()
{
	data.ease.Reset();
	data.trans.pos = 0;
	data.trans.scale = 0;
}

void EndComponent::UpDate()
{

}

void EndComponent::Draw3D()
{

}

void EndComponent::Draw2D()
{
	sprite.color.a = 0.5f;
	sprite.Draw();
}
