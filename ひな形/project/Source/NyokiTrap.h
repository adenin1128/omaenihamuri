#pragma once
#include "../Library/GameObject.h"

class NyokiTrap : public GameObject
{
public:
	NyokiTrap(int x, int y);
	~NyokiTrap();
	void Update() override;
	void Draw() override;

	// --- 衝突判定用 ---
	bool CheckHit(int px, int py, int pw, int ph); // プレイヤー矩形と当たっているか？

private:
	int hImage;    // 針の画像ハンドル
	float x, y;    // 座標
	int width;     // 幅（画像サイズ）
	int height;    // 高さ

	// --- 動き制御用 ---
	float offsetY;     // にょきっと出る量（0〜64）
	bool isActive;     // 発動中かどうか
	bool isExtended;   // 出きった状態
	float moveSpeed;   // 上昇スピード

	void Activate();   // プレイヤーが踏んだときに発動

};
