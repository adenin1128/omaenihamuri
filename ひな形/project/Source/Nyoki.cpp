#include "nyoki.h"
#include "field.h"
#include "Player.h"
#include <assert.h>

Nyoki::Nyoki(int px, int py)
{
	nyokiImage = LoadGraph("data/image/nyoblo.png");
	assert(nyokiImage > 0);
	x = px;
	y = py;
	size = 64;
	move = 0;
	count = 0;
	loop = 4;
}

Nyoki::~Nyoki()
{
}

void Nyoki::Update()
{
	if(loop > 0) {
		count += 1;
		if (count >= 50) {
			count = 0;
			move = (move + 4) % 17;
			loop--;
		}
	}
}

void Nyoki::Draw()
{
	DrawRectGraph(x, y, size * move,0,size,size * 4,nyokiImage, TRUE);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "count:: %d", count);
	DrawFormatString(0, 280, GetColor(255, 255, 255), "move:: %d", move);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "loop:: %d", loop);
}