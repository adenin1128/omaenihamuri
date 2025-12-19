#pragma once
#include "../Library/SceneBase.h"

class Result : public SceneBase
{
public:
	Result();
	~Result();
	void Update() override;
	void Draw() override;
private:
	int TyImage;
};