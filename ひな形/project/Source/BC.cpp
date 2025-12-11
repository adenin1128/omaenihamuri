#include "BC.h"
#include "field.h"
#include "Player.h"
#include <assert.h>

int BLGraphs[8];

BC::BC(int px, int py)
{
	ConveyorImage = LoadGraph("data/image/belt.png");
	LoadDivGraph("data/image/belt.png", 8, 8, 1, 64, 64, BLGraphs);
	assert(ConveyorImage > 0);
	x = px;
	y = py;
	speed = 0;
	timer = 0;
	frame = 0;
	hanten = FALSE;
}

BC::~BC()
{
}

void BC::Update()
{
	if (CheckHitKey(KEY_INPUT_R)) {
		hanten = FALSE;
	}
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();
	if (field->GetBeltHit() == 24) {
		speed = -5;
	}
	else {
		speed = 0;
	}
	if (field->GetBCHit() == 26) {
		hanten = TRUE;
	}
	else {
		hanten = FALSE;
	}
}

void BC::Draw()
{
	//DrawGraph(x, y + 64, ConveyorImage, TRUE);

	timer++;
	{
		if (timer % 5 == 0) {
			frame++;
			if (frame >= 8) {
				frame = 0;
			}
		}
		DrawRotaGraph(x + 35, y + 64 + 32, 1, 0, BLGraphs[frame], TRUE, hanten);
	}
}