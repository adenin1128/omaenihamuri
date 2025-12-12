#pragma once
#include "../Library/GameObject.h"
#include <vector>

class NyokiTrap2 : public GameObject
{
public:
	NyokiTrap2(int x, int y);
	~NyokiTrap2();
	void Update() override;
	void Draw() override;
	void Reset();

	// --- 衝突判定用 ---
	bool CheckHit(int px, int py, int pw, int ph);

private:
	int   hImage;    // 針の画像ハンドル
	float x, y;      // 座標（針が生える土台の左上位置）
	int   width;     // 幅
	int   height;    // 高さ
	float unitX;
	float unitY;
	float resetx, resety;

	// --- 動き制御用 ---
	float moveSpeed;   // 飛び出すスピード
	float offsetY;     // (今回は使いません)
	float offsetX;     // ニョキっと出ている量（0.0f 〜 64.0f）
	bool  isActive;    // 発動中（アニメーション中）
	bool  isExtended;  // 出きった状態

	void Activate();   // 発動処理
	std::vector<VECTOR2> colliderPoints; // 当たり判定の多角形
};