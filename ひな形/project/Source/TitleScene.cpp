#include "TitleScene.h"
#include "Trigger.h"
#include "Player.h"
#include "field.h"

TitleScene::TitleScene()
{
	titleimage = LoadGraph("data/image/OMAENOLOGO.png");
	new Field(0);
	thikathika = 0;
}

TitleScene::~TitleScene()    
{
}

void TitleScene::Update()
{
	thikathika += 1;
	if (KeyTrigger::CheckTrigger(KEY_INPUT_M)) {
		SceneManager::ChangeScene("MENU");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	if (thikathika < 60) {
		DrawExtendFormatStringToHandle(1920 / 3 - 198, 820, 4, 4, GetColor(0, 0, 0), GetDefaultFontHandle(), "PRESS THE M KEY TO START");

	}
	if (thikathika == 100)
	{
		thikathika = 0;
	}
	if (thikathika < 50)
	{
		SetFontSize(20);
		DrawExtendFormatStringToHandle(1920 / 3 - 198, 820, 4, 4, GetColor(0, 0, 0), GetDefaultFontHandle(), "PRESS THE M KEY TO START");
	}


}
	/*if (thikathika > 100) {
		DrawExtendFormatStringToHandle(850, 560, 4, 4, GetColor(0, 0, 0), GetDefaultFontHandle(), "PRESS THE M KEY TO START");
		thikathika = 0;
	}*/



void TitleScene::Draw()
{	
	DrawString(100, 400, "Push Space To Menu", GetColor(0, 0, 0));
	DrawRotaGraph(1920/2, 1080/2-128,7,0 ,titleimage, 1);
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawFormatString(100, 100, GetColor(255,255,255), "%4.1f", 1.0f / Time::DeltaTime());
	DrawFormatString(100, 30, GetColor(255, 255, 255), "%4.1f", thikathika);

}