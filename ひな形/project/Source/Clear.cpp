#include "Clear.h"
#include "field.h"
#include "Gameover.h"
#include "Player.h"
#include "Timer.h"
#include "StageNumber.h"

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
	StageNumber* sn = FindGameObject<StageNumber>();
	timer->GetTime();
	if (player->GetState() != STATE_CLEAR||sn->Clear == true) {
		if (CheckHitKey(KEY_INPUT_R)) {
			SceneManager::ChangeScene("RESULT");
		}
	}
}

void Clear::Draw()
{
	DrawRotaGraph(990, 540, 0.5, 0., clearImage, TRUE, FALSE);
}