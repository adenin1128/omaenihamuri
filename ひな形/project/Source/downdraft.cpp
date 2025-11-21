#include "downdraft.h"
#include "player.h"

downdraft::downdraft(int px, int py)
{
	downhit = false;
	x = px;
	y = py;
	size = 64;
	Vy = 0.0f;
}

downdraft::~downdraft()
{
}

void downdraft::Update()
{
	Player* player = FindGameObject<Player>();
	if (player != nullptr) {
		if (IsDown(player->GetX(), player->GetY())) {
			player->VerocityUp();
			return;
		}
	}
}

void downdraft::Draw()
{
	if (downhit == true) {
		DrawString(0, 320, "hit", GetColor(255, 255, 255));
		downhit = false;
	}
}

bool downdraft::IsDown(int px, int py)
{
	int xp = px;
	int yp = py;
	if ((xp < (x + size)) && ((xp + size) > x) && ((yp + size > y)) && (yp < (y + size))) {
		downhit = true;
		Vy = -10.0f;
		return true;
	}
	Vy = 0.0f;
	return false;
}
