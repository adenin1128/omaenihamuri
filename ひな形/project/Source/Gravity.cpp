#include "Gravity.h"
#include "Player.h"

Gravity::Gravity(int px, int py)
{
	gx = px;
	gy = py;
	size = 64;
}

Gravity::~Gravity()
{
}

void Gravity::Update()
{
	Player* player = FindGameObject<Player>();
	if (player != nullptr) {
		if (isDown(player->GetX(), player->GetY())) {
			player->VerocityDown();
			return;
		}
	}
}

void Gravity::Draw()
{
}

bool Gravity::isDown(int px, int py)
{
	int xp = px;
	int yp = py;
	if ((xp < (gx + size)) && ((xp + size) > gx) && ((yp + size > gy)) && (yp < (gy + size))) {
		return true;
	}
	return false;
}
