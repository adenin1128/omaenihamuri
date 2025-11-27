#pragma once
#include "../Library/GameObject.h"

class Nyoki : public GameObject
{
public:
	Nyoki(int px, int py);
	~Nyoki();
	void Update() override;
	void Draw() override;
	void Reset();
	
	int HitCheckDown(int px, int py);
	int HitCheckLeft(int px, int py);
	int HitCheckUp(int px, int py);
	int HitCheckRight(int px, int py);

private:
	int resetX, resetY;
	float nx, ny;
	int nyokiImage;
	int size;
	int move;
	int count;
	int loop;
	bool a;
	int currentMoveX;
	int maxMoveX;
};