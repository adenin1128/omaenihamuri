#pragma once
#include "../Library/GameObject.h"

enum MoveFloorState {
	STATE_A,    // 30‚©‚ç31‚ÖˆÚ“®
	STATE_B,    // 31‚©‚ç32‚ÖˆÚ“®
	STATE_C     // 32‚©‚ç31‚ÖˆÚ“®
};

class MoveFloor : public GameObject {
public:
	MoveFloor(int px, int py);
	~MoveFloor();
	void Update() override;
	void Draw() override;


	MoveFloorState state;
	MoveFloorState GetState() const { return state; }
	void SetState(MoveFloorState s) { state = s; }
	void SetMoveB() {
		state = STATE_B;
	}
	void SetMoveC() {
		state = STATE_C;
	}

private:
	float x, y;
	float RightSpeed;
	float LeftSpeed;
	int fImage;
	float MaxMoveFloor;
	float currentMoveFloor;
};
