#include <DxLib.h>
#include "NyokiTrap.h"
#include "Player.h"
#include "StageNumber.h"
#include <cmath> // 平方根を呼び出すやつ
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
	x = sx;
	y = sy;
	width = 64;
	height = 64;

	offsetY = 0.0f;
	isActive = false;
	isExtended = false;
	moveSpeed = 10.0f; // 上にせり出すスピード
}

//--------------------------------------
// デストラクタ
//--------------------------------------
NyokiTrap::~NyokiTrap()
{
	DeleteGraph(hImage);
}

//--------------------------------------
// 円と線分の当たり判定
//--------------------------------------
bool HitCheck_Circle_Line(VECTOR center, float radius, VECTOR a, VECTOR b)
{
	VECTOR ab = VSub(b, a);
	VECTOR ac = VSub(center, a);

	float abLen2 = ab.x * ab.x + ab.y * ab.y;
	if (abLen2 <= 0.0f) return false; // 同一点保険

	float t = (ab.x * ac.x + ab.y * ac.y) / abLen2;
	if (t < 0.0f) t = 0.0f;
	if (t > 1.0f) t = 1.0f;

	VECTOR closest = VAdd(a, VScale(ab, t));

	float dx = center.x - closest.x;
	float dy = center.y - closest.y;

	return (dx * dx + dy * dy <= radius * radius);
}

//--------------------------------------
// 点が三角形の中かどうか
//--------------------------------------
bool PointInTriangle(VECTOR p, VECTOR a, VECTOR b, VECTOR c)
{
	VECTOR v0 = VSub(c, a);
	VECTOR v1 = VSub(b, a);
	VECTOR v2 = VSub(p, a);

	float dot00 = VDot(v0, v0);
	float dot01 = VDot(v0, v1);
	float dot02 = VDot(v0, v2);
	float dot11 = VDot(v1, v1);
	float dot12 = VDot(v1, v2);

	float denom = (dot00 * dot11 - dot01 * dot01);
	if (denom == 0.0f) return false; // 退化三角形保険

	float invDenom = 1.0f / denom;
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return (u >= 0) && (v >= 0) && (u + v < 1);
}

//--------------------------------------
// 円と三角形の当たり判定
//--------------------------------------
bool HitCheck_Circle_Triangle(
	VECTOR center, float radius,
	VECTOR t1, VECTOR t2, VECTOR t3)
{
	// 円と三辺
	if (HitCheck_Circle_Line(center, radius, t1, t2)) return true;
	if (HitCheck_Circle_Line(center, radius, t2, t3)) return true;
	if (HitCheck_Circle_Line(center, radius, t3, t1)) return true;

	// 円の中心が三角形内部にある場合
	if (PointInTriangle(center, t1, t2, t3)) return true;

	return false;
}

//--------------------------------------
// Update
//--------------------------------------
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
	// プレイヤーが「上のブロック」を踏んだら発動
	//----------------------------------
	if (!isActive && !isExtended)
	{
		float triggerTop = y - height;
		float triggerBottom = y;
		float playerFootY = py + ph;

		bool inX = (px + pw > x) && (px < x + width);
		bool inY = (playerFootY > triggerTop) && (playerFootY <= triggerBottom);

		if (inX && inY)
		{
			Activate();
		}
	}

	//----------------------------------
	// トラップ上昇アニメーション
	//----------------------------------
	if (isActive && !isExtended)
	{
		offsetY += moveSpeed;
		if (offsetY >= height)
		{
			offsetY = (float)height;
			isActive = false;
			isExtended = true;
		}
	}

	//--------------------------------------
	// ▼▼▼ 三角形コライダー更新 ▼▼▼
	//--------------------------------------
	colliderPoints.resize(3);
	float tipX = x + 32;             // 針の中心
	float tipY = y - offsetY;        // 上にせり上がる

	colliderPoints[0] = VECTOR2(tipX, tipY - 32); // 上の頂点
	colliderPoints[1] = VECTOR2(tipX - 32, tipY + 32); // 左下
	colliderPoints[2] = VECTOR2(tipX + 32, tipY + 32); // 右下

	//--------------------------------------
	// ▼▼▼ 三角形の当たり判定（完全に trap と同じ）▼▼▼
	//--------------------------------------
	if (isExtended) // 針が出ている間だけ判定
	{
		if (!hittest_point_polygon_2d(
			colliderPoints[0], colliderPoints[1], colliderPoints[2],
			player->GetColliderLeftTop()) ||

			!hittest_point_polygon_2d(
				colliderPoints[0], colliderPoints[1], colliderPoints[2],
				player->GetColliderLeftBottom()) ||

			!hittest_point_polygon_2d(
				colliderPoints[0], colliderPoints[1], colliderPoints[2],
				player->GetColliderRightTop()) ||

			!hittest_point_polygon_2d(
				colliderPoints[0], colliderPoints[1], colliderPoints[2],
				player->GetColliderRightBottom()))
		{
			//----------------------------------
			// ヒット時の吹っ飛び処理（trap と同じ）
			//----------------------------------
			float playerX = player->GetX();
			float playerY = player->GetY();

			float dx = playerX - (x + 32);
			float dy = playerY - (y + 32 - offsetY);

			float length = std::sqrt(dx * dx + dy * dy);
			if (length == 0.0f) {
				length = 1.0f;
				dx = 1.0f;
				dy = 0.0f;
			}

			unitX = dx / length;
			unitY = dy / length;

			StageNumber* stageNumber = FindGameObject<StageNumber>();
			if (stageNumber->noDeath != true)
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
	// offsetY 分だけ上に描画
	DrawRectGraph(
		static_cast<int>(x),
		static_cast<int>(y - offsetY),
		0, 0, width, height,
		hImage,
		TRUE
	);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "針 = %.2f", y);
}

//--------------------------------------
// 旧AABB判定（今は使っていなければ不要）
//--------------------------------------
bool NyokiTrap::CheckHit(int px, int py, int pw, int ph)
{
	return (px + pw > x && px < x + width &&
		py + ph > y - offsetY && py < y + height);
}