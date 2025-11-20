#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
///</summary>
class PlayScene0 : public SceneBase
{
public:
	PlayScene0();
	~PlayScene0();
	void Update() override;
	void Draw() override;
private:
	int stagenum;
};

