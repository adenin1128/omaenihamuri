#pragma once
#include "../Library/GameObject.h"

class respawn :public GameObject
{
public:
	respawn(int px, int py);
	~respawn();
	void Update() override;
	void Draw() override;
private:
	int hataImage;
	int x, y;
};