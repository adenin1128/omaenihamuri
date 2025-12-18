#include "MoveFloor.h"
#include "Player.h"
#include "Field.h"
#include <assert.h>
#include <cmath> // std::sqrt, std::fabs

int suiGraphs[2];

MoveFloor::MoveFloor(int px, int py)
{
    fImage = LoadGraph("data/image/すい.png");
    LoadDivGraph("data/image/すい.png", 2, 2, 1, 640, 640, suiGraphs);
    assert(fImage > 0);

    resetX = px;
    resetY = py;

    Reset();
}

MoveFloor::~MoveFloor()
{
}

void MoveFloor::Reset()
{
    x = static_cast<float>(resetX);
    y = static_cast<float>(resetY);

    moveSpeed = 3.0f;

    state = STATE_A;
    activatedA = false;

    frame = 0;
    timer = 0;
    size = 64;
}

bool MoveFloor::IsPlayerOn(const Player* p) const
{
    if (!p) return false;

    const float px = p->GetX();
    const float py = p->GetY();
    const float pw = static_cast<float>(p->GetWidth());
    const float ph = static_cast<float>(p->GetHeight());

    // プレイヤー底面が床天面付近にあり、Xが重なっている
    const float playerBottom = py + ph;

    // X軸の重なりチェック（床の幅分）
    const bool xOverlap = (px < x + size) && (px + pw > x);

    // Y軸の接地チェック（少し余裕を持たせる）
    const bool onTop = std::fabs(playerBottom - y) <= 8.0f;

    return xOverlap && onTop;
}

//---------------------------------------------------------
// ★移動処理：XとYの両方を受け取って動かす
//---------------------------------------------------------
void MoveFloor::MoveOneStep(float moveX, float moveY, Player* p)
{
    // 床移動
    x += moveX;
    y += moveY;

    // 乗っていればプレイヤーも一緒に動かす
    if (p && IsPlayerOn(p)) {
        p->SetX(p->GetX() + moveX);
        p->SetY(p->GetY() + moveY);
    }
}

//---------------------------------------------------------
// Update
//---------------------------------------------------------
void MoveFloor::Update()
{
    Field* field = FindGameObject<Field>();
    Player* player = FindGameObject<Player>();
    if (!field) return;

    // ----------------------------------------------------
    // ★追加: プレイヤーが乗っていないときは動きを止める
    // ----------------------------------------------------
    if (!IsPlayerOn(player)) {
        return; // ここで関数を抜けるため、下の移動処理が実行されません
    }

    // ----------------------------------------------------
    // 目指すべきブロックの番号(ID)を決める
    // ----------------------------------------------------
    int targetBlockID = -1;

    switch (state) {
    case STATE_A: targetBlockID = 31; break; // 30地点から31へ向かう
    case STATE_B: targetBlockID = 32; break; // 31地点から32へ向かう
    case STATE_C: targetBlockID = 33; break; // 32地点から33へ向かう
    case STATE_D: targetBlockID = 31; break; // 33地点から31へ戻る
    default: break;
    }

    // ----------------------------------------------------
    // Fieldから目標地点の座標(targetX, targetY)を取得
    // ----------------------------------------------------
    int tx = 0, ty = 0;
    if (field->GetPointPos(targetBlockID, &tx, &ty) == false) {
        return;
    }

    float targetX = static_cast<float>(tx);
    float targetY = static_cast<float>(ty);

    // ----------------------------------------------------
    // 移動ロジック
    // ----------------------------------------------------

    // ※ activatedA の判定は、上の IsPlayerOn チェックに包括されるため、
    // 実質的にこの「STATE_A かつ !activatedA」のブロックは削除しても動作します。
    if (state == STATE_A && !activatedA) {
        activatedA = true;
    }

    // 現在地から目標へのベクトル（差分）
    float diffX = targetX - x;
    float diffY = targetY - y;

    // 残りの距離を計算
    float distance = std::sqrt(diffX * diffX + diffY * diffY);

    if (distance <= moveSpeed) {
        MoveOneStep(diffX, diffY, player);

        switch (state) {
        case STATE_A: state = STATE_B; break;
        case STATE_B: state = STATE_C; break;
        case STATE_C: state = STATE_D; break;
        case STATE_D: state = STATE_B; break;
        }
    }
    else {
        float moveX = (diffX / distance) * moveSpeed;
        float moveY = (diffY / distance) * moveSpeed;
        MoveOneStep(moveX, moveY, player);
    }
}

void MoveFloor::Draw()
{
    timer++;
    if (timer % 10 == 0) {
        frame++;
        if (frame >= 2) {
            frame = 0;
        }
    }
    // 回転描画 (中心座標はずらして指定)
    DrawRotaGraph(static_cast<int>(x) + 32, static_cast<int>(y) + 32, 0.2, 0, suiGraphs[frame], TRUE, FALSE);
}

// プレイヤーの下判定用
int MoveFloor::HitCheckDown(int px, int py) {
    if (px < static_cast<int>(x) || px >= static_cast<int>(x) + size) return 0;

    int push = py - static_cast<int>(y);
    if (push >= 0 && push < 16) {
        return push;
    }
    return 0;
}