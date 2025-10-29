#include "trap.h"
#include "field.h"
#include "Player.h"

struct Vector2D {
    double x;
    double y;
};
//���_�̒�`(�x�N�g���Ɠ���)
#define Vertex2D Vector2D

//�x�N�g�������Z(a-b)
VECTOR2 sub_vector(const VECTOR2& a, const VECTOR2& b)
{
    VECTOR2 ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

// �O�p�`�Ɠ_�̓����蔻��(2D�̏ꍇ)
// �߂�l    0:�O�p�`�̓����ɓ_������    1:�O�p�`�̊O���ɓ_������
int hittest_point_polygon_2d(VECTOR2 A, VECTOR2 B, VECTOR2 C, VECTOR2 P) {

    //����͊O�Ƃ݂Ȃ��܂��B
    //ABC���O�p�`���ǂ����̃`�F�b�N�͏ȗ�...

    VECTOR2 AB = sub_vector(B, A);
    VECTOR2 BP = sub_vector(P, B);

    VECTOR2 BC = sub_vector(C, B);
    VECTOR2 CP = sub_vector(P, C);

    VECTOR2 CA = sub_vector(A, C);
    VECTOR2 AP = sub_vector(P, A);

    //�O��    Z���������v�Z����΂悢�ł�
    double c1 = AB.x * BP.y - AB.y * BP.x;
    double c2 = BC.x * CP.y - BC.y * CP.x;
    double c3 = CA.x * AP.y - CA.y * AP.x;

    if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) {
        //�O�p�`�̓����ɓ_������
        return 0;
    }

    //�O�p�`�̊O���ɓ_������
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
        DrawFormatString(x - 100, y - 100, GetColor(255, 0, 0), "�Q�[���I�[�o�[");
    }
}
