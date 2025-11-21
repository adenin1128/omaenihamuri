#include "PlayScene0.h"
#include "DxLib.h"
#include "field.h"
#include "Player.h"
#include "../Source/Mainmenu.h"


PlayScene0::PlayScene0()
{
	MainmenuScene* main = FindGameObject<MainmenuScene>();
	stagenum = main->GetStageNum();
	new Field(stagenum);
}

PlayScene0::~PlayScene0()
{
}

void PlayScene0::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("MENU");
	}
}

void PlayScene0::Draw()
{

}