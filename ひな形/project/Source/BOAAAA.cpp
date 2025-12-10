#include "BOAAAA.h"
#include "Breath.h"
#include <cstdlib>
#include <cmath>
#include "Player.h"
#include "StageNumber.h"

//int boaGraphs[1];

Boaaa::Boaaa(int px, int py)
{
	//boaimage= LoadGraph("data/image/BOAAA.png");
	//LoadDivGraph("data/image/BOAAA.png", 1, 1, 1, 64, 64, boaGraphs);
    x = px;
    y = py;
    length = 2000;        // レーザーの長さ
    baseThickness = 35;
    changeThickness = 2;
    buretimer = 0;
}

Boaaa::~Boaaa()
{
}

void Boaaa::Update()
{
        Breath* breath = FindGameObject<Breath>();
        Player* player = FindGameObject<Player>();
        StageNumber* stageNumber = FindGameObject<StageNumber>(); 
        thickness = baseThickness + (rand() % (changeThickness * 2 + 1) - changeThickness);
        buretimer++;

        if (buretimer > 5000) {
            if (breath) {
                breath->SetState(STATE_FIN);
            }
        }

        if (breath && breath->GetState() == STATE_GO && player) {

            if (CheckHit(player)) {
                if (!(stageNumber && stageNumber->noDeath)) {
                    player->SetState(PlayerState::STATE_BOOM);
                }
            }
        }
}



void Boaaa::Draw()
{
    Breath* breath = FindGameObject<Breath>();
    if (breath && breath->GetState() == STATE_GO)
    {
        bx = x * 64 + 128;
        by = y * 64 + 54;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        color = GetColor(255, 255, 255);

        DrawBoxAA(bx, by - thickness, bx + length, by + thickness, color, TRUE);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

bool Boaaa::CheckHit(Player* player)
{
    Breath* breath = FindGameObject<Breath>();
    if (!(breath && breath->GetState() == STATE_GO)) {
        return false;
    }
    bx = x * 64 + 128;
    by = y * 64 + 54;
	//AABB 判定用プレイヤー座標取得
    float left = player->GetColliderLeftTop().x;
    float right = player->GetColliderRightTop().x;
    float top = player->GetColliderLeftTop().y;
    float bottom = player->GetColliderLeftBottom().y;

	// AABB 判定
    if (right < bx) return false;                 // プレイヤーがレーザーより左
    if (left > bx + length) return false;         // プレイヤーが右
    if (bottom < by - thickness) return false;    // プレイヤーが上
    if (top > by + thickness) return false;       // プレイヤーが下

    return true;
}