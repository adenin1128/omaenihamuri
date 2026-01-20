#include "Clear.h"
#include "field.h"
#include "Gameover.h"
#include "Player.h"
#include "Timer.h"
#include "StageNumber.h"

Clear::Clear()
{
	// --- BGMの読み込みと再生を追加 ---
   // 第2引数の DX_PLAYTYPE_LOOP でバックグラウンドでのループ再生になります
	bgmHandle = LoadSoundMem("data/sound/birthday3.mp3"); // パスは適宜調整してください
	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
	deathCount = 0;
	clearImage =  LoadGraph("data/image/culear.png");
	Timer* timer = FindGameObject<Timer>();
	timer->StopTimer();
	deathCount = timer->GetDeathCount();
}

Clear::~Clear()
{
	// 音楽を止めてメモリから削除
	StopSoundMem(bgmHandle);
	DeleteSoundMem(bgmHandle);
	DeleteGraph(clearImage);
}

void Clear::Update()
{
	Player* player = FindGameObject<Player>();
	Timer* timer = FindGameObject<Timer>();
	StageNumber* sn = FindGameObject<StageNumber>();
	timer->GetTime();
	if (player->GetState() != STATE_CLEAR||sn->Clear == true) {
		if (CheckHitKey(KEY_INPUT_R)) {
			SceneManager::ChangeScene("RESULT");
		}
	}
}

void Clear::Draw()
{
	DrawRotaGraph(990, 540, 0.5, 0., clearImage, TRUE, FALSE);
	DrawExtendFormatStringToHandle(930, 600, 4, 4, GetColor(0, 0, 0), GetDefaultFontHandle(), "PRESS THE R KEY", deathCount + 1);
}