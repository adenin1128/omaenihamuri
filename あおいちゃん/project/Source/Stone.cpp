#include "Stone.h"
#include "Field.h"
#include "Screen.h"
#include "Bird.h"

Stone::Stone()
{
	hImage = LoadGraph("data/image/stone.png");
	x = 0;
	y = 0;
}

Stone::Stone(int sx, int sy,float vx, float vy)
{
	hImage = LoadGraph("data/image/stone.png");
	x = sx;
	y = sy;
	velocityX = vx;
	velocityY = vy;
}

Stone::~Stone()
{
}

void Stone::Update()
{
	x += velocityX;
	y += velocityY;
	//一個しかバードがないとき
	//Bird* b = FindGameObject<Bird>();//バードを探す
	//b->IsHit(x, y);//->アローで使う
	//たくさんバード
	auto birds = FindGameObjects<Bird>();
	for (auto b : birds) {
		if (b->IsHit(x, y)) {
			DestroyMe();
		}
	}

}

void Stone::Draw()
{
	Field* field = FindGameObject<Field>();
	int sc = field->GetScollX();
	DrawRectGraph(x - sc, y, 0, 0, 64, 64, hImage, 1);
}
