#pragma once
#include "../Library/GameObject.h"

class Timer : public GameObject
{
public:
	Timer();
	~Timer();
	void Update() override;

	float GetTime() { return timer; }
	void StartTimer();
	void StopTimer();
	void ResetTimer();
	void deathcount();
	void ResetDeathcount();
	int GetDeathCount() { return Deathcount; }
private:
	float timer;
	bool stopwatch;
	int Deathcount;
};