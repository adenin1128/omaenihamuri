#include "BootScene.h"
#include "StageNumber.h"
#include "Fader.h"
#include "Timer.h"

BootScene::BootScene()
{
	new StageNumber(); // ステージ番号管理クラスのインスタンスを生成
	new Fader();
	new Timer();
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SetFontSize(60);
	SceneManager::ChangeScene("TITLE"); // 起動が終わったらTitleを表示
}

void BootScene::Draw()
{
}
