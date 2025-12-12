#pragma once
#include "../Library/GameObject.h"
#include <vector>

class NyokiTrap3 : public GameObject
{
public:
	NyokiTrap3(int x, int y);
	~NyokiTrap3();
	void Update() override;
	void Draw() override;
	void Reset();

	// --- 衝突判定用 ---
	bool CheckHit(int px, int py, int pw, int ph);

private:
	int   hImage;    // 針の画像ハンドル
	float x, y;      // 座標（針が生える床の位置）
	int   width;     // 幅
	int   height;    // 高さ
	float unitX;
	float unitY;
	float resetx, resety;

	// --- 動き制御用 ---
	float moveSpeed;   // 上昇スピード
	float offsetY;     // ニョキっと出る量（0〜64）
	float offsetX;     // (今回は使いません)
	bool  isActive;    // 発動中
	bool  isExtended;  // 出きった状態

	void Activate();   // 発動処理
	std::vector<VECTOR2> colliderPoints;
};