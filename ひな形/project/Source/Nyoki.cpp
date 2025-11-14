#include "nyoki.h"
#include "field.h"
#include "Player.h"
#include <assert.h>

Nyoki::Nyoki(int px, int py)
{
	nyokiImage = LoadGraph("data/image/nyoblo.png");
	assert(nyokiImage > 0);
	nx = px;
	ny = py;
	size = 64;
	move = 0;
	count = 0;
	loop = 4;//4にしたらニョキニョキする
	a = 0;
}

Nyoki::~Nyoki()
{
}

void Nyoki::Update()
{
	if(loop > 0) {
		count += 1;
		if (count >= 10) {
			count = 0;
			move = (move + 4) % 17;
			loop--;
		}
	}
}

void Nyoki::Draw()
{
	DrawRectGraph(nx, ny, size * move,0,size,size * 4,nyokiImage, TRUE);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "count:: %d", count);
	DrawFormatString(0, 280, GetColor(255, 255, 255), "move:: %d", move);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "loop:: %d", loop);
	DrawFormatString(0, 320, GetColor(255, 255, 255), "hit:: %d", a);
}

bool Nyoki::IsNyoki(int px, int py)
{
	//xp,ypはplayerの座標
	//nx,nyはNyokiの座標
	int xp = px;
	int yp = py;
	if ((xp < (nx + size)) && ((xp + size) > nx) && ((yp + size > ny)) && (yp < (ny + size))) {
		a++;
		return true;
	}
	//(xp<(nx+size))&&((xp + size)>nx)&&((yp+size>ny))&&(yp<(ny+size))これがAABBであってるはず…
	return false;
}
