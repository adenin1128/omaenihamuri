#include "skeleton.h"
#include "field.h"
#include "Player.h"

Skeleton::Skeleton(int px, int py)
{
	x = px;
	y = py;
	size = 64;
	b = 0;
}

Skeleton::~Skeleton()
{
}

void Skeleton::Update()
{
}

void Skeleton::Draw()
{
	DrawFormatString(0, 340, GetColor(255, 255, 255), "hitSkeleton:: %d", b);
}

bool Skeleton::IsHit(int px, int py)
{
	int xp = px;
	int yp = py;
	if ((xp < (x + size)) && ((xp + size) > x) && ((yp + size > y)) && (yp < (y + size))) {
		b++;
		return true;
	}
	return false;
}
