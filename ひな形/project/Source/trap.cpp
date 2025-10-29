#include "trap.h"
#include "field.h"
#include "Player.h"

struct Vector2D {
    double x;
    double y;
};
//頂点の定義(ベクトルと同じ)
#define Vertex2D Vector2D

//ベクトル引き算(a-b)
VECTOR2 sub_vector(const VECTOR2& a, const VECTOR2& b)
{
    VECTOR2 ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

// 三角形と点の当たり判定(2Dの場合)
// 戻り値    0:三角形の内側に点がある    1:三角形の外側に点がある
int hittest_point_polygon_2d(VECTOR2 A, VECTOR2 B, VECTOR2 C, VECTOR2 P) {

    //線上は外とみなします。
    //ABCが三角形かどうかのチェックは省略...

    VECTOR2 AB = sub_vector(B, A);
    VECTOR2 BP = sub_vector(P, B);

    VECTOR2 BC = sub_vector(C, B);
    VECTOR2 CP = sub_vector(P, C);

    VECTOR2 CA = sub_vector(A, C);
    VECTOR2 AP = sub_vector(P, A);

    //外積    Z成分だけ計算すればよいです
    double c1 = AB.x * BP.y - AB.y * BP.x;
    double c2 = BC.x * CP.y - BC.y * CP.x;
    double c3 = CA.x * AP.y - CA.y * AP.x;

    if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) {
        //三角形の内側に点がある
        return 0;
    }

    //三角形の外側に点がある
    return 1;

}


trap::trap(int px,int py, int i)
{
	type = (Type)i;
	hariImage = LoadGraph("data/image/hari.png");
	x = px;
	y = py;
	UP = -1.0f;
	isActive = false;
	isGameover = false;
}

trap::~trap()
{
}

void trap::Update()
{
	VECTOR2 top = VECTOR2(x + 32, y);
	VECTOR2 underLeft = VECTOR2(x, y + 64);
	VECTOR2 underRight = VECTOR2(x + 64, y + 64);

	Player* player = FindGameObject<Player>();
    if (!hittest_point_polygon_2d(top, underLeft, underRight, player->GetColliderLeftTop()) ||
        !hittest_point_polygon_2d(top, underLeft, underRight, player->GetColliderLeftBottom()) ||
        !hittest_point_polygon_2d(top, underLeft, underRight, player->GetColliderRightTop()) ||
        !hittest_point_polygon_2d(top, underLeft, underRight, player->GetColliderRightBottom()))
    {
        SetFontSize(32);
		DrawString(10, 10, "Hit!", GetColor(255, 0, 0));
    }

	if (isActive == true) {
		switch (type) {
		case Up:
			y += UP;
			break;
		case Down:
			y -= UP;
			break;
		}
	}
}

void trap::Active() {
	isActive = true; 
}
void trap::Draw()
{
	DrawCircle(x + 32, y, 2, GetColor(255, 0, 0), true);
    DrawCircle(x, y + 64, 2, GetColor(255, 0, 0), true);
    DrawCircle(x + 64, y + 64, 2, GetColor(255, 0, 0), true);
	DrawGraph(x, y, hariImage, true);
    if (isGameover) {
        SetFontSize(64);
        DrawFormatString(x - 100, y - 100, GetColor(255, 0, 0), "ゲームオーバー");
    }
}
