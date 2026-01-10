#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
	int titleimage;
private:
	float thikathika;
	float posY;         // 現在のタイトルのY座標
	bool isArrived;     // 定位置に到着したかどうかのフラグ
	const float targetY = 1080.0f / 2.0f - 128.0f; // 停止する目標座標
	int bgmHandle; // BGM用のハンドル
};
