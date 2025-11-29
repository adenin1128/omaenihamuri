#include "Breath.h"
#include <assert.h>

int buraGraphs[2];

Breath::Breath(int px, int py)
{
	buraimage= LoadGraph("data/image/BreathHead.png");
	LoadDivGraph("data/image/BreathHead.png", 2, 2, 1, 64, 64, buraGraphs);
	assert(buraimage > 0);
	state = STATE_START;
	x = px;
	y = py;
	frame2 = 0;
	timer2 = 0;
}

Breath::~Breath()
{
}
void Breath::Update()
{
}

void Breath::Draw()
{
	if (state == STATE_START) {
		int size = 64;
		timer2++;
		{
			if (timer2>= 120) {
				frame2 = 1;
				state = STATE_GO;
			}
			DrawRotaGraph(x * 64 + 32, y * 64 + 32, 4, 0, buraGraphs[frame2], TRUE, FALSE);
		}
	}

	if (state == STATE_GO) {
		DrawRotaGraph(x * 64 + 32, y * 64 + 32, 4, 0, buraGraphs[frame2], TRUE, FALSE);

	}
}