#include "GameOver.h"
#include "field.h"
#include  "Timer.h"
#include <assert.h>

GameOver::GameOver()
{
	loseImage = LoadGraph("data/image/you lose.png");
	assert(loseImage > 0);
	Timer* timer = FindGameObject<Timer>();
	deathCount = timer->GetDeathCount();
}

GameOver::~GameOver()
{
}

void GameOver::Update()
{
	if (CheckHitKey(KEY_INPUT_R)) {
		DestroyMe();
	}
}

void GameOver::Draw()
{
	DrawRotaGraph(990, 540, 0.5, 0., loseImage, TRUE, FALSE);
	DrawExtendFormatStringToHandle(850, 560, 4, 4, GetColor(0, 0, 0), GetDefaultFontHandle(), "ïâÇØÇΩâÒêî %dâÒ", deathCount + 1);

}