#pragma once
#include "../Library/GameObject.h"

class Nyoki : public GameObject
{
public:
	Nyoki(int px, int py);
	~Nyoki();
	void Update() override;
	void Draw() override;
	bool IsNyoki(int px, int py);

private:
	float nx, ny;
	int nyokiImage;
	int size;
	int move;
	int count;
	int loop;
	int a;
};