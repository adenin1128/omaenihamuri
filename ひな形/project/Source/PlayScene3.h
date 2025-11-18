#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
///</summary>
class PlayScene3 : public SceneBase
{
public:
	PlayScene3();
	~PlayScene3();
	void Update() override;
	void Draw() override;
};
