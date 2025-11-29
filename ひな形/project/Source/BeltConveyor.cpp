#include "BeltConveyor.h"
#include "field.h"
#include "Player.h"
#include <assert.h>

int BeltGraphs[8];

BeltConveyor::BeltConveyor(int px, int py)
{
	ConveyorImage = LoadGraph("data/image/belt.png");
	LoadDivGraph("data/image/belt.png", 8, 8, 1, 64, 64, BeltGraphs);
	assert(ConveyorImage > 0);
	x = px;
	y = py;
	speed = 0;
	timer = 0;
	frame = 0;
}

BeltConveyor::~BeltConveyor()
{
}

void BeltConveyor::Update()
{
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();
	if (field->GetBeltHit() == 23) {
		speed = 5;
	}
	else {
		speed = 0;
	}
	return;
}

void BeltConveyor::Draw()
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
		DrawRotaGraph(x + 35, y + 64 + 32, 1, 0, BeltGraphs[frame], TRUE, FALSE);
	}
}