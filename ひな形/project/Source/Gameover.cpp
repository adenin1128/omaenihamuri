#include "GameOver.h"
#include "field.h"
#include  "Timer.h"
#include <assert.h>

GameOver::GameOver()
{
	loseImage = LoadGraph("data/image/you lose.png");
	// --- 追加: サウンドの読み込み ---
	seHandle = LoadSoundMem("data/sound/GAMEOVER.mp3"); // パスは環境に合わせて調整してください
	assert(loseImage > 0);
	if (seHandle != -1) {
		PlaySoundMem(seHandle, DX_PLAYTYPE_BACK);
	}
	Timer* timer = FindGameObject<Timer>();
	deathCount = timer->GetDeathCount();
}

GameOver::~GameOver()
{
	//// --- 追加: サウンドのメモリ解放 ---
	DeleteSoundMem(seHandle);
}

void GameOver::Update()
{
	if (CheckHitKey(KEY_INPUT_R)) {
		StopSoundMem(seHandle);
		DestroyMe();
	}
}

void GameOver::Draw()
{
	DrawRotaGraph(990, 540, 0.5, 0., loseImage, TRUE, FALSE);
	DrawExtendFormatStringToHandle(850, 560, 4, 4, GetColor(0, 0, 0), GetDefaultFontHandle(), "負けた回数 %d回", deathCount + 1);

}