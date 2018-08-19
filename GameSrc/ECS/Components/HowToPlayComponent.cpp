#include "HowToPlayComponent.h"
#include "../../GameController/Helper.hpp"

HowToPlayComponent::HowToPlayComponent()
{
	howToText.Create("How to play by pressing the X key",size, font);
	moveText.Create("::HowToPlay::\n\n\nMovementKey\nW,A,S,D",size, font);
	shotText.Create("Shot\nMouse Left Click", size, font);
}

void HowToPlayComponent::Initialize()
{
	const float Y = (Engine::GetWindowSize().y / 2.f) - (size * 6);
	drawIn.Reset();
	isShow = false;
	isHide = false;
	moveData.trans.pos.x = -99999;
	moveData.trans.pos.y = Y;
	moveData.trans.angles.Zero();
	moveData.trans.scale = 1;
	moveData.ease.Reset();
	moveData.color = Float4(0.5f, 0.5f, 0.5f, 1);
	moveData.colorDelta = Float4(0.002f, 0.005f, 0.009f, 1);

	shotData.trans.pos.x = -99999;
	shotData.trans.pos.y = Y - 300;
	shotData.trans.angles.Zero();
	shotData.trans.scale = 1;
	shotData.ease.Reset();
	shotData.color = Float4(0.5f, 0.5f, 0.5f, 1);
	shotData.colorDelta = Float4(0.002f, 0.005f, 0.009f, 1);

	const Vec2 BottomLeft(
		(-Engine::GetWindowSize().x / 2.f) + (size * 9),
		(-Engine::GetWindowSize().y / 2.f) + (size * 1.7f));
	howToData.trans.pos.x = BottomLeft.x;
	howToData.trans.pos.y = BottomLeft.y;
	howToData.trans.angles.Zero();
	howToData.trans.scale = 1;
	howToData.ease.Reset();
	howToData.color = Float4(0.5f, 0.5f, 0.5f, 1);
	howToData.colorDelta = Float4(0.002f, 0.005f, 0.009f, 1);
}

void HowToPlayComponent::UpDate()
{
	ComAssist::GradationColor(moveData.color, moveData.colorDelta);
	ComAssist::GradationColor(shotData.color, shotData.colorDelta);
	ComAssist::GradationColor(howToData.color, howToData.colorDelta);

	const float easeStartPos = (-Engine::GetWindowSize().x / 2.0f) - 150;
	const float easeEndPos = (-Engine::GetWindowSize().x / 2.0f) + 300;
	if (KeyBoard::Down(KeyBoard::Key::KEY_X) && !isShow)
	{
		isShow = true;
		isHide = false;
		drawIn.Reset();
	}
	if (isShow)
	{
		moveData.ease.Run(Easing::QuadOut, 50);
		moveData.trans.pos.x = moveData.ease.GetVolume(easeStartPos, easeEndPos - easeStartPos);
		shotData.ease.Run(Easing::QuadOut, 50);
		shotData.trans.pos.x = shotData.ease.GetVolume(easeStartPos, easeEndPos - easeStartPos);
	}
	if (KeyBoard::Down(KeyBoard::Key::KEY_X) &&
		isShow && moveData.ease.IsEaseEnd())
	{
		isShow = false;
		isHide = true;
	}
	if (!isShow && isHide)
	{
		moveData.ease.Reset();
		shotData.ease.Reset();
		drawIn.Run(Easing::QuadOut, 50);
		moveData.trans.pos.x = drawIn.GetVolume(easeEndPos, easeStartPos - easeEndPos);
		shotData.trans.pos.x = drawIn.GetVolume(easeEndPos, easeStartPos - easeEndPos);
	}
}

void HowToPlayComponent::Draw2D()
{
	moveText.pos = moveData.trans.pos;
	moveText.color = moveData.color;
	moveText.scale = moveData.trans.scale;
	moveText.Draw();

	shotText.pos = shotData.trans.pos;
	shotText.color = shotData.color;
	shotText.scale = shotData.trans.scale;
	shotText.Draw();

	howToText.pos = howToData.trans.pos;
	howToText.color = howToData.color;
	howToText.scale = howToData.trans.scale;
	howToText.Draw();
}

void HowToPlayComponent::Reduction(Easing & reduction)
{
	moveData.trans.scale = reduction.GetVolume(1, 0 - 1);
	shotData.trans.scale = reduction.GetVolume(1, 0 - 1);
	howToData.trans.scale = reduction.GetVolume(1, 0 - 1);
}
