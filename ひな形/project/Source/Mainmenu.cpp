#include "Mainmenu.h"
#include <random>
#include "DxLib.h"
#include <iostream>
#include "field.h"
#include "StageNumber.h"
using namespace std;

//extern const char* Version();

MainmenuScene::MainmenuScene()
{
	menuImage = LoadGraph("data/image/menu.png"); // メニュー用の画像いつか用意する
	rand = 0;
	new Field(5);
}

MainmenuScene::~MainmenuScene()
{
}

void MainmenuScene::Update()
{
	StageNumber* stageNum = FindGameObject<StageNumber>();

	if (CheckHitKey(KEY_INPUT_0)) {
		random_device rnd;
		mt19937 mt(rnd());
		uniform_int_distribution<>rand100(1, 4);
		rand = rand100(mt);

		if (rand == 1) {
			// 処理 1
			stageNum->stagenum = 1;
			SceneManager::ChangeScene("PlayScene");
		}
		else if (rand == 2) {
			// 処理 2
			stageNum->stagenum = 2;
			SceneManager::ChangeScene("PlayScene");

		}
		else if (rand == 3) {
			// 処理 3
			stageNum->stagenum = 3;
			SceneManager::ChangeScene("PlayScene");

		}
		else if (rand == 4) {
			// 処理 4
			stageNum->stagenum = 4;
			SceneManager::ChangeScene("PlayScene");

		}
	}
	if (CheckHitKey(KEY_INPUT_1)) {
		stageNum->stagenum = 1;
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		stageNum->stagenum = 2;
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		stageNum->stagenum = 3;
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_4)) {
		stageNum->stagenum = 4;
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
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
