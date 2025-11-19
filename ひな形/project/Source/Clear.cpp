#include "Clear.h"
#include "field.h"
#include "Gameover.h"
#include "Player.h"

Clear::Clear()
{
	clearImage =  LoadGraph("data/image/culear.png");
	Field* field = FindGameObject<Field>();
	deathCount = field->GetDeathCount();

}

Clear::~Clear()
{    
}

void Clear::Update()
{
	Player* player = FindGameObject<Player>();
	if (player->GetState() != STATE_CLEAR) {
		if (CheckHitKey(KEY_INPUT_R)) {
			SceneManager::ChangeScene("MENU");
			DestroyMe();
		}
	}
}

void Clear::Draw()
{
	DrawRotaGraph(990, 540, 0.5, 0., clearImage, TRUE, FALSE);
	DrawExtendFormatStringToHandle(975, 600, 4, 4, GetColor(0, 0, 0), GetDefaultFontHandle(), "ïâÇØÇΩâÒêî %dâÒ", deathCount - 1);
	DrawExtendFormatStringToHandle(1000, 750, 3, 3, GetColor(0, 0, 0), GetDefaultFontHandle(), "Press R to Menu");
}