#include "skeleton.h"
#include "field.h"
#include "Player.h"

Skeleton::Skeleton(int px, int py)
{
	x = px;
	y = py;
	size = 64;
}

Skeleton::~Skeleton()
{
}

void Skeleton::Update()
{
}

void Skeleton::Draw()
{
}

bool Skeleton::IsHit(int px, int py)
{
	int xp = px;
	int yp = py;
	if ((xp < (x + size)) && ((xp + size) > x) && ((yp + size > y)) && (yp < (y + size))) {
		return true;
	}
	return false;
}
