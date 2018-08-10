#include "BGMComponent.h"

BGMComponent::BGMComponent()
{
	bgm.Load("Resource/Sounds/test.wav", false);
	bgm.SetLoopPoint(0u, 302400u);
	bgm.PlayBGM();
	bgm.SetGain(0.3f);
}

void BGMComponent::CheckState(const GameState& state)
{
	if (state == GameState::PLAY)
	{
		
	}

	if (state == GameState::END)
	{
		
		
	}
}

void BGMComponent::Initialize()
{
	pState = &entity->GetComponent<GameStateComponent>();
	IsIntroPlay = false;
	IsMainPlay = false;
}

void BGMComponent::UpDate()
{
	if (pState->GetCurrentState() == GameState::PLAY ||
		pState->GetCurrentState() == GameState::PAUSE)
	{
		//$Test$
		//if (!IsMainPlay)
		//{
			bgm.ExitLoop();
			IsMainPlay = true;
		//}
		
		bgm.SetLoopPoint(1360794u, 1965600u);
	}
	else if (pState->GetCurrentState() == GameState::END)
	{
		//ˆê“x‚¾‚¯ŒÄ‚Ô
		if (!IsIntroPlay)
		{
			bgm.ExitLoop();
			IsIntroPlay = true;
		}
		//$Test$
		bgm.SetLoopPoint(0u, 302400u);
	}
}

