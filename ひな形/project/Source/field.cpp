#include "field.h"
#include <vector>
#include "Player.h"
#include "trap.h"
#include "respawn.h"
#include "Trigger.h"
#include "downtrap.h"
#include "CsvReader.h"
using namespace std;

//vector<vector<int>> maps = {
//	//199は固定針！動かしたらあかん
//	//0:空白 1:地面（ブロック） 4:中間 5:すり抜けブロック 
//	//101～199:トラップの針 201～299:トラップを動かすための場所
//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
//  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
//	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
//	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
//	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
//	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
//	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
//	{1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
//	{1,0,0,0,0,0,0,0,0,0,0,315,314,313,312,311,310,309,308,307,306,305,304,303,302,301,0,0,0,1 },
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,209,0,0,1 },
//	{1,1,1,0,1,0,1,0,5,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1 },
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,208,208,1,108 },
//	{1,0,0,0,0,0,0,0,201,0,202,0,0,0,0,0,203,203,204,205,206,0,0,0,0,0,0,0,1,1 },
//	{1,0,0,0,0,0,0,0,201,0,202,0,0,0,0,0,203,203,204,205,206,0,0,0,0,207,0,0,0,1 },
//  {1,2,0,0,0,0,0,0,101,0,102,0,103,0,0,203,203,4,0,0,0,0,0,0,4,207,0,0,0,1 },
//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,104,105,109,1,1,1,1,1,1,1,1,1 },
//  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,106,0,0,1,1,1,107,1,1,1,1 },
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },//見えないトラップ置くゾーン
//
//};

vector<vector<int>> maps;
vector<vector<int>> saveMaps;
trap* traps[99];
downtrap* downtraps[99];
Field::Field(int stage)
{
	char filename[60];
	sprintf_s<60>(filename, "data/Stage%02d.csv", stage);

	CsvReader* csv = new CsvReader(filename);
	int lines = csv->GetLines();
	maps.resize(lines);
	for (int y = 0; y < lines; y++) {
		int cols = csv->GetColumns(y);
		maps[y].resize(cols);
		for (int x = 0; x < cols; x++) {
			int num = csv->GetInt(y, x);
			maps[y][x] = num;
		}
	}

	saveMaps = maps;
	haikeimage = LoadGraph("data/image/kabe.png");
	hImage = LoadGraph("data/image/New blo.png");
	harimage = LoadGraph("data/image/hari.png");
	hataimage = LoadGraph("data/image/hata.png");
	harisitaimage = LoadGraph("data/image/harisita.png");
	x = 0;
	y = 1080-64;
	scrollX = 0; 
	HIT_TRAP = 0;
	deathcount = 1;
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

			if (maps[y][x] > 300 && maps[y][x] < 400) {
				downtraps[maps[y][x] - 301] = new downtrap(x * 64, y * 64, maps[y][x] - 301);
			}

			if (maps[y][x] == 4) {
				new respawn(x * 64, y * 64);
			}
		}
	}
}

Field::~Field()
{
}

void Field::Update()
{
	if (KeyTrigger::CheckTrigger(KEY_INPUT_R)) {
		for (auto& trap : traps) {
			if (trap != nullptr) {
				trap->DestroyMe();
			}		
		}
		deathcount++;
		for (int y = 0; y < saveMaps.size();y++) {
			for (int x = 0;x < saveMaps[y].size();x++) {
				if (saveMaps[y][x] == 2) {
					FindGameObject<Player>()->DestroyMe();
					new Player(x * 64, y * 64);
				}

				// trap再生成
				if (maps[y][x] > 100 && maps[y][x] < 200) {
					traps[maps[y][x] - 101] = new trap(x * 64, y * 64, maps[y][x] - 101);
				}
			}
		}
	}
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
			int id = maps[y][x];

		/*	if (id >= 107 && id <= 122) {
				DrawGraph(x * 64, y * 64, harisitaimage, TRUE);
			}*/
		}
	}


	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 5) {
				DrawGraph(x * 64, y * 64, hImage, 1);
			}
		}
	}
	/*for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 4) {
				DrawGraph(x * 64, y * 64,hataimage, 1);
			}
		}
	}*/
	DrawFormatString(0, 180, GetColor(255, 255, 255), "HITTRAP::%d", HIT_TRAP);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "deathcount::%d", deathcount);
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
	if (maps[y][x] > 200) {
		traps[maps[y][x] - 201]->Active();
	}
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
	if (maps[y][x] > 200) {
		traps[maps[y][x] - 201]->Active();
	}
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
	if (maps[y][x] > 200) {
		traps[maps[y][x] - 201]->Active();
	}
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


void Field::ChangeMapChip(int x, int y, int type)
{
	saveMaps[y][x] = type;
}
void Field::ChangeRespawnPoint(int x, int y)
{
	if (maps[y][x] == 4) {
		// リスポーンポイントの削除
		for (int my = 0; my < saveMaps.size(); my++) {
			for (int mx = 0; mx < saveMaps[my].size(); mx++) {
				if (saveMaps[my][mx] == 2) {
					saveMaps[my][mx] = 0;
				}
			}
		}

		// saveMaps[y][x]をリスポーンポイントに設定
		ChangeMapChip(x, y, 2);
	}
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