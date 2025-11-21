#pragma once
#include "../Library/GameObject.h"

class downdraft : public GameObject
{
public:
	downdraft(int px, int py);
	~downdraft();
	void Update() override;
	void Draw() override;
	bool IsDown(int px, int py);
private:
	float x, y;
	int windImage;
	int downhit;
	int size;
	int Vy;
};