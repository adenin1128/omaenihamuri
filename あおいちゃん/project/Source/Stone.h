#pragma once
#include "../Library/GameObject.h"

class Stone : public GameObject
{
public:
	Stone();
	Stone(int sx, int sy, float vx, float vy);
	~Stone();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	float x, y;
	float velocityX, velocityY;
};