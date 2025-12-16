#pragma once
#include "../Library/GameObject.h"
#include "BOAAAA.h"

class Boaaa;

enum buraState {
	STATE_START, // ‹N“®
	STATE_GO,//”­Ë
	STATE_FIN//–Œã
};
class Breath : public GameObject {
public:
	Breath(int px, int py, int i, int d, int tx, int ty);
	~Breath();
	void Update() override;
	void Draw() override;
	buraState state;   //	breath‚Ìó‘ÔŠÇ—
	buraState GetState() const { return state; }
    void SetState(buraState s) { state = s; }
	void Active();

private:
	int buraimage;
	int x, y;
	int frame2;
	int timer2;
	float angle;
	Boaaa* boaaa;
	int dir;     // Œü‚«
	int moveX;   // X•ûŒü‚Ì—ÍEˆÚ“®—Ê
	int moveY;   // Y•ûŒü‚Ì—ÍEˆÚ“®—Ê
	bool isActive;
	int timer;
	int startTime = 60; // breath‚ª”­Ë‚³‚ê‚é‚Ü‚Å‚ÌŠÔ
	int maxTime = 300;  // breath‚ª‘¶İ‚·‚éÅ‘åŠÔ

};