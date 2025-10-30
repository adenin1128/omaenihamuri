#include "field.h"
#include <vector>
#include "Player.h"
#include "trap.h"
using namespace std;

vector<vector<int>> maps = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,0,0,0,0,0,201,0,202,0,203,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{1,0,0,0,0,0,0,0,201,0,202,0,203,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    {1,0,0,0,0,0,0,0,101,0,102,0,103,0,6,0,0,4,0,0,0,0,0,0,4,0,0,0,0,1 },
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1 },
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6,6,6,1,1,1,1,1,1,1,1,1 },

};
trap* traps[99];
Field::Field()
{
	haikeimage = LoadGraph("data/image/kabe.png");
	hImage = LoadGraph("data/image/New blo.png");
	harimage = LoadGraph("data/image/hari.png");
	hataimage = LoadGraph("data/image/hata.png");
	x = 0;
	y = 1080-64;
	scrollX = 0; 
	HIT_TRAP = 0;
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 2) {
				new Player(x * 64, y * 64);//
			}
		}
	}
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			/*if (maps[y][x] == 101) {
				trap1 = new trap(x * 64, y  * 64);
			}
			if (maps[y][x] == 5) {
				trap2 = new trap(x * 64, y * 64);
			}*/

			if (maps[y][x] > 100 && maps[y][x] < 200) {
				traps[maps[y][x] - 101] = new trap(x * 64, y * 64, maps[y][x] - 101);
			}
		}
	}
}

Field::~Field()
{
}

void Field::Update()
{
	//	scrollX += 1; //強制スクロールの場合
}

void Field::Draw()
{
	DrawRectGraph(0, 0, 0, 0, 1920, 1080, haikeimage, 1);
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 1) {
				DrawGraph(x * 64, y * 64, hImage, 1);
			}
		}
	}
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 4) {
				DrawGraph(x * 64, y * 64,hataimage, 1);
			}
		}
	}
	DrawFormatString(0, 180, GetColor(255, 255, 255), "HITTRAP::%d", HIT_TRAP);
}

int Field::HitCheckRight(int px, int py)
{
	int x = px / 64;
	int y = py/ 64;
	if (y >= maps.size())
		return 0;
	//if (maps[y][x] == 10) {
	//	trap1->Active();
	//	/*trap* t = FindGameObject<trap>();
	//	if (t != nullptr) {
	//		t->Active();
	//	}*/
	//}
	if (maps[y][x] > 200) {
		traps[maps[y][x] - 201]->Active();
	}
	if (maps[y][x] == 1)
	{ // 当たってる 
		return px % 64 + 1;
	}
	return 0;
}





int Field::HitCheckLeft(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (y >= maps.size())
		return 0;
	if (maps[y][x] == 1)
	{ // 当たってる 
		return px % 64 - 64;
	}
	return 0;
}



int Field::HitCheckUp(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (y >= maps.size())
		return 0;
	if (maps[y][x] == 1)
		return 64 - py % 64;
	return 0;
}



int Field::HitCheckDown(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (y >= maps.size())
		return 0;
	if (maps[y][x] == 1)
		return py  % 64 + 1;
	return 0;
}

bool Field::OutOfMap(int px, int py)
{
	if (py < 400 + 64 * maps.size()) {
		return 0;
	}
}

bool Field::Istrap(int px, int py)
{
	if (py < 400) {
		return 0;
	}
	int x = px / 64;
	int y = (py - 400) / 64;
	if (y >= maps.size())
		return 0;
	if (y >= maps.size())
		return 0;
	if (maps[y][x] == 10) {
		return true;
	}
	return false;
}
//int Field::HitCheckRightTrap(int px, int py)
//{
//	int x = px / 64;
//	int y = py / 64;
//	if (maps[y][x] > 100)
//	{ // 当たってる 
//		return px % 64 + 1;
//	}
//	return 0;
//}
//
//int Field::HitCheckLeftTrap(int px, int py)
//{
//	int x = px / 64;
//	int y = py / 64;
//	if (maps[y][x] > 100)
//	{ // 当たってる 
//		return px % 64 - 64;
//	}
//	return 0;
//}
//
//int Field::HitCheckUpTrap(int px, int py)
//{
//	int x = px / 64;
//	int y = py / 64;
//	if (maps[y][x] > 100)
//		return 64 - py % 64;
//	return 0;
//}
//
//int Field::HitCheckDownTrap(int px, int py)
//{
//	int x = px / 64;
//	int y = py / 64;
//	if (maps[y][x] > 100)
//		return py % 64 + 1;
//	return 0;
//}

//二方向触れているとぐわぐわする
//追加のインクルードディレクトの設定がわからない
//↓これ追加のインクルードディレクトに入れないと
// Libraryとこのプロジェクトのファイル（field.hとかなんかここにあるから）DxLIbの追加しないとのやつ