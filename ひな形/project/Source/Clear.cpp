#include "Clear.h"
#include "field.h"
#include "Gameover.h"
#include "Player.h"
#include "Timer.h"

Clear::Clear()
{
	deathCount = 0;
	clearImage =  LoadGraph("data/image/culear.png");
	Timer* timer = FindGameObject<Timer>();
	timer->StopTimer();
	deathCount = timer->GetDeathCount();
}

Clear::~Clear()
{
	DeleteGraph(clearImage);
}

void Clear::Update()
{
	Player* player = FindGameObject<Player>();
	Timer* timer = FindGameObject<Timer>();
	timer->GetTime();
	if (player->GetState() != STATE_CLEAR) {
		if (CheckHitKey(KEY_INPUT_R)) {
			SceneManager::ChangeScene("RESULT");
		}
	}
}

void Clear::Draw()
{
	DrawRotaGraph(990, 540, 0.5, 0., clearImage, TRUE, FALSE);
	DrawExtendFormatStringToHandle(950, 600, 3.5, 3.5, GetColor(0, 0, 0), GetDefaultFontHandle(), "ïâÇØÇΩâÒêî %dâÒ", deathCount - 1);
	DrawExtendFormatStringToHandle(970, 750, 3, 3, GetColor(0, 0, 0), GetDefaultFontHandle(), "Press R to Menu");
	Timer* timer = FindGameObject<Timer>();
	DrawExtendFormatStringToHandle(900, 750, 1, 1, GetColor(0, 0, 0), GetDefaultFontHandle(), "Ç©Ç©Ç¡ÇΩéûä‘ %.3fïb", (timer->GetTime())/60);
}