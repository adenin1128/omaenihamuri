#include "BeltConveyorL.h"
#include "field.h"
#include "Player.h"
#include <assert.h>

int BeltLGraphs[8];

BeltConveyorL::BeltConveyorL(int px, int py)
{
	ConveyorImage = LoadGraph("data/image/belt.png");
	LoadDivGraph("data/image/belt.png", 8, 8, 1, 64, 64, BeltLGraphs);
	assert(ConveyorImage > 0);
	x = px;
	y = py;
	speed = 0;
	timer = 0;
	frame = 0;
}

BeltConveyorL::~BeltConveyorL()
{
}

void BeltConveyorL::Update()
{
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();
	if (field->GetBeltHit() == 24) {
		speed = -5;
	}
	else {
		speed = 0;
	}
	return;
}

void BeltConveyorL::Draw()
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
		DrawRotaGraph(x + 35, y + 64 + 32, 1, 0, BeltLGraphs[frame], TRUE, TRUE);
	}
}