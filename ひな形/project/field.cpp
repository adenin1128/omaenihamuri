#include "field.h"
#include <vector>

using namespace std;

vector<vector<int>> maps = {
	{1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{0,2,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1 },
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};

Field::Field()
{
	hImage = LoadGraph("data/image/bgchar.png");
	x = 0;
	y = 600;
}

Field::~Field()
{
}

void Field::Update()
{
	//	scrollX += 1; //�����X�N���[���̏ꍇ
}

void Field::Draw()
{
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 1) {
				DrawRectGraph(x * 64, y * 64 + 400, 0, 32, 64, 64, hImage, 1);
			}
		}
	}
}

int Field::HitCheckRight(int px, int py)
{
	if (py < 400)
		return 0;
	int x = px / 64;
	int y = (py - 400) / 64;
	if (maps[y][x] == 1)
		return px % 64 + 1;
	return 0;
}

int Field::HitCheckLeft(int px, int py)
{
	if (py < 400)
		return 0;
	int x = px / 64;
	int y = (py - 400) / 64;
	if (maps[y][x] == 1)
		return 64 - px % 64;
	return 0;
}

int Field::HitCheckUp(int px, int py)
{
	if (py < 400)
		return 0;
	int x = px / 64;
	int y = (py - 400) / 64;
	if (maps[y][x] == 1)
		return 64 - (py - 400) % 64;
	return 0;
}

int Field::HitCheckDown(int px, int py)
{
	if (py < 400) {
		return 0;
	}
	int x = px / 64;
	int y = (py - 400) / 64;
	if (maps[y][x] == 1)
		return (py - 400) % 64 + 1;
	return 0;
}

