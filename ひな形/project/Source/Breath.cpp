#include "Breath.h"
#include "BOAAAA.h"
#include <assert.h>

int buraGraphs[2];



Breath::Breath(int px, int py, int i, int d, int tx, int ty) : GameObject()
{
	buraimage = LoadGraph("data/image/BreathHead.png");
	LoadDivGraph("data/image/BreathHead.png", 2, 2, 1, 64, 64, buraGraphs);
	assert(buraimage > 0);


	isActive = false;
	state = STATE_START;
	x = px;
	y = py;

	frame2 = 0;
	timer2 = 0;
	angle = 0;

	dir = 0;
	moveX = tx;
	moveY = ty;

	boaaa = nullptr;
}


Breath::~Breath()
{
	DeleteGraph(buraimage);
}
void Breath::Update()
{
	if (!isActive) return;

	timer++;

	if (state == STATE_START && timer > startTime) {
		state = STATE_GO;
		boaaa = new Boaaa(x, y, dir, 2000);
	}

	if (state == STATE_GO && timer > maxTime) {
		state = STATE_FIN;
		if (boaaa) boaaa->DestroyMe();
	}

	if (state == STATE_FIN) {
		DestroyMe();
	}
}

void Breath::Draw()
{
	if (!isActive) return;

	int frame2 = 0;
	if (state == STATE_START) {
		frame2 = 0;
	}

	if (state == STATE_GO) {
		frame2 = 1;
	}
	DrawRotaGraph(x + 32, y + 32, 4, angle, buraGraphs[frame2], TRUE, FALSE);
}

void Breath::Active() {
	isActive = true;
}


//Breath::Breath(int px, int py, int direction, int tx, int ty)
//	: Breath(int px, int py, int i, int d, int tx, int ty)   // Å© Ç±Ç±Ç™àÍî‘ëÂéñ
//{
//	dir = direction;
//	moveX = tx;
//	moveY = ty;
//}
