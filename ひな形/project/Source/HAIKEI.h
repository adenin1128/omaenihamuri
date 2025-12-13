#pragma once
#include "../Library/GameObject.h"

class HAIKEI : public GameObject {
public:
	HAIKEI(int num);
	~HAIKEI();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	int dImage;
	int mImage;
	int number;
};