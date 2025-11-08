#include "GameOver.h"
#include "field.h"
#include <assert.h>

GameOver::GameOver()
{
	loseImage = LoadGraph("data/image/you lose.png");
	assert(loseImage > 0);
	Field* field = FindGameObject<Field>();
	deathCount = field->GetDeathCount();
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
	DrawExtendFormatStringToHandle(870, 560, 2, 2, GetColor(0, 0, 0), GetDefaultFontHandle(), "ïâÇØÇΩâÒêî %dâÒ", deathCount);
}