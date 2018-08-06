#include "PauseComponent.h"

PauseComponent::PauseComponent()
{
	sprite.Load("Resource/Texture/pause.png");
	text.Create("PAUSE", 40);
}

void PauseComponent::Initialize()
{
	data.ease.Reset();
	data.trans.pos = 0;
	data.trans.scale = 0;
}

void PauseComponent::UpDate()
{
	data.ease.Run(Easing::QuadIn, 20);
	data.trans.scale = data.ease.GetVolume(0, 1);
}

void PauseComponent::Draw2D()
{
	text.pos = data.trans.pos;
	text.scale = data.trans.scale;
	text.color = Float4(1, 1, 1, 1);
	text.Draw();
	
	sprite.color.a = 0.5f;
	sprite.Draw();
}

const GameState PauseComponent::GetState()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_X))
	{
		data.ease.Reset();
		data.trans.scale = 0;
		return GameState::PLAY;
	}
	if (KeyBoard::Down(KeyBoard::Key::KEY_C))
	{
		return GameState::RESET;
	}
	return GameState::PAUSE;
}
