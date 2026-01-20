#pragma once
#include "../Library/GameObject.h"

class StageNumber : public GameObject
{
public:
	StageNumber();
	void Update() override;
	void Draw() override;
	int stagenum;
	bool noDeath;
	bool Clear;
	bool noSound;
};