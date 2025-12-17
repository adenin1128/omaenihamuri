#pragma once
#include "../Library/GameObject.h"

// クラスの前方宣言
class Player;

// ★変更点：名前が被らないように SUI_ をつけました
enum SuiUGOKUState {
    SUI_STATE_A,    // 30 -> 31
    SUI_STATE_B,    // 31 -> 32
    SUI_STATE_C,    // 32 -> 33
    SUI_STATE_D     // 33 -> 31
};

class SuiUGOKU : public GameObject {
public:
    SuiUGOKU(int px, int py);
    ~SuiUGOKU();

    void Update() override;
    void Draw() override;
    void Reset();

    // プレイヤーの下判定用
    int HitCheckDown(int px, int py);

    // 状態の取得・設定
    SuiUGOKUState GetState() const { return state; }
    void SetState(SuiUGOKUState s) { state = s; }

private:
    int frame;
    int timer;

    // 座標・描画
    int resetX, resetY;
    float x, y;
    int sImage;
    int size;

    // 速度
    float moveSpeed;

    // 状態
    SuiUGOKUState state;
    bool activatedA;

    static constexpr int PLATFORM_W = 64;
    static constexpr int PLATFORM_H = 16;

    bool IsPlayerOn(const Player* p) const;
    void MoveOneStep(float moveX, float moveY, Player* p);
};