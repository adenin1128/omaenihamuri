#include "respawn.h"
#include "Player.h"
#include "field.h"

respawn::respawn(int px, int py)
{
	hataImage = LoadGraph("data/image/hata.png");
	x = px;
	y = py;
}

respawn::~respawn()
{
}

void respawn::Update()
{
	Player* player = FindGameObject<Player>();
	VECTOR2 pPos = player->GetPosition();
	pPos.x += 32;
	pPos.y += 32;

	int diffX = pPos.x - x;
	diffX = diffX * diffX;
	int diffY = pPos.y - y;
	diffY = diffY * diffY;
	int diff = sqrtf(diffX + diffY);

	if (diff < 64) {
		Field* field = FindGameObject<Field>();
		
		field->ChangeRespawnPoint(x/64, y/64);
		DestroyMe();
	}
}

void respawn::Draw()
{
	DrawGraph(x, y, hataImage, true);
}