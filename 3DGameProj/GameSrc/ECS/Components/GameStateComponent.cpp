#include "GameStateComponent.h"

const void GameStateComponent::GamePlay()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		state = GameState::PLAY;
	}
}

const void GameStateComponent::GamePause()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_X) && state != GameState::TITLE)
	{
		state = GameState::PAUSE;
	}
}

const void GameStateComponent::GameReset()
{
	if(KeyBoard::Down(KeyBoard::Key::KEY_C) && state == GameState::PAUSE)
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
	state = GameState::TITLE;
}

void GameStateComponent::UpDate()
{
	GamePlay();
	GamePause();
	GameReset();
}
