#include "SuiUGOKU.h"
#include "Player.h"
#include "Field.h"
#include <assert.h>
#include <cmath>

static int suiGraphs[2];

SuiUGOKU::SuiUGOKU(int px, int py)
{
    sImage = LoadGraph("data/image/すい.png");
    LoadDivGraph("data/image/すい.png", 2, 2, 1, 640, 640, suiGraphs);
    assert(sImage > 0);

    resetX = px;
    resetY = py;

    Reset();
}

SuiUGOKU::~SuiUGOKU()
{
}

void SuiUGOKU::Reset()
{
    x = static_cast<float>(resetX);
    y = static_cast<float>(resetY);

    moveSpeed = 3.0f;

    // ★変更
    state = SUI_STATE_A;
    activatedA = false;

    frame = 0;
    timer = 0;
    size = 64;
}

bool SuiUGOKU::IsPlayerOn(const Player* p) const
{
    if (!p) return false;

    const float px = p->GetX();
    const float py = p->GetY();
    const float pw = static_cast<float>(p->GetWidth());
    const float ph = static_cast<float>(p->GetHeight());

    const float playerBottom = py + ph;
    const bool xOverlap = (px < x + size) && (px + pw > x);
    const bool onTop = std::fabs(playerBottom - y) <= 8.0f;

    return xOverlap && onTop;
}

void SuiUGOKU::MoveOneStep(float moveX, float moveY, Player* p)
{
    x += moveX;
    y += moveY;

    if (p && IsPlayerOn(p)) {
        p->SetX(p->GetX() + moveX);
        p->SetY(p->GetY() + moveY);
    }
}

void SuiUGOKU::Update()
{
    Field* field = FindGameObject<Field>();
    Player* player = FindGameObject<Player>();
    if (!field) return;

    int targetBlockID = -1;

    // ★変更：Enum名を新しいものに
    switch (state) {
    case SUI_STATE_A: targetBlockID = 41; break;
    case SUI_STATE_B: targetBlockID = 42; break;
    case SUI_STATE_C: targetBlockID = 43; break;
    case SUI_STATE_D: targetBlockID = 41; break;
    default: break;
    }

    int tx = 0, ty = 0;
    if (field->GetPointPos(targetBlockID, &tx, &ty) == false) {
        return;
    }

    float targetX = static_cast<float>(tx);
    float targetY = static_cast<float>(ty);

    // ★変更：Enum名を新しいものに
    if (state == SUI_STATE_A && !activatedA) {
        if (IsPlayerOn(player)) {
            activatedA = true;
        }
        else {
            return;
        }
    }

    float diffX = targetX - x;
    float diffY = targetY - y;
    float distance = std::sqrt(diffX * diffX + diffY * diffY);

    if (distance <= moveSpeed) {
        MoveOneStep(diffX, diffY, player);

        // ★変更：Enum名を新しいものに
        switch (state) {
        case SUI_STATE_A: state = SUI_STATE_B; break;
        case SUI_STATE_B: state = SUI_STATE_C; break;
        case SUI_STATE_C: state = SUI_STATE_D; break;
        case SUI_STATE_D: state = SUI_STATE_B; break;
        }
    }
    else {
        float moveX = (diffX / distance) * moveSpeed;
        float moveY = (diffY / distance) * moveSpeed;
        MoveOneStep(moveX, moveY, player);
    }
}

void SuiUGOKU::Draw()
{
    timer++;
    if (timer % 10 == 0) {
        frame++;
        if (frame >= 2) {
            frame = 0;
        }
    }
    DrawRotaGraph(static_cast<int>(x) + 32, static_cast<int>(y) + 32, 0.2, 0, suiGraphs[frame], TRUE, FALSE);
}

int SuiUGOKU::HitCheckDown(int px, int py) {
    if (px < static_cast<int>(x) || px >= static_cast<int>(x) + size) return 0;

    int push = py - static_cast<int>(y);
    if (push >= 0 && push < 16) {
        return push;
    }
    return 0;
}