#include <DxLib.h>
#include "NyokiTrap2.h"
#include "Player.h"
#include "StageNumber.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

// 当たり判定ライブラリ（環境に合わせてパスを確認してください）
#include "Collider.h"
using namespace ColliderLibrary;

const float BOOM_FORCE = 200.0f; // 吹っ飛びの勢い

//--------------------------------------
// コンストラクタ
//--------------------------------------
NyokiTrap2::NyokiTrap2(int sx, int sy)
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
NyokiTrap2::~NyokiTrap2()
{
	DeleteGraph(hImage);
}

//--------------------------------------
// Reset
//--------------------------------------
void NyokiTrap2::Reset()
{
	x = resetx;
	y = resety;

	width = 64;
	height = 64;

	offsetX = 0.0f;    // 最初は引っ込んでいる（0）
	isActive = false;
	isExtended = false;
	moveSpeed = 10.0f; // 飛び出すスピード
}

//--------------------------------------
// Update
//--------------------------------------
void NyokiTrap2::Update()
{
	Player* player = FindGameObject<Player>();
	if (player == nullptr) {
		return;
	}

	float px = player->GetX();
	float py = player->GetY();
	float pw = 64.0f; // プレイヤーサイズ（仮）
	float ph = 64.0f;

	//----------------------------------
	// トラップ発動判定（左側にプレイヤーが来たら）
	//----------------------------------
	if (!isActive && !isExtended)
	{
		// 高さ(Y)が合っているか
		bool inY = (py + ph > y) && (py < y + height);

		// 【変更点】トラップの「左側」にいるかチェック
		// triggerLeft 〜 triggerRight の間にプレイヤーの一部が入ったら発動
		// x はトラップ本体の左端座標。
		float triggerRight = x;         // 本体の左端
		float triggerLeft = x - 32.0f;  // そこから32px左までを感知エリアとする

		bool inX = (px < triggerRight) && (px + pw > triggerLeft);

		if (inX && inY)
		{
			Activate();
		}
	}

	//----------------------------------
	// トラップ移動アニメーション（左へせり出す）
	//----------------------------------
	if (isActive && !isExtended)
	{
		offsetX += moveSpeed; // 値自体は増やしていく

		if (offsetX >= (float)width) // 64ドット出きったら停止
		{
			offsetX = (float)width;
			isActive = false;
			isExtended = true;
		}
	}

	//--------------------------------------
	// ▼▼▼ 三角形コライダー更新（左向き） ▼▼▼
	//--------------------------------------
	colliderPoints.resize(3);

	// 【変更点】中心座標の計算
	// 左へ出すため、基準位置(x+32) から offsetX を「引く」
	float centerX = (x + 32) - offsetX;
	float centerY = y + 32;

	// 【変更点】左向きの三角形を定義
	// 画像サイズ64x64、中心が(centerX, centerY)
	// 元画像が「上向き」と仮定して、-90度回転した形状を作成
	colliderPoints[0] = VECTOR2(centerX - 32, centerY);      // 頂点：左の先端
	colliderPoints[1] = VECTOR2(centerX + 32, centerY - 32); // 底辺：右上
	colliderPoints[2] = VECTOR2(centerX + 32, centerY + 32); // 底辺：右下

	//--------------------------------------
	// ▼▼▼ 当たり判定処理 ▼▼▼
	//--------------------------------------
	if (isExtended || isActive) // 出ている間判定する
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

			// 【変更点】針の先端座標（左端）
			float tipX = centerX - 32;
			float tipY = centerY;

			// プレイヤーが針の先端から見てどの方向にいるか
			float dx = playerX - tipX;
			float dy = playerY - tipY;

			float length = std::sqrt(dx * dx + dy * dy);
			if (length == 0.0f) {
				length = 1.0f;
				dx = -1.0f; // 重なっていたら左へ
				dy = 0.0f;
			}

			// 正規化
			unitX = dx / length;
			unitY = dy / length;

			StageNumber* stageNumber = FindGameObject<StageNumber>();
			// ステージ番号管理があり、かつ「死なないモード」でなければ吹っ飛ばす
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
void NyokiTrap2::Activate()
{
	isActive = true;
}

//--------------------------------------
// Draw
//--------------------------------------
void NyokiTrap2::Draw()
{
	// 【変更点】描画位置の計算
	// 中心位置：(x + 32) から offsetX 分だけ「左（マイナス）」へずらす
	float drawX = (x + 32) - offsetX;
	float drawY = y + 32;

	// 【変更点】回転描画
	// -M_PI / 2.0  -> -90度（反時計回り）で左を向く
	DrawRotaGraph(
		(int)drawX,
		(int)drawY,
		1.0,           // 拡大率
		-M_PI / 2.0,   // 角度
		hImage,
		TRUE
	);

	// デバッグ用（必要ならコメントアウトを外してください）
	// DrawFormatString((int)x, (int)y - 20, GetColor(255,0,0), "Trap");
}