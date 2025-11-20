#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
///</summary>
class PlayScene4 : public SceneBase
{
public:
	PlayScene4();
	~PlayScene4();
	void Update() override;
	void Draw() override;
};
