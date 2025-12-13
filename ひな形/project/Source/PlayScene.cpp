#include "PlayScene.h"
#include "field.h"
#include "StageNumber.h"
#include "HAIKEI.h"
#include "Fader.h"

PlayScene::PlayScene()
{
	StageNumber* stagenum = FindGameObject< StageNumber >();
	int sn = stagenum->stagenum;
	Fader* fader = FindGameObject<Fader>();
	fader->FadeIn(0.1f);
	new Field(sn);
	new HAIKEI();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	Fader* fader = FindGameObject<Fader>();
	if (CheckHitKey(KEY_INPUT_T)) {
		fader->FadeOut(0.1f);
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_M)) {
		fader->FadeOut(0.1f);
		SceneManager::ChangeScene("MENU");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		fader->FadeOut(0.1f);
		SceneManager::Exit();
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}