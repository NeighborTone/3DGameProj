#include "GameStateComponent.h"
#include "TomatoComponent.h"
#include <iostream>

void GameStateComponent::GamePause()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_X) && 
		state != GameState::TITLE && 
		state != GameState::END)
	{
		state = GameState::PAUSE;
	}
}

void GameStateComponent::GameEnd()
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

void GameStateComponent::SetState(const GameState& state_)
{
	state = state_;
}

const GameState GameStateComponent::GetCurrentState() const
{
	return state;
}

void GameStateComponent::SetEntity(const Entity & tomato)
{
	if (tomato.GetComponent<TomatoComponent>().GetData().empty())
	{
		state = GameState::END;
	}
}

void GameStateComponent::Initialize()
{
	cnt.Reset();
	state = GameState::TITLE;
}

void GameStateComponent::UpDate()
{
	GamePause();
	GameEnd();
	//$Test$
	if (state == GameState::END)
	{
		if (KeyBoard::Down(KeyBoard::Key::KEY_B))
		{
			state = GameState::RESET;
		}
	}
	TimerRun();
}

