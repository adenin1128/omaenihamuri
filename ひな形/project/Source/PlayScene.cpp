#include "PlayScene.h"
#include "field.h"
#include "StageNumber.h"
#include "HAIKEI.h"
#include "Fader.h"
#include "Timer.h"
#include "Clear.h"
#include "Screen.h"
#include "Trigger.h"

PlayScene::PlayScene()
{
	StageNumber* stagenum = FindGameObject< StageNumber >();
	int sn = stagenum->stagenum;
	Fader* fader = FindGameObject<Fader>();
	fader->FadeIn(0.1f);
	new Field(sn);
	new HAIKEI(1);
}

PlayScene::~PlayScene()
{
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

	if (CheckHitKey(KEY_INPUT_T)) {
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
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		fader->FadeOut(0.1f);
		timer->StopTimer();
		timer->ResetTimer();
		timer->ResetDeathcount();
		SceneManager::Exit();
	}
}

void PlayScene::Draw()
{
	if (Screen::DEVELOPER_MODE == TRUE) {
		DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
		DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	}
}