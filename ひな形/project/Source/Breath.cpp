#include "Breath.h"
#include "BOAAAA.h"
#include <assert.h>

int buraGraphs[2];



Breath::Breath(int px, int py, int i, int d, int tx, int ty) : GameObject()
{
	buraimage = LoadGraph("data/image/BreathHead.png");
	LoadDivGraph("data/image/BreathHead.png", 2, 2, 1, 64, 64, buraGraphs);
	assert(buraimage > 0);

	ResetX = px;
	ResetY = py;

	Rdir = d;
	RmoveX = tx;
	RmoveY = ty;
	Reset();
}


Breath::~Breath()
{
	DeleteGraph(buraimage);
}

void Breath::Reset()
{
	used = false;
	isActive = false;
	state = STATE_START;
	x = ResetX;
	y = ResetY;

	frame2 = 0;
	timer = 0;
	angle = 0;

	dir = Rdir;
	moveX = RmoveX;
	moveY = RmoveY;

	boaaa = nullptr;
}

void Breath::Update()
{
	if (!isActive) return;

	timer++;

	if (state == STATE_START && timer > startTime) {
		state = STATE_GO;
		boaaa = new Boaaa(x, y, dir, 2000);
	}

	if (state == STATE_GO && timer > maxTime || CheckHitKey(KEY_INPUT_R)) {
		state = STATE_FIN;
		if (boaaa) boaaa->DestroyMe();
	}

	if (state == STATE_FIN) {
		isActive = false;
		timer = 0;
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
	if (used) return;
	used = true;
	isActive = true;
	timer = 0;
	state = STATE_START;
}


//Breath::Breath(int px, int py, int direction, int tx, int ty)
//	: Breath(int px, int py, int i, int d, int tx, int ty)   // Å© Ç±Ç±Ç™àÍî‘ëÂéñ
//{
//	dir = direction;
//	moveX = tx;
//	moveY = ty;
//}
