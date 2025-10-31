#pragma once
#include "../Library/GameObject.h"

enum PlayerState {
	STATE_NORMAL,    // 通常時
	STATE_BOOM, // 撃墜中
	STATE_GAMEOVER   // 画面外に出てゲームオーバー
};

class Player : public GameObject
{
public:
	Player();
	Player(float startX, float startY);
	~Player();
	void Update() override;
	void Draw() override;
	int PlayerHP;
	VECTOR2 GetPosition() { return VECTOR2(x, y); }
	VECTOR2 GetColliderLeftTop() { return VECTOR2(x + colliderOffset, y + colliderOffset); }
	VECTOR2 GetColliderLeftBottom() { return VECTOR2(x + colliderOffset, y + CHARACTER_HEIGHT - colliderOffset); }
	VECTOR2 GetColliderRightTop() { return VECTOR2(x + CHARACTER_WIDTH - colliderOffset, y + colliderOffset); }
	VECTOR2 GetColliderRightBottom() { return VECTOR2(x + CHARACTER_WIDTH - colliderOffset, y + CHARACTER_HEIGHT - colliderOffset); }
	float velX;          // X方向の速度 (BOOM用)
	float velY;          // Y方向の速度 (BOOM用)
	float rot;           // 回転角度 (BOOMのプレイヤーぐるぐる用)
	PlayerState state;   // プレイヤーの状態管理
	float GetX() const { return x; }
	float GetY() const { return y; }
	// 速度と状態を設定する
	void SetBOOM(float vx, float vy) {
		velX = vx;
		velY = vy;
		rot = 0.0f; // 初期回転をリセット
		state = STATE_BOOM;
	}
	PlayerState GetState() const { return state; }
	void SetState(PlayerState s) { state = s; }
	// Player.h の public: セクションに仮定で追加
	bool IsBOOM() const { return state == STATE_BOOM; }

private:

	static const int CHARACTER_WIDTH = 64;
	static const int CHARACTER_HEIGHT = 64;
	static const int ATLAS_WIDTH = 12;
	static const int ATLAS_HEIGHT = 1;
	static const int BOOM_CHARACTER_WIDTH = 64;
	static const int BOOM_CHARACTER_HEIGHT = 64;
	static const int BOOM_ATLAS_WIDTH = 36;
	static const int BOOM_ATLAS_HEIGHT = 1;
	static const int BOOM_ANIM_FRAME_COUNT = 36;
	static const int BOOM_ANIM_FRAME_INTERVAL = 4;
	static const int ANIM_FRAME_COUNT = 12;
	static const int ANIM_FRAME_INTERVAL = 4;   //  アニメーション間隔(frame)
	static const int WALK_SPEED = 4;            //  移動速度(dot/frame)

	int animImage;      //  アニメーション用画像ハンドル
	int animIndex;      //  どこのコマを表示するか
	int animFrame;      //  アニメーション間隔
	int xPosition;      //  キャラクターのX座標
	bool direction;		//  キャラクターの向き(true:左向き/false:右向き)
	int BOOMImage;      //  撃墜用画像ハンドル
	int boomAnimIndex;  //  撃墜アニメーションのコマ
	int boomFrame;      //  撃墜アニメーション間隔


	int hImage;
	int posX;
	int posY;
	float x, y;
	float velocity;
	bool onGround;
	int jumpcount;
	int Maxjumpcount;

	int colliderOffset = 8;
};





