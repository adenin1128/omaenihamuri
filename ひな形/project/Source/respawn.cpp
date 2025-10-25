#include "respawn.h"
#include "Player.h"
#include "field.h"

respawn::respawn(int px, int py)
{
	hataImage = LoadGraph("data/image/hata/png");
	x = px;
	y = py;
	isresActive = false;
}

respawn::~respawn()
{
}

void respawn::Update()
{
	if (CheckHitKey(KEY_INPUT_R)) {

	}
}

void respawn::resActive()
{
	isresActive = true;
}

void respawn::Draw()
{
	DrawGraph(x, y, hataImage, true);
}