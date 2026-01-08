#include "Result.h"
#include "Fader.h"
#include "Screen.h"
#include "Timer.h"
#include "field.h"

Result::Result()
{
	TyImage = LoadGraph("data/image/Ty.png");
	size = 4;

	Default = GetDefaultFontHandle();
}

Result::~Result()
{
	DeleteGraph(TyImage);
	Timer* timer = FindGameObject<Timer>();
	timer->ResetTimer();
}

void Result::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_O)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (Screen::DEVELOPER_MODE == TRUE || CheckHitKey(KEY_INPUT_RIGHT)) {
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			SceneManager::Exit();
		}
	}
}

void Result::Draw()
{
	Timer* timer = FindGameObject<Timer>();
	//DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(255, 255, 255),TRUE);
	DrawGraph(370, 240, TyImage, TRUE);
	DrawExtendFormatStringToHandle(550, 500, size, size, GetColor(255, 255, 255), Default, "死んだ回数　:　　%4d回", (timer->GetDeathCount()) - 1);
	DrawExtendFormatStringToHandle(550, 650, size, size, GetColor(255, 255, 255), Default, "クリア時間　:　　%.2f秒", (timer->GetTime()) / 60);
	DrawExtendFormatStringToHandle(680, 850, size - 0.5, size - 0.5, GetColor(255, 255, 255), Default, "Press SPACE to Title");

}