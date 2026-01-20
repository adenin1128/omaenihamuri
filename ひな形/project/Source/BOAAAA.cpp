#include "BOAAAA.h"
#include "Breath.h"
#include <cstdlib>
#include <cmath>
#include "Player.h"
#include "StageNumber.h"

//int boaGraphs[1];

//Boaaa::Boaaa(int px, int py)
//{
//	//boaimage= LoadGraph("data/image/BOAAA.png");
//	//LoadDivGraph("data/image/BOAAA.png", 1, 1, 1, 64, 64, boaGraphs);
//    x = px;
//    y = py;
//    length = 2000;        // レーザーの長さ
//    baseThickness = 35;
//    changeThickness = 2;
//    buretimer = 0;
//}

Boaaa::Boaaa(int px, int py, int d, int len)
{
	SEHandle = LoadSoundMem("data/sound/Beam.mp3");
	ChangeVolumeSoundMem(255, SEHandle);

	PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);

	ResetX = px;
	ResetY = py;
	ResetD = d;
	ResetL = len;
	Reset();
}

/*x = px;
  y = py;
  dir = (Direction)d;
  length = len;

  baseThickness = 35;
  changeThickness = 5;
  buretimer = 0;*/

Boaaa::~Boaaa()
{
	// 音楽を止めてメモリから削除
	//DeleteSoundMem(SEHandle);
}

void Boaaa::Reset()
{
	x = ResetX;
	y = ResetY;
	dir = (Direction)ResetD;
	length = ResetL;

	baseThickness = 35;
	changeThickness = 0;
	buretimer = 0;
}

void Boaaa::Update()
{
	rot = 3.14 / 2 * dir;
	Player* player = FindGameObject<Player>();
	StageNumber* stageNumber = FindGameObject<StageNumber>();

	thickness = baseThickness
		+ (rand() % (changeThickness * 2 + 1) - changeThickness);
	if (CheckHitKey(KEY_INPUT_R)) {
		DestroyMe();
		buretimer = 0;
	}



	if (player && CheckHit(player)) {
		if (!(stageNumber && stageNumber->noDeath)) {
			player->SetState(PlayerState::STATE_BOOM);
		}
	}
}



void Boaaa::Draw()
{
	int bx = x + 32;
	int by = y + 32;

	int dx = 0, dy = 0;
	switch (dir) {
	case 0: dy = -1; break; // 上
	case 1: dx = 1; break;  // 右
	case 2: dy = 1; break;  // 下
	case 3: dx = -1; break; // 左
	}

	int ex = bx + dx * length;
	int ey = by + dy * length;

	DrawLineAA(bx, by, ex, ey, GetColor(255, 255, 255), thickness);


	DrawFormatString(0, 300, GetColor(255, 255, 255), "SEHandle: %d", SEHandle);
}


bool Boaaa::CheckHit(Player* player)
{
	float pL = player->GetColliderLeftTop().x;
	float pR = player->GetColliderRightTop().x;
	float pT = player->GetColliderLeftTop().y;
	float pB = player->GetColliderLeftBottom().y;

	int cx = x + 32;
	int cy = y + 32;

	float l, r, t, b;

	switch (dir) {
	case 0: // 上
		l = cx - thickness;
		r = cx + thickness;
		t = cy - length;
		b = cy;
		break;

	case 1: // 右
		l = cx;
		r = cx + length;
		t = cy - thickness;
		b = cy + thickness;
		break;

	case 2: // 下
		l = cx - thickness;
		r = cx + thickness;
		t = cy;
		b = cy + length;
		break;

	case 3: // 左
		l = cx - length;
		r = cx;
		t = cy - thickness;
		b = cy + thickness;
		break;

	default:
		return false;
	}

	// AABB vs AABB
	if (r < pL) return false;
	if (l > pR) return false;
	if (b < pT) return false;
	if (t > pB) return false;

	return true;
}