#include "HAIKEI.h"

HAIKEI::HAIKEI()
{
	SetDrawOrder(10000);
	hImage = LoadGraph("data/image/kabe.png");
}

HAIKEI::~HAIKEI()
{
}

void HAIKEI::Update()
{
}

void HAIKEI::Draw()
{
	DrawGraph(0, 0, hImage, TRUE);
}