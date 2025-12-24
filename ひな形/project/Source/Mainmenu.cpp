#include "Mainmenu.h"
#include <random>
#include "DxLib.h"
#include <iostream>
#include "field.h"
#include "StageNumber.h"
#include "Fader.h"
#include "HAIKEI.h"
#include "Timer.h"
#include "Screen.h"
using namespace std;

//extern const char* Version();

MainmenuScene::MainmenuScene()
{
	rand = 0;
	new Field(5);
	new HAIKEI(3);
	Fader* fader = FindGameObject<Fader>();
	fader->FadeIn(0.1f);
}

MainmenuScene::~MainmenuScene()
{
	HAIKEI* h = FindGameObject<HAIKEI>();
	h->DestroyMe();
}

void MainmenuScene::Update()
{
	StageNumber* stageNum = FindGameObject<StageNumber>();
	Field* f = FindGameObject<Field>();
	Fader* fader = FindGameObject<Fader>();
	Timer* timer = FindGameObject<Timer>();

	if (f->GetGateHit() == 20) {
		random_device rnd;
		mt19937 mt(rnd());
		uniform_int_distribution<>rand100(1, 4);
		rand = rand100(mt);

		if (rand == 1) {
			// 処理 1
			fader->FadeOut(0.1f);
			stageNum->stagenum = 1;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		else if (rand == 2) {
			// 処理 2
			fader->FadeOut(0.1f);
			stageNum->stagenum = 2;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");

		}
		else if (rand == 3) {
			// 処理 3
			fader->FadeOut(0.1f);
			stageNum->stagenum = 3;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");

		}
		else if (rand == 4) {
			// 処理 4
			fader->FadeOut(0.1f);
			stageNum->stagenum = 4;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");

		}
	}
	if (CheckHitKey(KEY_INPUT_1)) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 1;
		timer->StartTimer();
		SceneManager::ChangeScene("PlayScene");
	}
	if (f->GetGateHit() == 21) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 1;
		timer->StartTimer();
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 2;
		timer->StartTimer();
		SceneManager::ChangeScene("PlayScene");
	}
	if (f->GetGateHit() == 22) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 3;
		timer->StartTimer();
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 3;
		timer->StartTimer();
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_4)) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 4;
		timer->StartTimer();
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		fader->FadeOut(0.1f);
		timer->StartTimer();
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_T)) {
		fader->FadeOut(0.1f);
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		fader->FadeOut(0.1f);
		SceneManager::Exit();
	}
}

void MainmenuScene::Draw()
{
	if (Screen::DEVELOPER_MODE == TRUE) {
		DrawString(100, 400, "stage1 press to 1 key ", GetColor(255, 255, 255));
		DrawString(100, 420, "stage2 press to 2 key", GetColor(255, 255, 255));
		DrawString(100, 440, "stage3 press to 3 key", GetColor(255, 255, 255));
		DrawString(100, 490, "stage4 press to 4 key", GetColor(255, 255, 255));
	}
}
