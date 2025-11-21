#include "NeoGravity.h"
#include "Player.h"

NeoGravity::NeoGravity(int px, int py)
{
	gx = px;
	gy = py;
	size = 64;
}

NeoGravity::~NeoGravity()
{
}

void NeoGravity::Update()
{
	Player* player = FindGameObject<Player>();
	if (player != nullptr) {
		if (isUp(player->GetX(), player->GetY())) {
			player->VerocitySITA();
			return;
		}
	}
}

void NeoGravity::Draw()
{
}

bool NeoGravity::isUp(int px, int py)
{
	int xp = px;
	int yp = py;
	if ((xp < (gx + size)) && ((xp + size) > gx) && ((yp + size > gy)) && (yp < (gy + size))) {
		return true;
	}
	return false;
}
