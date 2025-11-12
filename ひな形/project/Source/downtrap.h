#pragma once
#include "../Library/GameObject.h"
#include <vector>
class downtrap : public GameObject {
public:
	downtrap(int px, int py, int i);
	~downtrap();
	void Update() override;
	void Draw() override;
	void Active();
private:
	int harisitaImage;
	float x, y;
	float UP;
	bool isActive;     // ƒgƒ‰ƒbƒv‚ª”­“®‚µ‚½‚©
	bool isGameover;
	float kaiten;
	enum MoveType {
		Down
	};
	MoveType type;
	enum Direction {
		Top,
		Right,
		Under,
		Left
	};
	Direction dir;
	double rot;
	std::vector<VECTOR2> colliderPoints;
};