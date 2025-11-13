#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class MainmenuScene : public SceneBase
{
public:
	MainmenuScene();
	~MainmenuScene();
	void Update() override;
	void Draw() override;
	int menuImage;
};

