#include "FPS.h"
#include "../Engine.h"
#include "../Utilitys/Utility.hpp"
LARGE_INTEGER FPS::GetCounter() const
{
	//現在の時間を取得
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return counter;
}

LARGE_INTEGER FPS::GetCountFrequency() const
{
	//精度の取得
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}

FPS::FPS():
	frameCount(0),
	frameRate(0),
	time(0),
	deltaTime(0),
	second(0)
{
	Engine::COMInitialize();

	preCount = GetCounter();
	frequency = GetCountFrequency();
}

FPS::~FPS()
{

}

void FPS::UpDate()
{
	LARGE_INTEGER count = GetCounter();
	//どれくらい経過したか
	deltaTime = static_cast<float>(count.QuadPart - preCount.QuadPart) / frequency.QuadPart;
	preCount = GetCounter();

	time += deltaTime;

	++frameCount;
	second += deltaTime;
	//1秒たった
	if (second >= 1.0f)
	{
		frameRate = static_cast<int>(frameCount);
		frameCount = 0;
		second -= 1.0f;
	}
	if (deltaTime < 1.f / MaxFps)
	{
		DWORD sleepTime = static_cast<DWORD>((1.f / MaxFps - deltaTime) * 1000);
		timeBeginPeriod(1); // 分解能を上げる(こうしないとSleepの精度が落ちる模様)
		Sleep(sleepTime);   // 寝る
		DOUT << "sleep****" << sleepTime << std::endl;
		timeEndPeriod(1);   // 戻す
	}

	
}

float FPS::GetTime() const
{
	return time;
}

float FPS::GetDeltaTime() const
{
	return deltaTime;
}

int FPS::GetFrameRate() const
{
	return frameRate;
}
