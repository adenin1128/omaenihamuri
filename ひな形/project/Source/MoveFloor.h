
#pragma once
#include "../Library/GameObject.h"

enum MoveFloorState {
    STATE_A,    // 30 -> 31（初期：乗ったら動作開始）
    STATE_B,    // 31 -> 32（自動継続）
    STATE_C,    // 32 -> 33 (31から33へ移動)
    STATE_D     // 33 -> 31（折り返し）
};

class Player; // 前方宣言

class MoveFloor : public GameObject {
public:
    MoveFloor(int px, int py);
    ~MoveFloor();
    void Update() override;
    void Draw() override;

    MoveFloorState GetState() const { return state; }
    void SetState(MoveFloorState s) { state = s; }

private:
    // 座標・描画
    float x, y;
    int   fImage;

    // 速度・区間管理
    float moveSpeed;          // px/フレーム
    float maxSegmentLength;   // 今状態の目標区間長（Fieldから取得）
    float progressed;         // 進んだ距離の累積（px）

    // 状態
    MoveFloorState state;
    bool activatedA;          // STATE_Aで「乗って動作開始した」フラグ

    // 床サイズ（当たり判定用）※画像幅・高さに合わせて調整
    static constexpr int PLATFORM_W = 64;
    static constexpr int PLATFORM_H = 16;

    // ユーティリティ
    bool IsPlayerOn(const Player* p) const;
    void MoveOneStep(float dir, Player* p); // dir: +1 右 / -1 左
};
