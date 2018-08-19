#include "GameStateComponent.h"
#include "TomatoComponent.h"
#include "RankingComponent.h"
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
	if (timer->IsTimeOver() && state == GameState::PLAY)
	{
		state = GameState::END;
	}
}

void GameStateComponent::TimerRun()
{
	if (state == GameState::PLAY)
	{
		timer->TimerRun();
	}
}

void GameStateComponent::SetState(const GameState& state_)
{
	state = state_;
}

const GameState GameStateComponent::GetCurrentState() const
{
	return state;
}

void GameStateComponent::SetEntity(const Entity& entity)
{
	if (entity.GetComponent<TomatoComponent>().GetData().empty())
	{
		state = GameState::END;
	}
}

void GameStateComponent::Initialize()
{
	if (!entity->HasComponent<TimerComponent>())
	{
		entity->AddComponent<TimerComponent>();
	}
	timer = &entity->GetComponent<TimerComponent>();
	state = GameState::TITLE;
}

void GameStateComponent::UpDate()
{
	GamePause();
	GameEnd();
	TimerRun();
}

