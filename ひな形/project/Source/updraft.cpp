#include "updraft.h"
#include "player.h"

Updraft::Updraft(int px, int py)
{
	Uphit = false;
	x = px;
	y = py;
	size = 64;
	Vy = 0.0f;
}

Updraft::~Updraft()
{
}

void Updraft::Update()
{
	Player* player = FindGameObject<Player>();
	if (player != nullptr) {
		if (IsUp(player->GetX(), player->GetY())) {
			player->VerocityUp();
			return;
		}
	}
}

void Updraft::Draw()
{
	if (Uphit == true) {
		DrawString(0, 320, "hit", GetColor(255, 255, 255));
		Uphit = false;
	}
}

bool Updraft::IsUp(int px, int py)
{
	int xp = px;
	int yp = py;
	if ((xp < (x + size)) && ((xp + size) > x) && ((yp + size > y)) && (yp < (y + size))) {
		Uphit = true;
		Vy = -10.0f;
		return true;
	}
	Vy = 0.0f;
	return false;
}
