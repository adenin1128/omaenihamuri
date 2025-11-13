#include "TitleScene.h"

TitleScene::TitleScene()
{
	titleimage = LoadGraph("data/image/title.png");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("MENU");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit(); 
	}
}


void TitleScene::Draw()
{	
	DrawString(100, 400, "Push Space To Menu", GetColor(0, 0, 0));
	DrawGraph(0, 0, titleimage, 1);
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawFormatString(100, 100, GetColor(255,255,255), "%4.1f", 1.0f / Time::DeltaTime());

}
