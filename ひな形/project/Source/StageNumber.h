#pragma once
#include "../Library/GameObject.h"

class StageNumber : public GameObject
{
public:
	StageNumber();
	void Draw() override;
	int stagenum;
};