#pragma once
#include "../Library/GameObject.h"
#include <vector>
class trap : public GameObject {
public:
	trap(int px, int py, int i, int d, int vx, int vy);
	~trap();
	void Update() override;
	void Draw() override;
	void Active();
	void Reset();
	enum Direction {
		TOP,  //0
		RIGHT,//1
		UNDER,//2
		LEFT  //3
	};
private:
	int resetPx;
	int resetPy;
	int resetI;
	int resetD;
	int resetTx;
	int resetTy;
	int hariImage;
	float x, y;
	
	bool isActive;// ƒgƒ‰ƒbƒv‚ª”­“®‚µ‚½‚©
	bool isGameover;
	
	float vx, vy;
	Direction dir;
	double rot;
	std::vector<VECTOR2> colliderPoints;
};
