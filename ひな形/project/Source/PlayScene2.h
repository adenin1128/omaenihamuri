#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
///</summary>
class PlayScene2 : public SceneBase
{
public:
	PlayScene2();
	~PlayScene2();
	void Update() override;
	void Draw() override;
};
