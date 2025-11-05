#pragma once
#include "../Library/GameObject.h"

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
	enum Type {
		Down
	};
	Type type;
};