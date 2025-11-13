#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
///</summary>
class PlayScene1 : public SceneBase
{
public:
	PlayScene1();
	~PlayScene1();
	void Update() override;
	void Draw() override;
};
