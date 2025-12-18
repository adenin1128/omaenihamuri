#include "Result.h"

Result::Result()
{
	TyImage = LoadGraph("data/image/Ty.png");
}

Result::~Result()
{
}

void Result::Update()
{

}

void Result::Draw()
{
	DrawGraph(0, 0, TyImage, TRUE);
}