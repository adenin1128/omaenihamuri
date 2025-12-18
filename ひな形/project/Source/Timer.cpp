#include "Timer.h"

Timer::Timer()
{
	DontDestroyOnSceneChange();
	timer = 0.0f;
	stopwatch = false;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	if(stopwatch == true)
	{
		timer++;
	}
}

void Timer::StartTimer()
{
	stopwatch = true;
}

void Timer::StopTimer()
{
	stopwatch = false;
}

void Timer::ResetTimer()
{
	timer = 0.0f;
}
