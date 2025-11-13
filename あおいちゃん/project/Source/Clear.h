#pragma once
#include "../Library/GameObject.h"

class Clear : public GameObject
{
public:
	Clear();
	~Clear();
	void Update() override;
	void Draw() override;
private:
	int hImage;
};
