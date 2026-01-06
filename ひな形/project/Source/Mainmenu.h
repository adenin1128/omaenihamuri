#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
enum medaruState {
	STAGE1, 
	STAGE2,
	STAGE3,
};
class MainmenuScene : public SceneBase
{
public:
	MainmenuScene();
	~MainmenuScene();
	void Update() override;
	void Draw() override;
	int menuImage;
	int GetStageNum() { return rand; }
	medaruState state;   //	breathの状態管理
	medaruState GetState() const { return state; }
	void SetState(medaruState s) { state = s; }

private:
	int rand;
	int ganmenimage;
	int kantanimage;
	int fireimage;
	int nanidobarimage;
	int nanidotyoimage;
	int medaruimage;
	int migiimage;
	int hidariimage;
	int setumeiimage;
	int headimage;
	int douimage;
	int asiimage;
	int teimage;
	int mukiimage;
	int muzuiimage;
	int gekimuzuimage;
	int okoimage;
	int okoteimage;
	int medarustage;
	int medatimer;
	int A;
	int D;
	bool migi;
	bool hidari;
	float headx;
	float heady;
	float doux;
	float douy;
	float asix;
	float asiy;
	float tex;
	float tey;
	bool ue;
	int randy1;
	int randy2;
	int timer;
	int frame;
};

