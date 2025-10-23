#include "field.h"
#include <vector>
#include "Player.h"
#include "trap.h"
using namespace std;

vector<vector<int>> maps = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    {1,0,0,0,0,0,0,0,3,0,3,0,3,0,3,0,0,4,0,0,0,0,0,0,4,0,0,0,0,1 },
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1 },
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1,1,1 },

};

Field::Field()
{
	haikeimage = LoadGraph("data/image/kabe.png");
	hImage = LoadGraph("data/image/bgchar.png");
	harimage = LoadGraph("data/image/hari.png");
	hataimage = LoadGraph("data/image/hata.png");
	x = 0;
	y = 1080-64;
	scrollX = 0; 
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 2) {
				new Player(x * 64, y * 64);//
			}
		}
	}
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 3) {
				new trap(x * 64, y  * 64);
			}
		}
	}
}

Field::~Field()
{
}

void Field::Update()
{
	//	scrollX += 1; //�����X�N���[���̏ꍇ
}

void Field::Draw()
{
	DrawRectGraph(0, 0, 0, 0, 1920, 1080, haikeimage, 1);
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 1) {
				DrawRectGraph(x * 64, y * 64  , 0, 32, 64, 64, hImage, 1);
			}
		}
	}
	/*for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 3) {
				DrawRectGraph(x *64,y * 64, 0, 0, 64, 64, harimage, 1);
			}
		}
	}*/
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			if (maps[y][x] == 4) {
				DrawRectGraph(x * 64, y * 64, 2, 2, 64, 64, hataimage, 1);
			}
		}
	}
}

int Field::HitCheckRight(int px, int py)
{
	int x = px / 64;
	int y = py/ 64;
	if (maps[y][x] == 1)
	{ // �������Ă� 
		return px % 64 + 1;
	}
	return 0;
}





int Field::HitCheckLeft(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (maps[y][x] == 1)
	{ // �������Ă� 
		return px % 64 - 64;
	}
	return 0;
}



int Field::HitCheckUp(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (maps[y][x] == 1)
		return 64 - py % 64;
	return 0;
}



int Field::HitCheckDown(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	if (maps[y][x] == 1)
		return py  % 64 + 1;
	return 0;
}

//������G��Ă���Ƃ��킮�킷��
//�ǉ��̃C���N���[�h�f�B���N�g�̐ݒ肪�킩��Ȃ�
//������ǉ��̃C���N���[�h�f�B���N�g�ɓ���Ȃ���
// Library�Ƃ��̃v���W�F�N�g�̃t�@�C���ifield.h�Ƃ��Ȃ񂩂����ɂ��邩��jDxLIb�̒ǉ����Ȃ��Ƃ̂��