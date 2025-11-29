#include "BOAAAA.h"
#include "Breath.h"

//int boaGraphs[1];

Boaaa::Boaaa(int px, int py)
{
	boaimage= LoadGraph("data/image/BOAAA.png");
	//LoadDivGraph("data/image/BOAAA.png", 1, 1, 1, 64, 64, boaGraphs);
    x = px;
    y = py;
}

Boaaa::~Boaaa()
{
}

void Boaaa::Update()
{
}


void Boaaa::Draw()
{
    Breath* breath = FindGameObject<Breath>();

    if (breath && breath->GetState() == STATE_GO) {
        DrawRotaGraph(x * 64 + 128, y * 64 + 54,8, 0, boaimage, TRUE, FALSE);
    }
}
