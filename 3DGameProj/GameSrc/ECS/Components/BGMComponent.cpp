#include "BGMComponent.h"

BGMComponent::BGMComponent()
{
	bgm.Load("Resource/Sounds/test.wav", false);
	bgm.SetLoopPoint(0u, 302400u);
	bgm.PlayBGM();
	bgm.SetGain(0.3f);
}

void BGMComponent::StartMain(const bool isPlay)
{
	isMainPlay = isPlay;
}

void BGMComponent::Initialize()
{
	pState = &entity->GetComponent<GameStateComponent>();
	bgm.SetLoopPoint(0u, 302400u);
	isIntroPlay = false;
	isMainPlay = false;
}

void BGMComponent::UpDate()
{
	if ((isMainPlay ||
		pState->GetCurrentState() == GameState::PLAY ||
		pState->GetCurrentState() == GameState::PAUSE) &&
		pState->GetCurrentState() != GameState::END)
	{
		bgm.ExitLoop();
		bgm.SetLoopPoint(1360794u, 1965600u);
	}
	else if (pState->GetCurrentState() == GameState::END)
	{
		//ˆê“x‚¾‚¯ŒÄ‚Ô
		if (!isIntroPlay)
		{
			bgm.ExitLoop();
			isIntroPlay = true;
		}
		//$Test$
		bgm.SetLoopPoint(0u, 302400u);
	}
}

