#include "PlayScene.h"
#include "field.h"
#include "StageNumber.h"
#include "HAIKEI.h"
#include "Fader.h"

PlayScene::PlayScene()
{
	StageNumber* stagenum = FindGameObject< StageNumber >();
	int sn = stagenum->stagenum;
	new Field(sn);
	new HAIKEI();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_M)) {
		SceneManager::ChangeScene("MENU");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}