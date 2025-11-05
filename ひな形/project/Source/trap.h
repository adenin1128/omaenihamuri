#pragma once
#include "../Library/GameObject.h"

class trap : public GameObject {
public:
	trap(int px, int py, int i);
	~trap();
	void Update() override;
	void Draw() override;
	void Active();
private:
	int hariImage;
	float x, y;
	float UP;
	float right;
	float UP3;
	bool isActive;     // ƒgƒ‰ƒbƒv‚ª”­“®‚µ‚½‚©
	bool isGameover;
	float kaiten;
	enum Type {
		Up,
		Up2,
		Right,
		Up3,
		Up4,
		Up5,
		Up6,
		Down
	};
	Type type;
};
