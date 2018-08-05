#include "TimerComponent.h"

void TimerComponent::Initialize()
{
	data.ease.Reset();
	cnt.Reset();
	cnt.SetCounter(1200, 1, 0, 0);
}

void TimerComponent::UpDate()
{
	data.trans.pos.y = (Engine::GetWindowSize().y / 2.0f) - (size * 2);
}

void TimerComponent::Draw2D()
{
	text.Create("Time\n" + std::to_string(cnt.GetMilliSecond(60) / 1000), size, font);
	text.pos.y = data.trans.pos.y;
	text.color = Float4(1, 1, 1, 1);
	text.Draw();
}

void TimerComponent::TimerRun()
{
	cnt.Sub();
}

bool TimerComponent::IsTimeOver()
{
	return cnt.IsMin();
}
