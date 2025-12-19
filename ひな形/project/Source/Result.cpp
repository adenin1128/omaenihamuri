#include "Result.h"

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
		SceneManager::ChangeScene("TITEL");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void Result::Draw()
{
	DrawGraph(0, 0, TyImage, TRUE);
}