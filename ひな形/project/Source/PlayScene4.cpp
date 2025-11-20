#include "PlayScene4.h"
#include "DxLib.h"
#include "field.h"
#include "Player.h"


PlayScene4::PlayScene4()
{
	new Field(4);
}

PlayScene4::~PlayScene4()
{
}

void PlayScene4::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void PlayScene4::Draw()
{

}
