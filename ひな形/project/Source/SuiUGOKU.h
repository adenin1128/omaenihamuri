#pragma once
#include "../Library/GameObject.h"

class SuiUGOKU : public GameObject 
{
public:
    SuiUGOKU(int px, int py);
    ~SuiUGOKU();

    // プレイヤーの座標(px, py)などの情報を引数で受け取るように変更
    // &を付けることで、プレイヤーの座標を直接書き換えられるようにします（乗った時に一緒に動かすため）
    void Update(float& plX, float& plY, float plW, float plH, float& plVY);
    void Draw();

    void Reset();

private:
    int sImage;
    int suiGraphs[2]; // 画像ハンドル

    // 座標とサイズ
    float ResetX, ResetY;

    float x, y;
    float width, height;

    // 上昇スピード
    float moveSpeed;

    int frame;
    int timer;
};