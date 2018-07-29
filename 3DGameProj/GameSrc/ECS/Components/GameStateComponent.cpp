#include "GameStateComponent.h"

const void GameStateComponent::GamePlay()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		state = GameState::PLAY;
	}
}

const void GameStateComponent::GameStop()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_X))
	{
		state = GameState::STOP;
	}
}

const void GameStateComponent::GameReset()
{
	if(KeyBoard::Down(KeyBoard::Key::KEY_C))
	{
		state = GameState::RESET;
	}
}

const GameState GameStateComponent::GetCurrentState() const
{
	return state;
}

void GameStateComponent::Initialize()
{
	state = GameState::STOP;
}

void GameStateComponent::UpDate()
{
	GamePlay();
	GameStop();
	GameReset();
}
