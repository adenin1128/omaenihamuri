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
#include <assert.h>
using namespace std;

//extern const char* Version();
int medaruGraphs[3];

MainmenuScene::MainmenuScene()
{
	rand = 0;
	medatimer = 0;
	migi = false;
	hidari = false;
	new HAIKEI(3);
	Fader* fader = FindGameObject<Fader>();
	fader->FadeIn(0.1f);
	nanidobarimage = LoadGraph("data/image/nanidobar.png");
	nanidotyoimage = LoadGraph("data/image/nanidotyo.png");
	//medaruimage = LoadGraph("data/image/medaru.png");
	migiimage = LoadGraph("data/image/migi.png");
	hidariimage = LoadGraph("data/image/hidari.png");
	setumeiimage = LoadGraph("data/image/explanation.png");
	playerimage = LoadGraph("data/image/omae.png");
	medaruimage = LoadGraph("data/image/medaru.png");
	LoadDivGraph("data/image/medaru.png", 3, 3, 1, 128, 128, medaruGraphs);
	assert(medaruimage > 0);
	state = STAGE1;

}

MainmenuScene::~MainmenuScene()
{
	HAIKEI* h = FindGameObject<HAIKEI>();
	h->DestroyMe();
}

void MainmenuScene::Update()
{
	if (state == STAGE1) {
		medarustage = 1;
		migi = false;
		hidari = false;
		medatimer++;
		if (medatimer > 10) {
			if (CheckHitKey(KEY_INPUT_D)) {
				state = STAGE2;
				medatimer = 0;
				migi = true;
			}
			if (CheckHitKey(KEY_INPUT_A)) {
				state = STAGE3;
				medatimer = 0;	
				hidari = true;
			}
		}
	}
	else if (state == STAGE2) {
		medarustage = 2;
		migi = false;
        hidari = false;
		medatimer++;
		if (medatimer > 10) {
			if (CheckHitKey(KEY_INPUT_D)) {
				state = STAGE3;
				medatimer = 0;
				migi = true;
			}
			if (CheckHitKey(KEY_INPUT_A)) {
				state = STAGE1;
				medatimer = 0;
				hidari = true;
			}
		}
	}
	else if (state == STAGE3) {
		medarustage = 3;
		migi = false;
        hidari = false;
		medatimer++;
		if (medatimer > 10) {
			if (CheckHitKey(KEY_INPUT_D)) {
				state = STAGE1;
				medatimer = 0;
				migi = true;
			}
			if (CheckHitKey(KEY_INPUT_A)) {
				state = STAGE2;
				medatimer = 0;
				hidari = true;
			}
		}
	}

		StageNumber* stageNum = FindGameObject<StageNumber>();
		Field* f = FindGameObject<Field>();
		Fader* fader = FindGameObject<Fader>();
		Timer* timer = FindGameObject<Timer>();
		random_device rnd;
		mt19937 mt(rnd());
		uniform_int_distribution<>rand100(1, 4);
		rand = rand100(mt);

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (medarustage == 1) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 1;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		else if (medarustage == 2) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 2;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		else if (medarustage == 3) {
		if (rand == 3) {
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
	}
		if (CheckHitKey(KEY_INPUT_1)) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 1;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		//if (f->GetGateHit() == 21) {
		////	fader->FadeOut(0.1f);
		////	stageNum->stagenum = 1;
		////	timer->StartTimer();
		////	SceneManager::ChangeScene("PlayScene");
		////}
		if (CheckHitKey(KEY_INPUT_2)) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 2;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		////if (f->GetGateHit() == 22) {
		////	fader->FadeOut(0.1f);
		////	stageNum->stagenum = 3;
		////	timer->StartTimer();
		////	SceneManager::ChangeScene("PlayScene");
		////}
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
	DrawRotaGraph(1500, 500, 12, 0, playerimage, TRUE);
	DrawRotaGraph(400, 150, 7, 0, nanidobarimage, TRUE);
	DrawRotaGraph(450, 150, 3, 0, nanidotyoimage, TRUE);
	DrawRotaGraph(960, 900, 7.5, 0, setumeiimage, TRUE);
	if (migi == true)
	{
		DrawRotaGraph(650, 550, 4, 0, migiimage, TRUE);
	}
	else if (migi == false)
	{
		DrawRotaGraph(650, 550, 3, 0, migiimage, TRUE);
	}

	if (hidari == true)
	{
		DrawRotaGraph(150, 550, 4, 0, hidariimage, TRUE);

	}else if (hidari == false)
	{
		DrawRotaGraph(150, 550, 3, 0, hidariimage, TRUE);
	}

	if (state == STAGE1)
		DrawRotaGraph(400, 550, 3, 0, medaruGraphs[0], TRUE);
	else if (state == STAGE2)
		DrawRotaGraph(400, 550, 3, 0, medaruGraphs[1], TRUE);
	else if (state == STAGE3)
	    DrawRotaGraph(400, 550, 3, 0, medaruGraphs[2], TRUE);


	if (Screen::DEVELOPER_MODE == TRUE) {
		DrawString(100, 400, "stage1 press to 1 key ", GetColor(255, 255, 255));
		DrawString(100, 420, "stage2 press to 2 key", GetColor(255, 255, 255));
		DrawString(100, 440, "stage3 press to 3 key", GetColor(255, 255, 255));
		DrawString(100, 490, "stage4 press to 4 key", GetColor(255, 255, 255));
	}
}
