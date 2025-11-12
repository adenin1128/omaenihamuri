#pragma once
#include "../Library/GameObject.h"
#include <vector>
class trap : public GameObject {
public:
	trap(int px, int py, int i, int d);
	~trap();
	void Update() override;
	void Draw() override;
	void Active();
	enum Type {
		Up,
		Up2,
		Right,
		Up3,
		Up4,
		Up5,
		Up6,
		Up7,
		Up8,
		Down
	};
	enum Direction {
		TOP,
		RIGHT,
		UNDER,
		LEFT
	};
private:
	int hariImage;
	float x, y;
	float UP;
	float right;
	float right3;
	float UP3;
	bool isActive;     // ƒgƒ‰ƒbƒv‚ª”­“®‚µ‚½‚©
	bool isGameover;
	float kaiten;
	
	Type type;
	Direction dir;
	double rot;
	std::vector<VECTOR2> colliderPoints;
};
