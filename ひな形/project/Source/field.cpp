#include "field.h"
#include <vector>
#include <memory>
#include "Player.h"
#include "trap.h"
#include "respawn.h"
#include "Trigger.h"
#include "CsvReader.h"
#include "Nyoki.h"
#include "Clear.h"
#include "updraft.h"
#include "Gravity.h"
#include "NeoGravity.h"
#include "downdraft.h"
#include "MoveFloor.h"
#include "Gameover.h"
#include "Skeleton.h"
#include "BeltConveyor.h"
#include "BeltConveyorL.h"
#include "BC.h"
#include "Breath.h"
#include "NyokiTrap.h"
#include "NyokiTrap2.h"
#include "NyokiTrap3.h"
#include "NyokiTrap4.h"
#include "Fader.h"
#include "SuiUGOKU.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>

using namespace std;

//vector<vector<int>> maps = {
//	//199は固定針！動かしたらあかん
//	//0:空白 1:地面（ブロック） 4:中間 5:すり抜けブロック 6:透明ブロック 7:Goal 
//  //9:Nyoki発動 10:Nyoki1 11:Nyoki2 12:Nyoki3 14:Nyokistop
//  //13:透明ブロック生成 15:上昇気流 16:上昇解除 17:Jetpack 19:Jetpack解除
//  //18:低速落下 20:ランダムワープゲート 21:簡単ゲート 22:難しゲート
//  //23:コンベア右 24:コンベア左 25:コンベア反転　26:反転起動
//  //30:動く床開始 31:動く床中間1 32:動く床中間2 33:動く床終点
//	//101～199:トラップの針 201～299:トラップを動かすための場所
//};

vector<vector<int>> maps;
vector<vector<int>> saveMaps;
vector<vector<int>> trapDatas;
vector<vector<int>> breathDatas;


trap* traps[99];
Breath* breaths[99];

int doorGraphs[7];
int kaiheiGraphs[9];
int EasyGraphs[8];
int HGgraphs[8];
int WGgraphs[5];

void GenerateTrap(int posx, int posy, int id) {
	int direction = 0, tx = 0, ty = 0;
	for (int y = 0; y < trapDatas.size(); y++) {
		if (trapDatas[y][0] == id) {
			direction = trapDatas[y][1];
			tx = trapDatas[y][2];
			ty = trapDatas[y][3];
		}
	}
	traps[id - 101] = new trap(posx, posy, id, direction, tx, ty);

}
;
void GenerateBreath(int posx, int posy, int id) {
	int direction = 0, tx = 0, ty = 0;

	for (int y = 0; y < breathDatas.size(); y++) {
		if (breathDatas[y][0] == id) {
			direction = breathDatas[y][1];
			tx = breathDatas[y][2];
			ty = breathDatas[y][3];
		}
	}
	int index = id - 401;
	if (index >= 0 && index < 99) {
		breaths[index] = new Breath(posx, posy, id, direction, tx, ty);
	}
}



Field::Field(int stage)
{
	clear = false;
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

	sprintf_s<60>(filename, "data/trap%02d.csv", stage);
	csv = new CsvReader(filename);
	lines = csv->GetLines();
	trapDatas.resize(lines);
	for (int y = 0; y < lines; y++) {
		int cols = csv->GetColumns(y);
		trapDatas[y].resize(cols);
		for (int x = 0; x < cols; x++) {
			int num = csv->GetInt(y, x);
			trapDatas[y][x] = num;
		}
	}

	sprintf_s<60>(filename, "data/breath%02d.csv", stage);
	csv = new CsvReader(filename);
	lines = csv->GetLines();
	breathDatas.resize(lines);
	for (int y = 0; y < lines; y++) {
		int cols = csv->GetColumns(y);
		breathDatas[y].resize(cols);
		for (int x = 0; x < cols; x++) {
			int num = csv->GetInt(y, x);
			breathDatas[y][x] = num;
		}
	}

	saveMaps = maps;
	SetDrawOrder(100);
	hImage = LoadGraph("data/image/New blo.png");
	doorimage = LoadGraph("data/image/GOOOOOOOOOOAL.png");
	LoadDivGraph("data/image/GOOOOOOOOOOAL.png", 7, 7, 1, 64, 64, doorGraphs);
	kaiheiimage = LoadGraph("data/image/GOOOOOOOOAL/png");
	LoadDivGraph("data/image/GOOOOOOOOAL.png", 9, 9, 1, 64, 64, kaiheiGraphs);
	easyImage = LoadGraph("data/image/EasyGate.png");//簡単用ゲート
	LoadDivGraph("data/image/EasyGate.png", 8, 8, 1, 518, 518, EasyGraphs);
	HGimage = LoadGraph("data/image/HardGate.png");
	LoadDivGraph("data/image/HardGate.png", 8, 8, 1, 768, 768, HGgraphs);
	gokunobanImage = LoadGraph("data/image/AonoOkonomiyaki.png");
	LoadDivGraph("data/image/AonoOkonomiyaki.png", 5, 5, 1, 128, 128, WGgraphs);
	assert(gokunobanImage > 0);

	x = 0;
	y = 1080 - 64;
	scrollX = 0;
	HIT_TRAP = 0;
	deathcount = 1;
	size = 2;
	timer = 0;
	for (int& f : frame) {
		f = 0;
	}
	state = STATE_0;
	hit = false;
	jet = false;
	DL = 0;
	one = false;
	two = false;
	skHit = false;
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 2) {
				new Player(x * 64, y * 64);
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

			//↓トラップ
			if (maps[y][x] > 100 && maps[y][x] < 200) {
				GenerateTrap(x * 64, y * 64, maps[y][x]);
			}
			if (maps[y][x] >= 401 && maps[y][x] < 500) {
				GenerateBreath(x * 64, y * 64, maps[y][x]);
			}
			if (maps[y][x] == 4) {
				new respawn(x * 64, y * 64);
			}
			if (maps[y][x] == 15) {
				new Updraft(x * 64, y * 64);
			}
			if (maps[y][x] == 16) {
				new Gravity(x * 64, y * 64);
			}
			if (maps[y][x] == 17) {
				Jetpack(x, y);
			}
			if (maps[y][x] == 18) {
				new NeoGravity(x * 64, y * 64);
			}
			if (maps[y][x] == 30) {
				new MoveFloor(x * 64, y * 64);
			}
			if (maps[y][x] == 23) {
				new BeltConveyor(x * 64, y * 64);
			}
			if (maps[y][x] == 24) {
				new BeltConveyorL(x * 64, y * 64);
			}
			if (maps[y][x] == 25) {
				new BC(x * 64, y * 64);
			}
			if (maps[y][x] == 80) { //右向き
				new NyokiTrap(x * 64 - 64, y * 64);
			}
			if (maps[y][x] == 81) {//左向き
				new NyokiTrap2(x * 64 + 64, y * 64);
			}
			if (maps[y][x] == 82) {//上向き
				new NyokiTrap3(x * 64, y * 64 + 64);
			}
			if (maps[y][x] == 83) {//下向き
				new NyokiTrap4(x * 64, y * 64 - 64);
			}
			if (maps[y][x] == 40) {
				new SuiUGOKU(x * 64, y * 64);
			}
		}
	}
}

Field::~Field()
{
	DeleteGraph(hImage);
	DeleteGraph(doorimage);
	DeleteGraph(kaiheiimage);
	DeleteGraph(easyImage);
	DeleteGraph(HGimage);
	DeleteGraph(gokunobanImage);
}

void Field::Update()
{
	if (KeyTrigger::CheckTrigger(KEY_INPUT_R)) {
#if true	
		{
			skHit = false;
			hit = false;
			deathcount++;
		}
		{
			GameOver* obj = FindGameObject<GameOver>();
			if (obj != nullptr)
				obj->DestroyMe();
		}
		{
			Fader* fader = FindGameObject<Fader>();
			fader->FadeOut(0.3f);
		}
		{
			auto objs = FindGameObjects<Player>();
			for (auto obj : objs) {
				for (int y = 0; y < saveMaps.size(); y++) {
					for (int x = 0; x < saveMaps[y].size(); x++) {
						if (saveMaps[y][x] == 2) {
							obj->Reset(x * 64, y * 64);
						}
					}
				}
			}
		}
		{
			auto objs = FindGameObjects<Nyoki>();
			for (auto obj : objs)
				obj->Reset();
		}
		{
			auto objs = FindGameObjects<trap>();
			for (auto obj : objs)
				obj->Reset();
		}
		{
			auto objs = FindGameObjects<MoveFloor>();
			for (auto obj : objs)
				obj->Reset();
		}
		{
			auto objs = FindGameObjects<NyokiTrap>();
			for (auto obj : objs)
				obj->Reset();
		}
		{
			auto objs = FindGameObjects<NyokiTrap2>();
			for (auto obj : objs)
				obj->Reset();
		}
		{
			auto objs = FindGameObjects<NyokiTrap3>();
			for (auto obj : objs)
				obj->Reset();
		}
		{
			auto objs = FindGameObjects<NyokiTrap4>();
			for (auto obj : objs)
				obj->Reset();
		}
		{
			auto objs = FindGameObjects<SuiUGOKU>();
			for (auto obj : objs)
				obj->Reset();
		}

		{
			Fader* fader = FindGameObject<Fader>();
			fader->FadeIn(0.3f);
		}

#else
		hit = false;
		int freme = 0;
		for (auto& trap : traps) {
			if (trap != nullptr) {
				freme += 1;
				trap->DestroyMe();
			}
		}
		deathcount++;
		for (int y = 0; y < saveMaps.size(); y++) {
			for (int x = 0; x < saveMaps[y].size(); x++) {
				if (saveMaps[y][x] == 2) {
					FindGameObject<Player>()->DestroyMe();
					new Player(x * 64, y * 64);
				}

				// trap再生成
				//if (freme >= 1) {
				if (saveMaps[y][x] > 100 && saveMaps[y][x] < 200) {
					GenerateTrap(x * 64, y * 64, saveMaps[y][x]);
					freme = 0;
				}
				//}
				/*if (saveMaps[y][x] == 11) {
					FindGameObject<Skeleton>()->DestroyMe();
					new Skeleton(x * 64, y * 64);
				}*/
				/*if (hit == true) {
					if (saveMaps[y][x] == 10) {
						FindGameObject<Nyoki>()->DestroyMe();
					}
				}*/
			}
		}
#endif
	}
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
	{
		timer++;
		{
			if (timer % 10 == 0) {
				frame[0]++;
				if (frame[0] >= 8) {
					frame[0] = 0;
				}
			}
			for (int y = 0; y < maps.size(); y++) {
				for (int x = 0; x < maps[y].size(); x++) {
					if (maps[y][x] == 21) {
						DrawRotaGraph(x * 64 + 35, y * 64 + 34, 0.5, 0, EasyGraphs[frame[0]], TRUE, FALSE);
					}
				}
			}
		}
		{
			if (timer % 10 == 0) {
				frame[1]++;
				if (frame[1] >= 8) {
					frame[1] = 0;
				}
			}
			for (int y = 0; y < maps.size(); y++) {
				for (int x = 0; x < maps[y].size(); x++) {
					if (maps[y][x] == 22) {
						DrawRotaGraph(x * 64 + 32, y * 64 - 32, 0.35, 0, HGgraphs[frame[1]], TRUE, FALSE);
					}
				}
			}
		}
		{
			if (timer % 10 == 0) {
				frame[2]++;
				if (frame[2] >= 5) {
					frame[2] = 0;
				}
			}
			for (int y = 0; y < maps.size(); y++) {
				for (int x = 0; x < maps[y].size(); x++) {
					if (maps[y][x] == 20) {
						DrawRotaGraph(x * 64 + 32, y * 64 + 32, 0.75, 0, WGgraphs[frame[2]], TRUE, FALSE);
					}
				}
			}
		}
	}
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 7) {
				{
					timer++;
					if (timer % 10 == 0) {
						frame[3]++;

						if (frame[3] >= 7) {
							frame[3] = 0;
						}
					}
					if (state == STATE_0) {
						DrawRotaGraph(x * 64 + 32, y * 64 + 32, size, 0, doorGraphs[frame[3]], TRUE, FALSE);
					}
				}
				{
					if (frame[4] < 8) {
						if (timer % 15 == 0) {
							frame[4]++;
						}
						timer++;
					}
					if (state == STATE_1) {
						DrawRotaGraph(x * 64 + 32, y * 64 + 32, size, 0, kaiheiGraphs[frame[4]], TRUE, FALSE);
						if (frame[4] >= 8) {
							state = STATE_2;
						}
					}
				}

				if (state == STATE_2) {
					DrawRotaGraph(x * 64 + 32, y * 64 + 32, size, 0, kaiheiGraphs[8], TRUE, FALSE);
				}
			}
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
	DrawFormatString(0, 280, GetColor(255, 255, 255), "BeltHit::%d", BeltHit);
	if (hit == true)
		DrawString(0, 320, "hit", GetColor(255, 255, 255));
	if (jet == true)
		DrawString(0, 320, "hit", GetColor(255, 255, 255));
	if (skHit == true)
		DrawString(0, 320, "skHit", GetColor(255, 255, 255));
}

void Field::CheckTrap(int x, int y) {
	if (maps[y][x] > 200 && maps[y][x] < 300) {
		traps[maps[y][x] - 201]->Active();
	}
}

void Field::CheckBreath(int x, int y)
{
	int id = maps[y][x];

	// トリガー（501～599)Breath を起動
	if (id >= 501 && id < 600) {
		int index = id - 501;
		if (index >= 0 && index < 99 && breaths[index] != nullptr) {
			breaths[index]->Active();
		}
	}

	// 直接踏んだ場合
	if (id >= 401 && id < 500) {
		int index = id - 401;
		if (index >= 0 && index < 99 && breaths[index] != nullptr) {
			breaths[index]->Active();
		}
	}
}



int Field::HitCheckRight(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (OutOfMap(x, y))
		return 0;
	CheckTrap(x, y);
	CheckBreath(x, y);
	if (maps[y][x] == 1)
	{ // 当たってる 
		return px % 64 + 1;
	}
	if (skHit == true) {
		if (maps[y][x] == 6) {
			return px % 64 + 1;
		}
	}
	return 0;
}

int Field::HitCheckLeft(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (OutOfMap(x, y))
		return 0;
	CheckTrap(x, y);
	CheckBreath(x, y);
	if (maps[y][x] == 1)
	{ // 当たってる 
		return px % 64 - 64;
	}
	if (skHit == true) {
		if (maps[y][x] == 6) {
			return px % 64 - 64;
		}
	}
	return 0;
}

int Field::HitCheckUp(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (OutOfMap(x, y))
		return 0;
	CheckTrap(x, y);
	CheckBreath(x, y);
	if (maps[y][x] == 1)
		return 64 - py % 64;
	if (skHit == true) {
		if (maps[y][x] == 6) {
			return 64 - py % 64;
		}
	}
	return 0;
}

int Field::HitCheckDown(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (OutOfMap(x, y))
		return 0;
	CheckTrap(x, y);
	CheckBreath(x, y);
	if (maps[y][x] == 1)
		return py % 64 + 1;
	if (skHit == true) {
		if (maps[y][x] == 6) {
			return px % 64 + 1;
		}
	}
	return 0;
}


bool Field::OutOfMap(int x, int y)
{
	if (y >= maps.size() || y < 0 || x >= maps[0].size() || x < 0) {
		return true;
	}
	return false;
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
	return false;
}


void Field::ChangeMapChip(int x, int y, int type)
{
	saveMaps[y][x] = type;
}
void Field::ChangeRespawnPoint(int x, int y)
{
	Player* player = FindGameObject<Player>();
	if (player != nullptr) {
		if (player->GetState() == STATE_NORMAL) {
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
	}
}

bool Field::IsGoal(int px, int py)
{
	if (py < 0) {
		return 0;
	}
	int x = (px + 32) / 64;
	int y = (py + 32) / 64;
	if (OutOfMap(x, y))
		return 0;
	if (maps[y][x] == 7) {
		return true;
	}
	return false;
}

int Field::NyokiMove(int px, int py)
{
	int x = (px + 32) / 64;
	int y = (py + 32) / 64;
	if (OutOfMap(x, y))
		return 0;
	Nyoki* nk = FindGameObject<Nyoki>();
	if (nk != nullptr) return 0;

	if (maps[y][x] == 9 && !hit) {
		for (int y = 0; y < maps.size(); y++) {
			for (int x = 0; x < maps[y].size(); x++) {
				if (maps[y][x] == 10) {
					new Nyoki(x * 64, y * 64, -19 * 64, 4);
					hit = true;
					return true;
				}
			}
		}
	}
	return 0;
}

bool Field::IsSkeleton(int px, int py) {
	int x = px / 64;
	int y = py / 64;

	// 境界チェック
	if (y < 0 || y >= maps.size()) return false;
	if (x < 0 || x >= maps[y].size()) return false;

	// 13タイルに入ったら一度だけ全6タイルに配置
	if (maps[y][x] == 13 && !skHit) {
		for (int iy = 0; iy < maps.size(); ++iy) {
			for (int ix = 0; ix < maps[iy].size(); ++ix) {
				if (maps[iy][ix] == 6) {
					skeletons.emplace_back(std::make_unique<Skeleton>(ix * 64, iy * 64));
				}
			}
		}
		skHit = true;
	}
	return false;
}



bool Field::Jetpack(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (OutOfMap(x, y))
		return 0;
	if (maps[y][x] == 17) {
		jet = true;
	}
	else if (maps[y][x] == 19) {
		jet = false;
	}
	return false;
}

bool Field::IsGate(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (OutOfMap(x, y))
		return 0;
	if (maps[y][x] == 20) {
		DL = 20;
	}
	if (maps[y][x] == 21) {
		DL = 21;
	}
	if (maps[y][x] == 22) {
		DL = 22;
	}
	return false;
}

int Field::IsBelt(int px, int py)
{
	int x = (px + 32) / 64;
	int y = (py + 32) / 64;
	if (OutOfMap(x, y))
		return 0;
	if (maps[y][x] == 23) {
		BeltHit = 23;
	}
	else if (maps[y][x] == 24) {
		BeltHit = 24;
	}
	else if (maps[y][x] == 25) {
		BeltHit = 24;
	}
	else {
		BeltHit = 0;
	}
	return false;
}

int Field::IsBC(int px, int py)
{
	int x = (px + 32) / 64;
	int y = (py + 32) / 64;
	if (OutOfMap(x, y))
		return 0;
	if (maps[y][x] == 26) {
		BCHit = 26;
	}
	return 0;
}




int Field::Movefloor(int px, int py)
{
	MoveFloor* mf = FindGameObject<MoveFloor>();
	if (!mf) return 0;

	int x40 = -1, x41 = -1, x42 = -1, x43 = -1;

	for (int yy = 0; yy < (int)maps.size(); ++yy) {
		for (int xx = 0; xx < (int)maps[yy].size(); ++xx) {
			if (maps[yy][xx] == 40)      x40 = xx;
			else if (maps[yy][xx] == 41) x41 = xx;
			else if (maps[yy][xx] == 42) x42 = xx;
			else if (maps[yy][xx] == 43) x43 = xx;
		}
	}

	switch (mf->GetState()) {
	case STATE_A: // 30 -> 31
		if (x40 < 0 || x41 < 0) return 0;
		return (x41 - x40) * 64;

	case STATE_B: // 31 -> 32
		if (x41 < 0 || x42 < 0) return 0;
		return (x42 - x41) * 64;

	case STATE_C: // 32 -> 33
		if (x42 < 0 || x43 < 0) return 0;
		return (x43 - x42) * 64;
	case STATE_D: // 33 -> 31
		if (x43 < 0 || x41 < 0) return 0;
		return (x41 - x43) * 64;
	}

	return 0;
}
// 距離計算用関数 (SuiUGOKUを取得するように変更)
int Field::Suiugoku(int px, int py)
{
	// ★SuiUGOKUのヘッダーをインクルードしていないとここでエラーになります
	SuiUGOKU* mf = FindGameObject<SuiUGOKU>();
	if (!mf) return 0;

	int x30 = -1, x31 = -1, x32 = -1, x33 = -1;

	for (int yy = 0; yy < (int)maps.size(); ++yy) {
		for (int xx = 0; xx < (int)maps[yy].size(); ++xx) {
			if (maps[yy][xx] == 30)      x30 = xx;
			else if (maps[yy][xx] == 31) x31 = xx;
			else if (maps[yy][xx] == 32) x32 = xx;
			else if (maps[yy][xx] == 33) x33 = xx;
		}
	}

	// ★変更：Enum名を新しいものに
	switch (mf->GetState()) {
	case SUI_STATE_A: // 30 -> 31
		if (x30 < 0 || x31 < 0) return 0;
		return (x31 - x30) * 64;

	case SUI_STATE_B: // 31 -> 32
		if (x31 < 0 || x32 < 0) return 0;
		return (x32 - x31) * 64;

	case SUI_STATE_C: // 32 -> 33
		if (x32 < 0 || x33 < 0) return 0;
		return (x33 - x32) * 64;
	case SUI_STATE_D: // 33 -> 31
		if (x33 < 0 || x31 < 0) return 0;
		return (x31 - x33) * 64;
	}

	return 0;
}

// ★この関数も忘れずに Field.cpp にある必要があります
bool Field::GetPointPos(int id, int* ox, int* oy)
{
	for (int y = 0; y < (int)maps.size(); ++y) {
		for (int x = 0; x < (int)maps[y].size(); ++x) {
			if (maps[y][x] == id) {
				*ox = x * 64;
				*oy = y * 64;
				return true;
			}
		}
	}
	return false;
}

int Field::IsBreath(int px, int py) {
	/*if (maps[y][x] == 8) {

	}*/
	return 0;
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