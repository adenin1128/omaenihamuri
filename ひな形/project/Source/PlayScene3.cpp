#include "PlayScene3.h"
#include "DxLib.h"
#include "field.h"
#include "Player.h"


PlayScene3::PlayScene3()
{
	new Field(3);
}

PlayScene3::~PlayScene3()
{
}

void PlayScene3::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("MENU");
	}
}

void PlayScene3::Draw()
{

}
