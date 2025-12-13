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
	Breath(int px, int py);
	~Breath();
	void Update() override;
	void Draw() override;
	buraState state;   //	breath‚Ìó‘ÔŠÇ—
	buraState GetState() const { return state; }
    void SetState(buraState s) { state = s; }
	Breath(int x, int y, int direction, int tx, int ty);
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
};