
#include "MoveFloor.h"
#include "Player.h"
#include "field.h"
#include <assert.h>
#include <cmath> // std::fabs

int suiGraphs[2];

MoveFloor::MoveFloor(int px, int py)
{
    fImage = LoadGraph("data/image/すい.png");
    LoadDivGraph("data/image/すい.png", 2, 2, 1, 640, 640, suiGraphs);
    assert(fImage > 0);

    x = static_cast<float>(px);
    y = static_cast<float>(py);

    moveSpeed = 3.0f;
    maxSegmentLength = 0.0f;
    progressed = 0.0f;

    state = STATE_A;
    activatedA = false;

    frame = 0;
    timer = 0;

    size = 64;
}

MoveFloor::~MoveFloor()
{
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
    const bool xOverlap =
        (px < x + PLATFORM_W) && (px + pw > x);
    const bool onTop =
        std::fabs(playerBottom - y) <= 6.0f; // 許容誤差（必要なら調整）

    return xOverlap && onTop;
}

void MoveFloor::MoveOneStep(float dir, Player* p)
{
    const float dx = moveSpeed * dir;

    // 残距離に合わせて丸める（行き過ぎ防止）
    const float remaining = std::fabs(maxSegmentLength) - progressed;
    float step = dx;
    if (std::fabs(dx) > remaining) {
        step = (dx > 0 ? +remaining : -remaining);
    }

    // 床移動
    x += step;
    progressed += std::fabs(step);

    // 乗っていれば同じだけプレイヤーも動かす
    if (p && IsPlayerOn(p)) {
        p->SetX(p->GetX() + step);
    }
}

void MoveFloor::Update()
{
    Field* field = FindGameObject<Field>();
    Player* player = FindGameObject<Player>();
    if (!field) return;

    // 今状態の区間長（px）取得：30/31/32の差×64
    maxSegmentLength = static_cast<float>(field->Movefloor(static_cast<int>(x), static_cast<int>(y)));
    if (maxSegmentLength == 0.0f) return; // 見つからない時は何もしない

    switch (state) {
    case STATE_A: {
        // 30->31 は「乗ったら開始」
        if (!activatedA) {
            if (IsPlayerOn(player)) {
                activatedA = true;
                progressed = 0.0f;
            }
            else {
                return; // 乗ってない間は停止
            }
        }
        const float dir = (maxSegmentLength >= 0.0f) ? +1.0f : -1.0f;
        MoveOneStep(dir, player);

        if (progressed >= std::fabs(maxSegmentLength)) {
            state = STATE_B;   // 31到達 → 31->32へ
            progressed = 0.0f;
        }
        break;
    }

    case STATE_B: {
        const float dir = (maxSegmentLength >= 0.0f) ? +1.0f : -1.0f;
        MoveOneStep(dir, player);

        if (progressed >= std::fabs(maxSegmentLength)) {
            // 32到達 → 32->33へ
            state = STATE_C;   
            progressed = 0.0f;
        }
        break;
    }

    case STATE_C: {
        const float dir = (maxSegmentLength >= 0.0f) ? +1.0f : -1.0f;
        MoveOneStep(dir, player);

        if (progressed >= std::fabs(maxSegmentLength)) {
            //33到達　33→31へ
            state = STATE_D;
            progressed = 0.0f;
        }
        break;
    }
    case STATE_D: {
        const float dir = (maxSegmentLength >= 0.0f) ? +1.0f : -1.0f;
        MoveOneStep(dir, player);

        if (progressed >= std::fabs(maxSegmentLength)) {
            // 31到達 → 31->32へ
            state = STATE_B;   
            progressed = 0.0f;
        }
        break;
    }
    default:
        break;
    }
    // もし「乗っている時だけ往復、降りたら停止」にしたいなら、
           // if (!IsPlayerOn(player)) { state = STATE_A; activatedA = false; }
}

void MoveFloor::Draw()
{
    //DrawGraph(static_cast<int>(x), static_cast<int>(y), fImage, TRUE);

    timer++;
    {
        if (timer % 10 == 0) {
            frame++;
            if (frame >= 2) {
                frame = 0;
            }
        }
        DrawRotaGraph(static_cast<int>(x) + 32, static_cast<int>(y) + 32, 0.2, 0, suiGraphs[frame], TRUE, FALSE);
    }
}

// プレイヤーの下判定用
int MoveFloor::HitCheckDown(int px, int py) {
    // Nyokiの横範囲内かチェック
    if (px < static_cast<int>(x) || px >= static_cast<int>(x) + size) return 0;

    // ブロックの上面とプレイヤーの足元の距離
    int push = py - static_cast<int>(y);
    if (push >= 0 && push < 16) {  // ブロックの上面付近なら押し出す
        return push;
    }
    return 0;
}