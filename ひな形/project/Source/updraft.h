#pragma once
#include "../Library/GameObject.h"

class Updraft : public GameObject
{
public:
	Updraft(int px, int py);
	~Updraft();
	void Update() override;
	void Draw() override;
	bool IsUp(int px, int py);
private:
	float x, y;
	int windImage;
	int Uphit;
	int size;
	int Vy;
};