#include "PlayScene1.h"
#include "DxLib.h"
#include "field.h"
#include "Player.h"


PlayScene1::PlayScene1()
{
	new Field(1);
}

PlayScene1::~PlayScene1()
{
}

void PlayScene1::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void PlayScene1::Draw()
{

}
