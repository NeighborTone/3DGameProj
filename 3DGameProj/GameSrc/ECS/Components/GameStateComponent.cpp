#include "GameStateComponent.h"
#include <iostream>
const void GameStateComponent::GamePlay()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		state = GameState::PLAY;
	}
}

const void GameStateComponent::GamePause()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_X) && 
		state != GameState::TITLE && 
		state != GameState::END)
	{
		state = GameState::PAUSE;
	}
}

const void GameStateComponent::GameReset()
{
	if(KeyBoard::Down(KeyBoard::Key::KEY_C) && 
		state != GameState::TITLE &&
		state != GameState::PLAY)
	{
		cnt.Reset();
		state = GameState::RESET;
	}
}

const void GameStateComponent::GameEnd()
{
	if (cnt.GetMilliSecond(60) >= TimeLimit && state == GameState::PLAY)
	{
		state = GameState::END;
	}
}

void GameStateComponent::TimerRun()
{
	if (state == GameState::PLAY)
	{
		cnt.Add();
	}
	
}

GameStateComponent::GameStateComponent():
#undef max
	cnt(0,1,0, std::numeric_limits<int>::max())
{

}

const GameState GameStateComponent::GetCurrentState() const
{
	return state;
}

void GameStateComponent::Initialize()
{
	cnt.Reset();
	state = GameState::TITLE;
}

void GameStateComponent::UpDate()
{
	GamePlay();
	GamePause();
	GameReset();
	GameEnd();
	TimerRun();
}

void GameStateComponent::Draw2D()
{
	std::cout << cnt.GetMilliSecond(60) << std::endl;
}
