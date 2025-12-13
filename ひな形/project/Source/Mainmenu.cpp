#include "Mainmenu.h"
#include <random>
#include "DxLib.h"
#include <iostream>
#include "field.h"
#include "StageNumber.h"
#include "Fader.h"
using namespace std;

//extern const char* Version();

MainmenuScene::MainmenuScene()
{
	menuImage = LoadGraph("data/image/menu.png"); // メニュー用の画像いつか用意する
	rand = 0;
	new Field(5);
	Fader* fader = FindGameObject<Fader>();
	fader->FadeIn(0.1f);
}

MainmenuScene::~MainmenuScene()
{
}

void MainmenuScene::Update()
{
	StageNumber* stageNum = FindGameObject<StageNumber>();
	Field* f = FindGameObject<Field>();
	Fader* fader = FindGameObject<Fader>();

	if (f->GetGateHit() == 20) {
		random_device rnd;
		mt19937 mt(rnd());
		uniform_int_distribution<>rand100(1, 4);
		rand = rand100(mt);

		if (rand == 1) {
			// 処理 1
			fader->FadeOut(0.1f);
			stageNum->stagenum = 1;
			SceneManager::ChangeScene("PlayScene");
		}
		else if (rand == 2) {
			// 処理 2
			fader->FadeOut(0.1f);
			stageNum->stagenum = 2;
			SceneManager::ChangeScene("PlayScene");

		}
		else if (rand == 3) {
			// 処理 3
			fader->FadeOut(0.1f);
			stageNum->stagenum = 3;
			SceneManager::ChangeScene("PlayScene");

		}
		else if (rand == 4) {
			// 処理 4
			fader->FadeOut(0.1f);
			stageNum->stagenum = 4;
			SceneManager::ChangeScene("PlayScene");

		}
	}
	if (CheckHitKey(KEY_INPUT_1)) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 1;
		SceneManager::ChangeScene("PlayScene");
	}
	if (f->GetGateHit() == 21) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 1;
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 2;
		SceneManager::ChangeScene("PlayScene");
	}
	if (f->GetGateHit() == 22) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 3;
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 3;
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_4)) {
		fader->FadeOut(0.1f);
		stageNum->stagenum = 4;
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		fader->FadeOut(0.1f);
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
	DrawRectGraph(0, 0, 0, 0, 1920, 1080, menuImage, 1);
	DrawString(100, 400, "stage1 press to 1 key ", GetColor(255, 255, 255));
	DrawString(100, 420, "stage2 press to 2 key", GetColor(255, 255, 255));
	DrawString(100, 440, "stage3 press to 3 key", GetColor(255, 255, 255));
	DrawString(100, 490, "stage4 press to 4 key", GetColor(255, 255, 255));
	//DrawString(0, 20, Version(), GetColor(255, 255, 255));
	/*DrawString(0, 0, "TITLE SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "一応一旦1でステージ１だお", GetColor(255, 255, 255));
	DrawString(100, 420, "2でステージ２だお", GetColor(255, 255, 255));
	DrawString(100, 440, "ステージ3も追加したお", GetColor(255, 255, 255));
	DrawString(100, 490, "魂のステージ4をご照覧あれ", GetColor(255, 255, 255));
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%4.1f", 1.0f / Time::DeltaTime());*/
}
