#pragma once
#include "../Library/GameObject.h"

class Nyoki : public GameObject
{
public:
	Nyoki(int px, int py);
	~Nyoki();
	void Update() override;
	void Draw() override;
private:
	float x, y;
	int nyokiImage;
	int size;
	int move;
	int count;
	
};