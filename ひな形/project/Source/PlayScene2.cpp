#include "PlayScene2.h"
#include "DxLib.h"
#include "field.h"
#include "Player.h"


PlayScene2::PlayScene2()
{
	new Field(2);
}

PlayScene2::~PlayScene2()
{
}

void PlayScene2::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void PlayScene2::Draw()
{

}
