#include "TitleScene.h"
#include <DxLib.h>
#include "Screen.h"

int image;
const int CHR_SIZE = 64;
int coinImage;

TitleScene::TitleScene()
{
	image = LoadGraph("data/chara.png");
	coinImage = LoadGraph("data/item.png");
}

TitleScene::~TitleScene()
{
}

float a = 0; // TITLE SCENE�𓮂���
float x = 20; // �L�����N�^�[�𓮂���
float y = 50;
int pat = 4; // �A�j���[�V�����̃p�^�[��
int count = 0; // �A�j���[�V������x�点�邽��
const int DOWN = 0;
const int LEFT = 1;
const int UP = 2;
const int RIGHT = 3;
int dir = DOWN; // ����
const int STOP = 0;
const int WALK = 4;
int move = STOP;

float coinX = 0;
float coinY = 0;

int dispCount = 0; // 0���傫����΁ACOINGET�ƕ\������
int dispX; // �Q�b�g�̕\������ꏊ
int dispY;

int remainTime = 10*60;

//�Q�̈�����Ԃ��Aave()�����

int add(int a, int b)
{
	int c = a + b;
	return c;
}

float ave(int a, int b)
{
	float c = (float)(a + b) / 2;
	c = ((float)a + (float)b)/2;
	return c;
}

void GoRight(float spd)
{
	x += spd;
	if (x > Screen::WIDTH - CHR_SIZE) {
		x = Screen::WIDTH - CHR_SIZE;
	}
	dir = RIGHT;
	move = WALK;
}

void TitleScene::Update()
{
	if (remainTime > 0) {
		remainTime -= 1;
	}
	float speed = 3;
	if (remainTime > 0) {
		move = STOP;
		if (CheckHitKey(KEY_INPUT_D)) { // D�L�[���������̂ŁA�E�ɍs��
			GoRight(speed);
		}
		if (CheckHitKey(KEY_INPUT_A)) {
			x -= speed;
			if (x < 0) {
				x = 0;
			}
			dir = LEFT;
			move = WALK;
		}
		if (CheckHitKey(KEY_INPUT_W)) {
			y -= speed;
			if (y < 0) {
				y = 0;
			}
			dir = UP;
			move = WALK;
		}
		if (CheckHitKey(KEY_INPUT_S)) {
			y += speed;
			if (y > Screen::HEIGHT - CHR_SIZE) {
				y = Screen::HEIGHT - CHR_SIZE;
			}
			dir = DOWN;
			move = WALK;
		}
	}
	count += 1;
	if (count >= 10) {
		count = 0;
		pat = (pat + 1) % 4 + move;
	}

	float dx = coinX - x; // X���W�̍�
	float dy = coinY - y; // Y���W�̍�
	float d = sqrt(dx*dx + dy*dy); // ���������߂�
	if (d<64) {
		dispCount = 60;
		dispX = coinX;
		dispY = coinY;
		// rand()�͗���(0�`32767�̂ǂꂩ���擾)
		coinX = rand() % (Screen::WIDTH - CHR_SIZE);
		coinY = rand() % (Screen::HEIGHT - CHR_SIZE);
	}
	dispCount -= 1;
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	int x = add(3, 4);

	float a = ave(3, 5);

	DrawFormatString(400, 200, GetColor(255,255,255),
		"%d", x);
	DrawFormatString(500, 200, GetColor(255, 255, 255),
		"%f", a);
	// a�̒l��\������
	DrawString(0, 0, "TITLE SCENE", GetColor(255, 255, 255), 0);
	DrawString(200, 400, "Push [P]Key To Play", GetColor(255, 255, 255));

	//	DrawGraph(0, 0, image, 1);
	DrawRectGraph(x, y, CHR_SIZE * pat, CHR_SIZE * dir,
		CHR_SIZE, CHR_SIZE, image, 1);

	DrawRectGraph(coinX, coinY, CHR_SIZE * 1, CHR_SIZE * 0,
		CHR_SIZE, CHR_SIZE, coinImage, 1);


	DrawFormatString(0, 100, GetColor(255,255,255),
		"X=%f Y=%f", x, y);

	if (dispCount > 0) {
		DrawFormatString(dispX, dispY, GetColor(255, 255, 255),
			"�R�C���Q�b�g�I");
	}
	int second = remainTime/60;

	int nowSize = GetFontSize(); // ���̃t�H���g�T�C�Y
	SetFontSize(100); // �T�C�Y��ς��ĕ\��
	DrawFormatString(600, 0, GetColor(255, 255, 255),
		"TIME=%2d", second);
	SetFontSize(nowSize);

}
