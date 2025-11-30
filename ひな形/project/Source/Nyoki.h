#pragma once
#include "../Library/GameObject.h"

enum NyokiState {
	STATE_NEW,   //NyokiをNewして4つブロック出るまで
	STATE_MOVE1,
	STATE_MOVE2,
	STATE_MOVE3,
	STATE_STOP
};

class Nyoki : public GameObject
{
public:
	Nyoki(int px, int py);
	~Nyoki();
	void Update() override;
	void Draw() override;
	void Reset();
	
	int HitCheckDown(int px, int py);
	int HitCheckLeft(int px, int py);
	int HitCheckUp(int px, int py);
	int HitCheckRight(int px, int py);

	NyokiState state;
	void SetMOVE1() { STATE_MOVE1; }
	void SetMOVE2() { STATE_MOVE2; }
	void SetMOVE3() { STATE_MOVE3; }
	void SetSTOP() { STATE_STOP; }
	NyokiState GetState() const { return state; }

	void MoveOneStep(float dir); // dir: +1 右 / -1 左


private:
	int resetX, resetY;
	float nx, ny;
	int nyokiImage;
	int size;
	int move;
	int count;
	int loop;
	bool a;

	float currentMoveX;    //進んだ距離
	float maxMoveX;        //最大距離
	float nyokiSpeed;      //移動スピード
};