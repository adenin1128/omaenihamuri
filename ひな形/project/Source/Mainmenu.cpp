#include "Mainmenu.h"
#include <random>
using namespace std;

MainmenuScene::MainmenuScene()
{
	menuImage = LoadGraph("data/image/menu.png"); // メニュー用の画像いつか用意する
	rand = 0;
}

MainmenuScene::~MainmenuScene()
{
}

void MainmenuScene::Update()
{
	
	if (CheckHitKey(KEY_INPUT_0)) {
		random_device rnd;
		mt19937 mt(rnd());
		uniform_int_distribution<>rand100(1, 4);
		rand = rand100(mt);
		SceneManager::ChangeScene("Play0");
	}
	if (CheckHitKey(KEY_INPUT_1)) {
		SceneManager::ChangeScene("PLAY1");
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		SceneManager::ChangeScene("PLAY2");
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		SceneManager::ChangeScene("PLAY3");
	}
	if (CheckHitKey(KEY_INPUT_4)) {
		SceneManager::ChangeScene("PLAY4");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void MainmenuScene::Draw()
{
	DrawRectGraph(0, 0, 0, 0, 1920, 1080, menuImage, 1);
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255, 255, 255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255, 255, 255));
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%4.1f", 1.0f / Time::DeltaTime());
	DrawString(100, 400, "一応一旦1でステージ１だお\n2でステージ２だお", GetColor(255, 255, 255));
	DrawString(100, 440, "ステージ3も追加したお", GetColor(255, 255, 255));
	DrawString(100, 490, "魂のステージ4をご照覧あれ", GetColor(255, 255, 255));
}
