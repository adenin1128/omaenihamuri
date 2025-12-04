#include "BOAAAA.h"
#include "Breath.h"
#include <cstdlib>

//int boaGraphs[1];

Boaaa::Boaaa(int px, int py)
{
	//boaimage= LoadGraph("data/image/BOAAA.png");
	//LoadDivGraph("data/image/BOAAA.png", 1, 1, 1, 64, 64, boaGraphs);
    x = px;
    y = py;
    length = 2000;        // レーザーの長さ
    baseThickness = 25;
    changeThickness = 2;
    buretimer = 0;
}

Boaaa::~Boaaa()
{
}

void Boaaa::Update()
{
    Breath* breath = FindGameObject<Breath>();
    thickness = baseThickness + (rand() % (changeThickness * 2 + 1) - changeThickness);
    buretimer++;
    if (buretimer < 420) {
        (breath->SetState(STATE_FIN));
    }
}


void Boaaa::Draw()
{
    
    // ブラスターが見える条件
    Breath* breath = FindGameObject<Breath>();
    if (breath && breath->GetState() == STATE_GO) {
        // 口の位置
        bx = x * 64 + 128;
        by = y * 64 + 54;
        // アルファいじれる
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        // レーザーの色
        color = GetColor(255, 255, 255);
        // 横レーザー

        DrawBoxAA(bx, by - thickness, bx + length, by + thickness, color, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}