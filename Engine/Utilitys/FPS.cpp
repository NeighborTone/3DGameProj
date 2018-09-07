#include "FPS.h"
#include "../Engine.h"

LARGE_INTEGER FPS::GetCounter() const
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return counter;
}

LARGE_INTEGER FPS::GetCountFrequency() const
{
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
	if (frameCont2 == 0)
	{
		startTime = GetTime();
	}
	if (frameCont2 == AVG)
	{
		float t = GetTime();
		fps = 1000.f / ((t - startTime) / AVG);
		frameCont2 = 0;
		startTime = t;
	}
	++frameCont2;

	LARGE_INTEGER count = GetCounter();
	deltaTime = static_cast<float>(count.QuadPart - preCount.QuadPart) / frequency.QuadPart;
	preCount = GetCounter();

	time += deltaTime;

	++frameCount;
	second += deltaTime;
	if (second >= 1.0f)
	{
		frameRate = static_cast<int>(frameCount);
		frameCount = 0;
		second -= 1.0f;
	}


	
}

void FPS::Wait()
{
	int tookTime = static_cast<int>(GetTime() - startTime);	//‚©‚©‚Á‚½ŽžŠÔ
	int waitTime = frameCont2 * 1000 / Rate - tookTime;	//‘Ò‚Â‚×‚«ŽžŠÔ
	if (waitTime > 0) 
	{
		Sleep(waitTime);
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
