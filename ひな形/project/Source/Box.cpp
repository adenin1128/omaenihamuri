
#include "Box.h"

Box::Box(int px, int py, int i) {

}

Box::~Box()
{
}

void Box::Draw()
{

}

void Box::Update()
{

}

struct BoxDirection {
	float Up, Down, Right, Left;
};
bool CheckHit( const BoxDirection& x, const BoxDirection& b) {

	return  !(x.Right < b.Left ||
		x.Left  > b.Right ||
		x.Down  < b.Up ||
		x.Up    > b.Down);
}
void BOXCOLLIDER(BoxDirection& x, const BoxDirection& b)
{

    if (!CheckHit(x, b)) return;

    float overlapX1 = b.Right - x.Left;

    float overlapX2 = x.Right - b.Left;

    float overlapY1 = b.Down - x.Up;

    float overlapY2 = x.Down - b.Up;

    float overlapX = (overlapX1 < overlapX2) ? -overlapX1 : overlapX2;

    float overlapY = (overlapY1 < overlapY2) ? -overlapY1 : overlapY2;

    if (fabs(overlapX) < fabs(overlapY))

    {

        x.Left += overlapX;

        x.Right += overlapX;

    }

    else

    {

        x.Up += overlapY;

        x.Down += overlapY;
    }
}

