#include "HAIKEI.h"

HAIKEI::HAIKEI(int num)
{
	number = -1;
	SetDrawOrder(10000);
	hImage = LoadGraph("data/image/kabe.png");
	dImage = LoadGraph("data/image/doukutu.png");
	mImage = LoadGraph("data/image/menu.png");
	number = num;
}

HAIKEI::~HAIKEI()
{
	DeleteGraph(hImage);
	DeleteGraph(dImage);
	DeleteGraph(mImage);
}

void HAIKEI::Update()
{
}

void HAIKEI::Draw()
{
	if (number == 1) {
		DrawGraph(0, 0, hImage, TRUE);
	}
	else if (number == 2) {
		DrawRotaGraph(64, 64, 7.5, 0, dImage, TRUE, FALSE);
	}
	else if (number == 3) {
		DrawRotaGraph(64, 64, 7.5, 0, mImage, TRUE, FALSE);
	}
}