#include <DxLib.h>
#include "NyokiTrap4.h"
#include "Player.h"
#include "StageNumber.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

// 当たり判定ライブラリ
#include "Collider.h"
using namespace ColliderLibrary;

const float BOOM_FORCE = 200.0f; // 吹っ飛びの勢い

//--------------------------------------
// コンストラクタ
//--------------------------------------
NyokiTrap4::NyokiTrap4(int sx, int sy)
{
	hImage = LoadGraph("data/image/hari.png"); // 針画像
	resetx = (float)sx;
	resety = (float)sy;

	Reset();

	SetDrawOrder(1000);
}

//--------------------------------------
// デストラクタ
//--------------------------------------
NyokiTrap4::~NyokiTrap4()
{
	DeleteGraph(hImage);
}

//--------------------------------------
// Reset
//--------------------------------------
void NyokiTrap4::Reset()
{
	x = resetx;
	y = resety;

	width = 64;
	height = 64;

	offsetY = 0.0f;    // 最初は天井に埋まっている（0）
	isActive = false;
	isExtended = false;
	moveSpeed = 10.0f; // 下降スピード
}

//--------------------------------------
// Update
//--------------------------------------
void NyokiTrap4::Update()
{
	Player* player = FindGameObject<Player>();
	if (player == nullptr) {
		return;
	}

	float px = player->GetX();
	float py = player->GetY();
	float pw = 64.0f;
	float ph = 64.0f;

	//----------------------------------
	// トラップ発動判定（プレイヤーが下に来たら）
	//----------------------------------
	if (!isActive && !isExtended)
	{
		// プレイヤーの左右(X)が、トラップの幅(X)と重なっているかチェック
		float triggerLeft = x;
		float triggerRight = x + width;
		bool inX = (px < triggerRight) && (px + pw > triggerLeft);

		// プレイヤーの頭上(Y)が、トラップの下(Y)にあるかチェック
		// トラップの位置(y)から、下方向(y + height + 32)くらいまでを感知エリアとします
		float triggerTop = y;
		float triggerBottom = y + height + 32.0f;

		// プレイヤーの上辺(py)がエリア内か、またはプレイヤーの下辺(py+ph)がエリア内か
		bool inY = (py < triggerBottom) && (py + ph > triggerTop);

		if (inX && inY)
		{
			Activate();
		}
	}

	//----------------------------------
	// トラップ下降アニメーション（下へ移動）
	//----------------------------------
	if (isActive && !isExtended)
	{
		offsetY += moveSpeed; // 突き出す量を増やす（下へ）

		if (offsetY >= (float)height) // 64ドット出きったら停止
		{
			offsetY = (float)height;
			isActive = false;
			isExtended = true;
		}
	}

	//--------------------------------------
	// ▼▼▼ 三角形コライダー更新（下向き） ▼▼▼
	//--------------------------------------
	colliderPoints.resize(3);

	// 中心の計算：基準位置(y+32) から offsetY 分だけ「下（プラス）」へ
	float centerX = x + 32;
	float centerY = (y + 32) + offsetY;

	// 【変更点】下向きの三角形を作る（逆三角形）
	// 中心(centerX, centerY)から見て、下・左上・右上
	colliderPoints[0] = VECTOR2(centerX, centerY + 32);      // 頂点：下 (先端)
	colliderPoints[1] = VECTOR2(centerX - 32, centerY - 32); // 底辺：左上
	colliderPoints[2] = VECTOR2(centerX + 32, centerY - 32); // 底辺：右上


	//--------------------------------------
	// ▼▼▼ 当たり判定処理 ▼▼▼
	//--------------------------------------
	if (isExtended || isActive) // 針が出ている間
	{
		bool hit =
			hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderLeftTop()) ||
			hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderLeftBottom()) ||
			hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderRightTop()) ||
			hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderRightBottom());

		if (hit)
		{
			//----------------------------------
			// ヒット時の吹っ飛び処理
			//----------------------------------
			float playerX = player->GetX();
			float playerY = player->GetY();

			// 針の先端座標（下端）
			float tipX = centerX;
			float tipY = centerY + 32;

			float dx = playerX - tipX;
			float dy = playerY - tipY;

			float length = std::sqrt(dx * dx + dy * dy);
			if (length == 0.0f) {
				length = 1.0f;
				dx = 0.0f;
				dy = 1.0f; // 重なっていたら真下へ
			}

			// 正規化
			unitX = dx / length;
			unitY = dy / length;

			StageNumber* stageNumber = FindGameObject<StageNumber>();
			if (stageNumber != nullptr && stageNumber->noDeath != true)
			{
				player->SetBOOM(unitX * BOOM_FORCE, unitY * BOOM_FORCE);
			}
		}
	}
}

//--------------------------------------
// Activate
//--------------------------------------
void NyokiTrap4::Activate()
{
	isActive = true;
}

//--------------------------------------
// Draw
//--------------------------------------
void NyokiTrap4::Draw()
{
	// 描画位置の計算
	// Y座標を offsetY 分だけ下にずらす
	float drawX = x + 32;
	float drawY = (y + 32) + offsetY;

	// 【変更点】180度回転（PI）で下向き
	DrawRotaGraph(
		(int)drawX,
		(int)drawY,
		1.0,    // 拡大率
		M_PI,   // 角度（180度回転）
		hImage,
		TRUE
	);

	// デバッグ表示
	// DrawFormatString((int)x, (int)y, GetColor(255,0,0), "DOWN");
}