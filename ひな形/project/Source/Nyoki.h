#pragma once
#include "../Library/GameObject.h"

class Nyoki : public GameObject
{
public:
	Nyoki(int px, int py);
	~Nyoki();
	void Update() override;
	void Draw() override;
	
	int HitCheckDown(int px, int py);
	int HitCheckLeft(int px, int py);
	int HitCheckUp(int px, int py);
	int HitCheckRight(int px, int py);

private:
	float nx, ny;
	int nyokiImage;
	int size;
	int move;
	int count;
	int loop;
	bool a;
};