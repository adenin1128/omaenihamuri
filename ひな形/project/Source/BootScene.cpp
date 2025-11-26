#include "BootScene.h"
#include "StageNumber.h"

BootScene::BootScene()
{
	new StageNumber(); // ステージ番号管理クラスのインスタンスを生成
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TITLE"); // 起動が終わったらTitleを表示
}

void BootScene::Draw()
{
}
