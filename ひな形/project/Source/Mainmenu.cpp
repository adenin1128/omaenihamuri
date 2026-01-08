#include "Mainmenu.h"
#include <random>
#include "DxLib.h"
#include <iostream>
#include "field.h"
#include "StageNumber.h"
#include "Fader.h"
#include "HAIKEI.h"
#include "Timer.h"
#include "Screen.h"
#include <assert.h>

using namespace std;

//extern const char* Version();
int medaruGraphs[3];
int fireGraphs[15];

MainmenuScene::MainmenuScene()
{
	timer = 0;
	rand = 0;
	medatimer = 0;
	migi = false;
	hidari = false;
	new HAIKEI(3);
	Fader* fader = FindGameObject<Fader>();
	fader->FadeIn(0.1f);
	nanidobarimage = LoadGraph("data/image/nanidobar.png");
	nanidotyoimage = LoadGraph("data/image/nanidotyo.png");
	//medaruimage = LoadGraph("data/image/medaru.png");
	migiimage = LoadGraph("data/image/migi.png");
	hidariimage = LoadGraph("data/image/hidari.png");
	setumeiimage = LoadGraph("data/image/explanation.png");
	headimage = LoadGraph("data/image/omaehead.png");
	douimage = LoadGraph("data/image/omaedou.png");
	asiimage = LoadGraph("data/image/omaeasi.png");
	teimage = LoadGraph("data/image/omaete.png");
	okoteimage = LoadGraph("data/image/omaete2.png");
	mukiimage = LoadGraph("data/image/muki.png");
	medaruimage = LoadGraph("data/image/medaru.png");
	ganmenimage = LoadGraph("data/image/ganmen.png");
	kantanimage = LoadGraph("data/image/kantan.png");
	muzuiimage = LoadGraph("data/image/2muzui.png");
	fireimage = LoadGraph("data/image/fire.png");
	okoimage = LoadGraph("data/image/okohead.png");
	gekimuzuimage = LoadGraph("data/image/gekimuzu.png");
	A = LoadGraph("data/image/A.png");
	D = LoadGraph("data/image/D.png");
	LoadDivGraph("data/image/medaru.png", 3, 3, 1, 128, 128, medaruGraphs);
	fireimage = LoadGraph("data/image/ONFIRE.png");
	LoadDivGraph("data/image/ONFIRE.png", 15, 15, 1, 1980, 1080, fireGraphs);
	assert(fireimage > 0);
	state = STAGE1;
	ue = false;
	Timer* tm = FindGameObject<Timer>();
	tm->ResetDeathcount();
	doux = 1500;
	douy = 450;
	asix = 1500;
	asiy = 450;
	headx = 1500;
	heady = 440;
	tex = 1500;
	tey = 450;
	frame = 0;
}

MainmenuScene::~MainmenuScene()
{
	HAIKEI* h = FindGameObject<HAIKEI>();
	h->DestroyMe();
}

void MainmenuScene::Update()
{
	if (ue == false) {
		heady += 0.5;
		douy += 0.3;
		asiy += 0.2;
		tey += 0.4;
		if (heady > 460&&douy> 460&&asiy >460&&tey >460) {
			ue = true;
		}
	}
	else if (ue == true) {
		heady -= 0.5;
		douy -= 0.3;
		asiy -= 0.2;
		tey -= 0.4;
		if (heady < 440 && douy> 440 && asiy > 440&&tey >440) {
			ue = false;
		}
	}

	if (state == STAGE1) {
		medarustage = 1;
		migi = false;
		hidari = false;
		medatimer++;
		if (medatimer > 10) {
			if (CheckHitKey(KEY_INPUT_D)) {
				state = STAGE2;
				medatimer = 0;
				migi = true;
			}
			if (CheckHitKey(KEY_INPUT_A)) {
				state = STAGE3;
				medatimer = 0;	
				hidari = true;
			}
		}
	}
	else if (state == STAGE2) {
		medarustage = 2;
		migi = false;
        hidari = false;
		medatimer++;
		if (medatimer > 10) {
			if (CheckHitKey(KEY_INPUT_D)) {
				state = STAGE3;
				medatimer = 0;
				migi = true;
			}
			if (CheckHitKey(KEY_INPUT_A)) {
				state = STAGE1;
				medatimer = 0;
				hidari = true;
			}
		}
	}
	else if (state == STAGE3) {
		medarustage = 3;
		migi = false;
        hidari = false;
		medatimer++;
		if (medatimer > 10) {
			if (CheckHitKey(KEY_INPUT_D)) {
				state = STAGE1;
				medatimer = 0;
				migi = true;
			}
			if (CheckHitKey(KEY_INPUT_A)) {
				state = STAGE2;
				medatimer = 0;
				hidari = true;
			}
		}
	}

		StageNumber* stageNum = FindGameObject<StageNumber>();
		Field* f = FindGameObject<Field>();
		Fader* fader = FindGameObject<Fader>();
		Timer* timer = FindGameObject<Timer>();
		random_device rnd;
		mt19937 mt(rnd());
		uniform_int_distribution<>rand100(1, 4);
		rand = rand100(mt);

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (medarustage == 1) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 1;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		else if (medarustage == 2) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 2;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		else if (medarustage == 3) {
		if (rand == 3) {
		// 処理 3
		fader->FadeOut(0.1f);
		stageNum->stagenum = 3;
		timer->StartTimer();
		SceneManager::ChangeScene("PlayScene");

				}
		else if (rand == 4) {
		// 処理 4
		fader->FadeOut(0.1f);
		stageNum->stagenum = 4;
		timer->StartTimer();
		SceneManager::ChangeScene("PlayScene");
				}
		}
	}
		if (CheckHitKey(KEY_INPUT_1)) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 1;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		//if (f->GetGateHit() == 21) {
		////	fader->FadeOut(0.1f);
		////	stageNum->stagenum = 1;
		////	timer->StartTimer();
		////	SceneManager::ChangeScene("PlayScene");
		////}
		if (CheckHitKey(KEY_INPUT_2)) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 2;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		////if (f->GetGateHit() == 22) {
		////	fader->FadeOut(0.1f);
		////	stageNum->stagenum = 3;
		////	timer->StartTimer();
		////	SceneManager::ChangeScene("PlayScene");
		////}
		if (CheckHitKey(KEY_INPUT_3)) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 3;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		if (CheckHitKey(KEY_INPUT_4)) {
			fader->FadeOut(0.1f);
			stageNum->stagenum = 4;
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		if (CheckHitKey(KEY_INPUT_RETURN)) {
			fader->FadeOut(0.1f);
			timer->StartTimer();
			SceneManager::ChangeScene("PlayScene");
		}
		if (CheckHitKey(KEY_INPUT_O)) {
			fader->FadeOut(0.1f);
			SceneManager::ChangeScene("TITLE");
		}
		if (Screen::DEVELOPER_MODE == TRUE || CheckHitKey(KEY_INPUT_RIGHT)) {
			if (CheckHitKey(KEY_INPUT_ESCAPE)) {
				fader->FadeOut(0.1f);
				SceneManager::Exit();
			}
		}

}

void MainmenuScene::Draw()
{
	//DrawRotaGraph(1920/2, 650, 1, 0, fireimage, TRUE);

	{
		timer++;
		if (timer % 7 == 0) {
			frame++;

			if (frame >= 15) {
				frame = 0;
			}
		}
			//DrawRotaGraph(Screen::WIDTH / 2, Screen::HEIGHT / 2+100, 1, 0, fireGraphs[frame], TRUE, FALSE);
			DrawRotaGraph(1500, 630, 0.25, 0, fireGraphs[frame], TRUE, FALSE);
	}

	if(state == STAGE1)
	{
		DrawRotaGraph(400, 300, 0.5, 0, kantanimage, TRUE);
	}
	else if (state == STAGE2)
	{
		DrawRotaGraph(400, 300, 0.5, 0, muzuiimage, TRUE);
	}
	else if (state == STAGE3)
	{
		DrawRotaGraph(400, 300, 0.5, 0, gekimuzuimage, TRUE);
	}


	DrawRotaGraph(asix, asiy, 5.5, 0, asiimage, TRUE);
	DrawRotaGraph(doux, douy, 5.5, 0, douimage, TRUE);
	if (state == STAGE3) {
		DrawRotaGraph(tex, tey, 0.91, 0, mukiimage, TRUE);
	}
	else if (state == STAGE2) {
		DrawRotaGraph(tex, tey+30, 5.5, 0, okoteimage, TRUE);
	}
	else if (state == STAGE1) {
		DrawRotaGraph(tex, tey + 30, 5.5, 0, teimage, TRUE);
	}
	if (state == STAGE3) {
		DrawRotaGraph(headx, heady-120, /*0.174*/0.14, 0, ganmenimage, TRUE);
	}
	if(state == STAGE2){
	DrawRotaGraph(headx, heady, 5.5, 0, okoimage, TRUE);
    }
	if (state == STAGE1) {
		DrawRotaGraph(headx, heady, 5.5, 0, headimage, TRUE);
	}
	DrawRotaGraph(450, 100, 7, 0, nanidobarimage, TRUE);
	DrawRotaGraph(450, 100, 3, 0, nanidotyoimage, TRUE);
	DrawRotaGraph(960, 900, 7.5, 0, setumeiimage, TRUE);
	if (migi == true)
	{
		DrawRotaGraph(650, 550, 4, 0, migiimage, TRUE);
		DrawRotaGraph(750, 550, 3, 0, D, TRUE);
	}
	else if (migi == false)
	{
		DrawRotaGraph(650, 550, 3, 0, migiimage, TRUE);
		DrawRotaGraph(750, 550, 2, 0, D, TRUE);
	}

	if (hidari == true)
	{
		DrawRotaGraph(150, 550, 4, 0, hidariimage, TRUE);
		DrawRotaGraph(50, 550, 3, 0, A, TRUE);

	}else if (hidari == false)
	{
		DrawRotaGraph(150, 550, 3, 0, hidariimage, TRUE);
		DrawRotaGraph(50, 550, 2, 0, A, TRUE);
	}

	if (state == STAGE1)
		DrawRotaGraph(400, 550, 3, 0, medaruGraphs[0], TRUE);
	else if (state == STAGE2)
		DrawRotaGraph(400, 550, 3, 0, medaruGraphs[1], TRUE);
	else if (state == STAGE3)
	    DrawRotaGraph(400, 550, 3, 0, medaruGraphs[2], TRUE);


	if (state == STAGE1) {
		DrawExtendFormatStringToHandle(680, 850, 3, 3, GetColor(255, 255, 255), GetDefaultFontHandle(), "こんなの余裕だね！");
	}
	else if (state == STAGE2) {
		DrawExtendFormatStringToHandle(680, 850, 3, 3, GetColor(255, 255, 255), GetDefaultFontHandle(), "クリアできるのカナ！？");
	}
	else if (state == STAGE3) {
		DrawExtendFormatStringToHandle(680, 850, 3, 3, GetColor(255, 255, 255), GetDefaultFontHandle(), "お前には無理！！");
	}

	if (Screen::DEVELOPER_MODE == TRUE) {
		DrawString(100, 400, "stage1 press to 1 key ", GetColor(255, 255, 255));
		DrawString(100, 420, "stage2 press to 2 key", GetColor(255, 255, 255));
		DrawString(100, 440, "stage3 press to 3 key", GetColor(255, 255, 255));
		DrawString(100, 490, "stage4 press to 4 key", GetColor(255, 255, 255));
	}
}
