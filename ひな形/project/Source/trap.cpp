#include "trap.h"
#include "field.h"
#include "Player.h"
#include "Gameover.h"
#include <cmath> // 平方根を呼び出すやつ
#define _USE_MATH_DEFINES
#include <math.h>

// 当たり判定ライブラリ
#include "Collider.h"
using namespace ColliderLibrary;

const float BOOM_FORCE = 200.0f; // 吹っ飛びの勢い

VECTOR2 RotatePoint(VECTOR2 vec, double rot)
{
    // 中心を基準に座標を回転
    double dx = vec.x - 32;
    double dy = vec.y - 32;

    double newX = dx * std::cos(rot) - dy * std::sin(rot);
    double newY = dx * std::sin(rot) + dy * std::cos(rot);

    return VECTOR2(newX + 32, newY + 32);
}

trap::trap(int px, int py, int i, int d, int tx, int ty)
{
    dir = (Direction)d;
    hariImage = LoadGraph("data/image/hari.png");
    x = px;
    y = py;

    vx = tx;
	vy = ty;


    isActive = false;
    isGameover = false;
    // 上向きの三角形の頂点座標を設定
    colliderPoints.resize(3);
    colliderPoints[0] = VECTOR2(32, 0);          // 頂点
    colliderPoints[1] = VECTOR2(0, 64);          // ポイント２
    colliderPoints[2] = VECTOR2(64, 64);     // ポイント３

    // 向きに応じて頂点座標を回転・移動
    rot = 3.14 / 2 * dir; // 向きに応じた回転角 
    colliderPoints[0] = VECTOR2(x, y) + RotatePoint(VECTOR2(32, 0), rot);
    colliderPoints[1] = VECTOR2(x, y) + RotatePoint(VECTOR2(0, 64), rot);
    colliderPoints[2] = VECTOR2(x, y) + RotatePoint(VECTOR2(64, 64), rot);
}

trap::~trap()
{
}

void trap::Update()
{
    colliderPoints[0] = VECTOR2(x, y) + RotatePoint(VECTOR2(32, 0), rot);
    colliderPoints[1] = VECTOR2(x, y) + RotatePoint(VECTOR2(0, 64), rot);
    colliderPoints[2] = VECTOR2(x, y) + RotatePoint(VECTOR2(64, 64), rot);
    Player* player = FindGameObject<Player>();

    // プレイヤーが撃墜中かゲームオーバーなら処理しない
    if (player->GetState() != STATE_NORMAL) {

        if (isActive) {
            x += vx;
			y += vy;
        }
        return;
    }


    // 当たり判定
    if (!hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderLeftTop()) ||
        !hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderLeftBottom()) ||
        !hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderRightTop()) ||
        !hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderRightBottom()))
    {
        //SetFontSize(32); DrawString(100, 100, "Hit!", GetColor(255, 0, 0)); //debug用(機能しない)

       //ゲームオーバー処理の代わりに撃墜処理を呼び出す

       // 1. 撃墜ベクトルの計算
        float playerX = player->GetX();
        float playerY = player->GetY();

        float dx = playerX - (x + 32); // プレイヤー中心 - トラップ中心
        float dy = playerY - (y + 32);

        float length = std::sqrt(dx * dx + dy * dy);

        if (length == 0.0f) {
            length = 1.0f;
            dx = 1.0f; dy = 0.0f; // 例外処理
        }

        float unitX = dx / length;
        float unitY = dy / length;

        // 2. プレイヤーに初速を設定し、状態をSTATE_BOOMにする
        player->SetBOOM(unitX * BOOM_FORCE, unitY * BOOM_FORCE);
    }

    if (isActive) {
		x += vx;
		y += vy;
        }
}
void trap::Active() {
    isActive = true;
}
void trap::Draw()
{
    for (auto point : colliderPoints) {
        DrawCircle((int)point.x, (int)point.y, 3, GetColor(255, 0, 0), true);
    }

    DrawRotaGraph(x + 32, y + 32, 1, rot, hariImage, true);
    //DrawRotaGraph(x + 32, y + 32, 1.0, M_PI, hariImage, true, false);
}
