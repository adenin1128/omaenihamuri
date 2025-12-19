#include "Result.h"
#include "Fader.h"
#include "Screen.h"
#include "Timer.h"
#include "field.h"

Result::Result()
{
	TyImage = LoadGraph("data/image/Ty.png");
}

Result::~Result()
{
}

void Result::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void Result::Draw()
{
	Timer* timer = FindGameObject<Timer>();
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(255, 255, 255),TRUE);
	DrawGraph(0, 0, TyImage, TRUE);
	DrawExtendFormatStringToHandle(950, 600, 3.5, 3.5, GetColor(0, 0, 0), GetDefaultFontHandle(), "•‰‚¯‚½‰ñ” %d‰ñ", (timer->GetDeathCount()) - 1);
	DrawExtendFormatStringToHandle(970, 750, 3, 3, GetColor(0, 0, 0), GetDefaultFontHandle(), "Press R to Menu");
	DrawExtendFormatStringToHandle(900, 750, 1, 1, GetColor(0, 0, 0), GetDefaultFontHandle(), "‚©‚©‚Á‚½ŽžŠÔ %.3f•b", (timer->GetTime()) / 60);

}