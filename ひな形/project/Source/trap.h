#pragma once
#include "../Library/GameObject.h"
#include <vector>
class trap : public GameObject {
public:
	trap(int px, int py, int i, int d);
	~trap();
	void Update() override;
	void Draw() override;
	void UPActive();
	void DOWNActive();
	void RIGHTActive();
	void LEFTActive();
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
		Down,
		Left
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
	bool isActive1;// トラップが発動したか
	bool isActive2;// トラップが発動したか
	bool isActive3;// トラップが発動したか
	bool isActive4;// トラップが発動したか
	bool isGameover;
	float kaiten;
	
	Type type;
	Direction dir;
	double rot;
	std::vector<VECTOR2> colliderPoints;
};
