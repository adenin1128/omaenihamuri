#include "GameOver.h"
#include <assert.h>

GameOver::GameOver()
{
	hImage = LoadGraph("data/image/GAMEOVER.png");
	assert(hImage > 0);
}

GameOver::~GameOver()
{
}

void GameOver::Update()
{
	if (CheckHitKey(KEY_INPUT_E)) {


	}
}

void GameOver::Draw()
{
	DrawGraph(1400, 200, hImage, TRUE);
}