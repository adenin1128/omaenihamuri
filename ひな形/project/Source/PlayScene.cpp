#include "PlayScene.h"
#include "field.h"
#include "StageNumber.h"
#include "HAIKEI.h"
#include "Fader.h"
#include "Timer.h"
#include "Clear.h"
#include "Screen.h"
#include "Trigger.h"
#include <DxLib.h>

PlayScene::PlayScene()
{
	// --- BGMの読み込みと再生を追加 ---
   // 第2引数の DX_PLAYTYPE_LOOP でバックグラウンドでのループ再生になります
	bgmHandle = LoadSoundMem("data/sound/PLAYSCENE.mp3"); // パスは適宜調整してください
	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
	StageNumber* stagenum = FindGameObject< StageNumber >();
	int sn = stagenum->stagenum;
	Fader* fader = FindGameObject<Fader>();
	fader->FadeIn(0.1f);
	new Field(sn);
	new HAIKEI(1);
}

PlayScene::~PlayScene()
{
	// 音楽を止めてメモリから削除
	StopSoundMem(bgmHandle);
	DeleteSoundMem(bgmHandle);
	HAIKEI* h = FindGameObject<HAIKEI>();
	h->DestroyMe();
	Clear* clear = FindGameObject<Clear>();
	if (clear != nullptr) {
		clear->DestroyMe();
	}
}

void PlayScene::Update()
{
	Fader* fader = FindGameObject<Fader>();
	Timer* timer = FindGameObject<Timer>();
	StageNumber* sn = FindGameObject<StageNumber>();

	if (sn->noSound == true) {
		ChangeVolumeSoundMem(0, bgmHandle);
	}
	else {
		ChangeVolumeSoundMem(255, bgmHandle);
	}

	if (CheckHitKey(KEY_INPUT_O)) {
		fader->FadeOut(0.1f);
		timer->StopTimer();
		timer->ResetTimer();
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_M)) {
		fader->FadeOut(0.1f);
		timer->StopTimer();
		timer->ResetTimer();
		SceneManager::ChangeScene("MENU");
	}

	if (Screen::DEVELOPER_MODE == TRUE || CheckHitKey(KEY_INPUT_RIGHT)) {
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			fader->FadeOut(0.1f);
			timer->StopTimer();
			timer->ResetTimer();
			timer->ResetDeathcount();
			SceneManager::Exit();
		}
	}
}

void PlayScene::Draw()
{
	if (Screen::DEVELOPER_MODE == TRUE) {
		DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
		DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	}
}