#pragma once
#include "../Library/GameObject.h"


enum buraState {
	STATE_START, // ‹N“®
	STATE_GO,   //”­Ë 
};
class Breath : public GameObject {
public:
	Breath(int px, int py);
	~Breath();
	void Update() override;
	void Draw() override;
	buraState state;   //	breath‚Ìó‘ÔŠÇ—
	buraState GetState() const { return state; }

private:
	int buraimage;
	int x, y;
	int frame2;
	int timer2;
};