#include"downtrap.h"
#include "trap.h"
#include "field.h"
#include "Player.h"
#include "Gameover.h"
#include <cmath>
// 当たり判定ライブラリ
#include "Collider.h"
using namespace ColliderLibrary;

const float BOOM_FORCE = 200.0f; // 吹っ飛びの勢い

downtrap::downtrap(int px, int py, int i)
{
    type = (MoveType)i;
    harisitaImage = LoadGraph("data/image/hari.png");
    x = px;
    y = py;
    UP = -5.0f;
    isActive = false;
    isGameover = false;

    dir = Right; // 向き

	// 上向きの三角形の頂点座標を設定
	colliderPoints.resize(3);
	colliderPoints[0] = VECTOR2(32,  0);          // 頂点
	colliderPoints[1] = VECTOR2( 0, 64);          // ポイント２
	colliderPoints[2] = VECTOR2(64, 64);     // ポイント３

	//// 向きに応じて頂点座標を回転・移動
	//rot = 3.14 / 2 * dir; // 向きに応じた回転角 
	//VECTOR2 center(32, 32); // 回転の中心点（トラップの中心）
 //   colliderPoints[0] = VECTOR2(x, y) + RotatePoint(colliderPoints[0], rot, center);
 //   colliderPoints[1] = VECTOR2(x, y) + RotatePoint(colliderPoints[1], rot, center);
 //   colliderPoints[2] = VECTOR2(x, y) + RotatePoint(colliderPoints[2], rot, center);
}



downtrap::~downtrap()
{
}

void downtrap::Update()
{
    Player* player = FindGameObject<Player>();

    // プレイヤーが撃墜中かゲームオーバーなら処理しない
    if (player->GetState() != STATE_NORMAL) {

        if (isActive) {
            switch (type) {
            case Down: y -= UP; break;
            }
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

        // お試しでnew GameOver()を呼ばない
        if (player->GetState() == STATE_BOOM) {
            SetFontSize(32);
            DrawString(200, 70, "BOOM ok", GetColor(255, 255, 0));
        }
    }

    if (isActive == true) {
        switch (type) {
        case Down:
            y -= UP;
            break;

        }
    }
}

void downtrap::Active()
{
    isActive = true;
}

void downtrap::Draw()
{
    for(auto point : colliderPoints) {
        DrawCircle((int)point.x, (int)point.y, 3, GetColor(255, 0, 0), true);
	}

    DrawRotaGraph(x + 32, y + 32, 1, rot, harisitaImage, true);
    //DrawRotaGraph(x + 32, y + 32, 1.0, M_PI, hariImage, true, false);
    if (isGameover) {
        SetFontSize(64);
        DrawFormatString(x - 100, y - 100, GetColor(255, 0, 0), "ゲームオーバー");
    }
    Player* player = FindGameObject<Player>();
    if (player && player->IsBOOM()) { // IsBOOM() は Player.h で定義されているとして
        SetFontSize(32);
        DrawString(10, 50, "BOOM ACTIVE!", GetColor(255, 255, 0));
    }
}

