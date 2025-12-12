#include <DxLib.h>
#include "NyokiTrap3.h"
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
NyokiTrap3::NyokiTrap3(int sx, int sy)
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
NyokiTrap3::~NyokiTrap3()
{
	DeleteGraph(hImage);
}

//--------------------------------------
// Reset
//--------------------------------------
void NyokiTrap3::Reset()
{
	x = resetx;
	y = resety;

	width = 64;
	height = 64;

	offsetY = 0.0f;    // 最初は埋まっている（0）
	isActive = false;
	isExtended = false;
	moveSpeed = 10.0f; // 上昇スピード
}

//--------------------------------------
// Update
//--------------------------------------
void NyokiTrap3::Update()
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
	// トラップ発動判定（プレイヤーが上に乗ったら）
	//----------------------------------
	if (!isActive && !isExtended)
	{
		// プレイヤーの左右(X)が、トラップの幅(X)と重なっているかチェック
		// triggerLeft, triggerRight はトラップの幅そのもの
		float triggerLeft = x;
		float triggerRight = x + width;
		bool inX = (px < triggerRight) && (px + pw > triggerLeft);

		// プレイヤーの足元(Y)が、トラップの上部(Y)に乗っているかチェック
		// 少し猶予を持たせて、トラップの上空32px〜トラップの底辺までを感知エリアとします
		float triggerTop = y - 32.0f;
		float triggerBottom = y + height;
		bool inY = (py + ph > triggerTop) && (py < triggerBottom); // 足元で判定

		if (inX && inY)
		{
			Activate();
		}
	}

	//----------------------------------
	// トラップ上昇アニメーション（上へ移動）
	//----------------------------------
	if (isActive && !isExtended)
	{
		offsetY += moveSpeed; // 突き出す量を増やす

		if (offsetY >= (float)height) // 64ドット出きったら停止
		{
			offsetY = (float)height;
			isActive = false;
			isExtended = true;
		}
	}

	//--------------------------------------
	// ▼▼▼ 三角形コライダー更新（上向き） ▼▼▼
	//--------------------------------------
	colliderPoints.resize(3);

	// 中心の計算：基準位置(y+32) から offsetY 分だけ「上（マイナス）」へ
	float centerX = x + 32;
	float centerY = (y + 32) - offsetY;

	// 上向きの三角形を作る（画像通り）
	// 中心(centerX, centerY)から見て、上・左下・右下の座標
	colliderPoints[0] = VECTOR2(centerX, centerY - 32);      // 頂点：上 (先端)
	colliderPoints[1] = VECTOR2(centerX - 32, centerY + 32); // 底辺：左下
	colliderPoints[2] = VECTOR2(centerX + 32, centerY + 32); // 底辺：右下


	//--------------------------------------
	// ▼▼▼ 当たり判定処理 ▼▼▼
	//--------------------------------------
	if (isExtended || isActive) // 針が出ている間
	{
		// プレイヤーの四隅 vs 針の三角形
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

			// 針の先端座標（上端）
			float tipX = centerX;
			float tipY = centerY - 32;

			float dx = playerX - tipX;
			float dy = playerY - tipY;

			float length = std::sqrt(dx * dx + dy * dy);
			if (length == 0.0f) {
				length = 1.0f;
				dx = 0.0f;
				dy = -1.0f; // 重なっていたら真上へ
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
void NyokiTrap3::Activate()
{
	isActive = true;
}

//--------------------------------------
// Draw
//--------------------------------------
void NyokiTrap3::Draw()
{
	// 描画位置の計算
	// Y座標を offsetY 分だけ上にずらす
	float drawX = x + 32;
	float drawY = (y + 32) - offsetY;

	// 回転なし（0.0）で描画
	DrawRotaGraph(
		(int)drawX,
		(int)drawY,
		1.0,    // 拡大率
		0.0,    // 角度（上向きなので回転なし）
		hImage,
		TRUE
	);

	// デバッグ表示（必要なら）
	// DrawFormatString((int)x, (int)y, GetColor(255,0,0), "UP");
}