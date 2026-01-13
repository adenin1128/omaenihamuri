#include "HAIKEI.h"

HAIKEI::HAIKEI(int num)
{
	number = -1;
	SetDrawOrder(10000);
	hImage = LoadGraph("data/image/kabe.png");
	dImage = LoadGraph("data/image/haikei1.png");
	mImage = LoadGraph("data/image/aka.png");
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
		DrawRotaGraph(1920/2, 1080/2, 1, 0, dImage, TRUE, FALSE);
	}
	else if (number == 3) {
		DrawRotaGraph(64, 64, 7.5, 0, mImage, TRUE, FALSE);
	}
}