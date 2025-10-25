#pragma once
#include "../Library/GameObject.h"

class trap : public GameObject {
public:
	trap(int px,int py, int i);
	~trap();
	void Update() override;
	void Draw() override;
	void Active();
private:
	int hariImage;
	float x, y;
	float UP;
	bool isActive;     // ƒgƒ‰ƒbƒv‚ª”­“®‚µ‚½‚©
	bool isGameover;
	enum Type {
		Up,
		Down,
		Right
	};
	Type type;
};
