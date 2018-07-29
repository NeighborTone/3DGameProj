#include "CursorComponent.h"

CursorComponent::CursorComponent()
{
	sprite.Load("Resource/Texture/cursor2.png");
}

void CursorComponent::Initialize()
{
	trans.angles = 0;
}

void CursorComponent::UpDate()
{
	--trans.angles.z;
}

void CursorComponent::Draw2D()
{
	sprite.angle = trans.angles;
	sprite.pos = trans.pos;
	sprite.Draw();
}
