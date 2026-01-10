#pragma once
#include "../Library/GameObject.h"

class Timer : public GameObject
{
public:
	Timer(int stage);
	~Timer();
	void Update() override;

	float GetTime() { return timer; }
	void StartTimer();
	void StopTimer();
	void ResetTimer();

	void AcerageTime();
	float GetAverageTime() { return AT; }

	void deathcount();
	void ResetDeathcount();
	int GetDeathCount() { return Deathcount; }

	void AverageDeathCount();
	float GetAverageDeathCount() { return AD; }

private:
	float timer;
	bool stopwatch;
	int Deathcount;
	float AT;
	float AD;
};