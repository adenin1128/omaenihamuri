#pragma once
#include "../Library/GameObject.h"

class HAIKEI : public GameObject {
public:
		HAIKEI();
		~HAIKEI();
		void Update() override;
		void Draw() override;
private:
	int hImage;
};