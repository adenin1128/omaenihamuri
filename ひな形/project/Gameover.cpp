#include "GameOver.h"

GameOver::GameOver()
{
	hImage = LoadGraph("data/image/GAMEOVER.png");
}

GameOver::~GameOver()
{
}

void GameOver::Update()
{
}

void GameOver::Draw()
{
	DrawGraph(1400, 200, hImage, TRUE);
}