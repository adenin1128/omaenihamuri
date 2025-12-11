#include <DxLib.h>
#include "NyokiTrap.h"
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
NyokiTrap::NyokiTrap(int sx, int sy)
{
	hImage = LoadGraph("data/image/hari.png"); // 針画像
	resetx = sx;
	resety = sy;

	Reset();

	SetDrawOrder(1000);
}

//--------------------------------------
// デストラクタ
//--------------------------------------
NyokiTrap::~NyokiTrap()
{
	DeleteGraph(hImage);
}

void NyokiTrap::Reset()
{
	x = resetx;
	y = resety;

	width = 64;
	height = 64;

	offsetX = 0.0f; // ★変更：YではなくXのオフセットを使います
	isActive = false;
	isExtended = false;
	moveSpeed = 10.0f; // ★横にせり出すスピード
}

// （※ここに HitCheck_Circle_Line などの判定関数がある想定ですが省略します。元のままで大丈夫です）

//--------------------------------------
// Update
//--------------------------------------
void NyokiTrap::Update()
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
	// ★変更：プレイヤーが「右横」に来たら発動
	//----------------------------------
	if (!isActive && !isExtended)
	{
		// プレイヤーの高さ(Y)が、トラップの高さ(Y)と重なっているかチェック
		bool inY = (py + ph > y) && (py < y + height);

		// プレイヤーの横位置(X)が、トラップの右側（反応エリア）にいるかチェック
		// x + width はトラップの右端。そこから少し先までを反応エリアとします
		float triggerLeft = x + width;
		float triggerRight = x + width + 32.0f; // 32ピクセル手前まで近づいたら反応
		bool inX = (px < triggerRight) && (px + pw > triggerLeft);

		if (inX && inY)
		{
			Activate();
		}
	}

	//----------------------------------
	// ★変更：トラップ横移動アニメーション
	//----------------------------------
	if (isActive && !isExtended)
	{
		offsetX += moveSpeed; // 右へ移動
		if (offsetX >= width) // 64ドット出きったら停止
		{
			offsetX = (float)width;
			isActive = false;
			isExtended = true;
		}
	}

	//--------------------------------------
	// ▼▼▼ 三角形コライダー更新（右向き） ▼▼▼
	//--------------------------------------
	colliderPoints.resize(3);

	// 針の画像の中心座標を計算（元の位置 + オフセット）
	float centerX = x + 32 + offsetX;
	float centerY = y + 32;

	// 右向きの三角形を作る
	// data/image/hari.png が「上向き」の画像だと仮定して計算しています

	colliderPoints[0] = VECTOR2(centerX + 32, centerY);      // 頂点：右の先端
	colliderPoints[1] = VECTOR2(centerX - 32, centerY - 32); // 底辺：左上
	colliderPoints[2] = VECTOR2(centerX - 32, centerY + 32); // 底辺：左下

	//--------------------------------------
	// ▼▼▼ 三角形の当たり判定 ▼▼▼
	//--------------------------------------
	if (isExtended) // 針が出ている間だけ判定
	{
		// プレイヤーの四隅と、針の三角形の判定
		if (!hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderLeftTop()) ||
			!hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderLeftBottom()) ||
			!hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderRightTop()) ||
			!hittest_point_polygon_2d(colliderPoints[0], colliderPoints[1], colliderPoints[2], player->GetColliderRightBottom()))
		{
			//----------------------------------
			// ヒット時の吹っ飛び処理
			//----------------------------------
			float playerX = player->GetX();
			float playerY = player->GetY();

			// 吹っ飛ぶ方向の計算（針の先端からプレイヤーへのベクトル）
			// 先端座標 (x + 32 + offsetX, y + 32)
			float tipX = x + 32 + offsetX;
			float tipY = y + 32;

			float dx = playerX - tipX;
			float dy = playerY - tipY;

			float length = std::sqrt(dx * dx + dy * dy);
			if (length == 0.0f) {
				length = 1.0f;
				dx = 1.0f; // 重なっていたら右へ
				dy = 0.0f;
			}

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
void NyokiTrap::Activate()
{
	isActive = true;
}

//--------------------------------------
// Draw
//--------------------------------------
void NyokiTrap::Draw()
{
	// ★変更：回転させて描画するために DrawRotaGraph を使用します
	// 元画像が「上向き」の針の場合、右に向けるには +90度（PI / 2）回転させます

	// 描画する中心座標 (offsetX分だけ右にずらす)
	// ※元のx,yは左上座標なので、中心は +32 する
	float drawX = x + 32 + offsetX;
	float drawY = y + 32;

	DrawRotaGraph(
		(int)drawX,
		(int)drawY,
		1.0,           // 拡大率
		M_PI / 2.0,    // 角度（ラジアン）。90度回転で右向き
		hImage,
		TRUE
	);

	// デバッグ用表示（必要なければ消してください）
	// DrawFormatString(0, 300, GetColor(255, 255, 255), "針X = %.2f", drawX);
}