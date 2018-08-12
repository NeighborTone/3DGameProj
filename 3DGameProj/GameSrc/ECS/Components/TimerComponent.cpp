#include "TimerComponent.h"

void TimerComponent::Initialize()
{
	data.ease.Reset();
	data.color = Float4(1, 1, 1, 1);
	cnt.Reset();
	cnt.SetCounter(1800, 1, 0, 0);
}

void TimerComponent::UpDate()
{
	if ((cnt.GetMilliSecond(60) / 1000) <= 10)
	{
		data.color = Float4(1, 0, 0, 1);
	}
	data.trans.pos.y = (Engine::GetWindowSize().y / 2.0f) - (size * 2);
}

void TimerComponent::Draw2D()
{
	text.Create("Time\n" + std::to_string(cnt.GetMilliSecond(60) / 1000), size, font);
	text.pos.y = data.trans.pos.y;
	text.color = data.color;
	text.Draw();
}

void TimerComponent::TimerRun()
{
	cnt.Sub();
}

const bool TimerComponent::IsTimeOver()
{
	return cnt.IsMin();
}

const Counter& TimerComponent::GetTimeLimit() const
{
	return cnt;
}
