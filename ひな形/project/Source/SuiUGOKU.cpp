#include "SuiUGOKU.h"
#include <cmath>    // std::abs 等を使用する場合
#include <assert.h> // 画像読み込みチェック用

SuiUGOKU::SuiUGOKU(int px, int py)
{
    // 座標の初期化
    ResetX = static_cast<float>(px);
    ResetY = static_cast<float>(py);

    
    // 画像読み込み
    sImage = LoadGraph("data/image/すい.png");
    LoadDivGraph("data/image/すい.png", 2, 2, 1, 640, 640, suiGraphs);

    // 画像が正しく読めたかチェック
    assert(sImage > 0);

    Reset();
}

SuiUGOKU::~SuiUGOKU()
{
    // 必要であれば画像やリソースの削除処理
}

void SuiUGOKU::Reset()
{
    x = ResetX;
    y = ResetY;

    // 当たり判定サイズの設定
 // ※画像の描画倍率(0.2倍など)に合わせて調整してください
 // ここでは前回のコードを参考に64pxとしています
    width = 64.0f;
    height = 64.0f;

    // 上昇スピード
    moveSpeed = 2.0f;

    // アニメーション用
    frame = 0;
    timer = 0;
    size = 64;
}

// ---------------------------------------------------------
// Update
// 引数でプレイヤーの情報(座標や速度)を受け取り、直接書き換える
// ---------------------------------------------------------
void SuiUGOKU::Update(float& plX, float& plY, float plW, float plH, float& plVY)
{
    // --- 1. 当たり判定（プレイヤーが上に乗っているか？） ---

    float plBottom = plY + plH; // プレイヤーの足元のY座標

    // X軸の重なりチェック
    // 「プレイヤーの左端 < 床の右端」 かつ 「プレイヤーの右端 > 床の左端」
    bool xOverlap = (plX < x + width) && (plX + plW > x);

    // Y軸の接触チェック
    // プレイヤーの足元と、床の上端(y)との距離が近いか（10.0fは許容範囲）
    // かつ、プレイヤーが落下中(plVY >= 0)であること
    bool yContact = (std::abs(plBottom - y) <= 10.0f) && (plVY >= 0);

    // --- 2. 乗っている場合の処理 ---
    if (xOverlap && yContact)
    {
        // A. 床を上昇させる
        y -= moveSpeed;

        // B. プレイヤーも一緒に上昇させる（重要）
        // プレイヤーの足元(plBottom)を、床の新しいY位置(y)にぴったり合わせる
        // これにより、置いてけぼりにならず、めり込みも防げます
        plY = y - plH;

        // C. プレイヤーの落下速度を0にする（着地状態にする）
        plVY = 0.0f;
    }
}

void SuiUGOKU::Draw()
{
    // アニメーション制御
    timer++;
    if (timer % 10 == 0) {
        frame++;
        if (frame >= 2) {
            frame = 0;
        }
    }

    // 描画
    // 画像の中心を基準に回転描画する場合、座標を調整
    // widthが64なら、中心は+32
    DrawRotaGraph(x + 32, y + 32, 0.2, 0.0, suiGraphs[frame], TRUE, FALSE);

    // デバッグ用：当たり判定の枠を表示（動作確認用）
    // DrawBox((int)x, (int)y, (int)(x + width), (int)(y + height), GetColor(255, 0, 0), FALSE);
}

// プレイヤーの下判定用
int SuiUGOKU::HitCheckDown(int px, int py) {
    if (px < static_cast<int>(x) || px >= static_cast<int>(x) + size) return 0;

    int push = py - static_cast<int>(y);
    if (push >= 0 && push < 16) {
        return push;
    }
    return 0;
}