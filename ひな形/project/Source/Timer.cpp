#include "Timer.h"
#include <vector>
#include "CsvReader.h"

using namespace std;

vector<vector<int>> Times;

Timer::Timer(int stage)
{
	DontDestroyOnSceneChange();

	char filename[60];
	sprintf_s<60>(filename, "data/time%02d.csv", stage);
	CsvReader* csv = new CsvReader(filename);
	csv = new CsvReader(filename);
	int lines = csv->GetLines();
	lines = csv->GetLines();
	Times.resize(lines);
	for (int y = 0; y < lines; y++) {
		int cols = csv->GetColumns(y);
		Times[y].resize(cols);
		for (int x = 0; x < cols; x++) {
			int num = csv->GetInt(y, x);
			Times[y][x] = num;
		}
	}

	timer = 0.0f;
	stopwatch = false;
	Deathcount = 0;
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

void Timer::AcerageTime()
{

}

void Timer::deathcount()
{
	Deathcount++;
}

void Timer::ResetDeathcount()
{
	Deathcount = 0;
}

void Timer::AverageDeathCount()
{
}
