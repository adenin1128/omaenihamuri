#pragma once
#include "../Library/GameObject.h"

class Result : public GameObject
{
public:
	Result();
	~Result();
	void Update() override;
	void Draw() override;
private:
	int TyImage;
};