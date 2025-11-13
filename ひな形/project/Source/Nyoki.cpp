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
}

Nyoki::~Nyoki()
{
}

void Nyoki::Update()
{
	while (move = 4) {
		count += 1;
		if (count >= 5) {
			count = 0;
			move = (move + 4) % 13;
		}
	}
}

void Nyoki::Draw()
{
	DrawRectGraph(x, y, size * move,0,size,size * 4,nyokiImage, TRUE);
}