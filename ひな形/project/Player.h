#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject
{
public:
	Player();
	Player(float startX, float startY);
	~Player();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	float x, y;
	float velocity;
	bool onGround;
};





