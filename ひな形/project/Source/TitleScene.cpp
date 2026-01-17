#include "TitleScene.h"
#include "Trigger.h"
#include "Player.h"
#include "field.h"
#include "Fader.h"
#include "HAIKEI.h"
#include "Screen.h"
#include "Timer.h"

TitleScene::TitleScene()
{
    titleimage = LoadGraph("data/image/OMAENOLOGO.png");
    new HAIKEI(2);

    // --- BGMの読み込みと再生を追加 ---
    // 第2引数の DX_PLAYTYPE_LOOP でバックグラウンドでのループ再生になります
    bgmHandle = LoadSoundMem("data/sound/TITLE.mp3"); // パスは適宜調整してください
    PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);

    thikathika = 0;
    posY = -500.0f;     // 画面より上の位置からスタート
    isArrived = false;  // 最初は未到着

    Fader* fader = FindGameObject<Fader>();
    fader->FadeIn(0.1f);
    Timer* timer = FindGameObject<Timer>();
    timer->ResetDeathcount();
}

TitleScene::~TitleScene()
{
    // 音楽を止めてメモリから削除
    StopSoundMem(bgmHandle);
    DeleteSoundMem(bgmHandle);
    HAIKEI* h = FindGameObject<HAIKEI>();
    if (h) h->DestroyMe();
}

void TitleScene::Update()
{
    StageNumber* sn = FindGameObject<StageNumber>();
    if (sn->noSound == true) {
        ChangeVolumeSoundMem(0, bgmHandle);
    }
    else {
        ChangeVolumeSoundMem(255, bgmHandle);
    }
    // --- 1. タイトル画像を降ろす処理 ---
    if (!isArrived) {
        // イージング（滑らかに止まる）
        float speed = (targetY - posY) * 0.05f;
        posY += speed;

        // 目標地点に十分近づいたら固定
        if (targetY - posY < 1.0f) {
            posY = targetY;
            isArrived = true;
        }
    }

    // --- 2. 到着後の点滅カウンタ更新 ---
    if (isArrived) {
        thikathika++;
        if (thikathika >= 100) {
            thikathika = 0;
        }
    }

    // --- 3. 入力処理 ---
    if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE)) {
        SceneManager::ChangeScene("MENU");
    }
    if (Screen::DEVELOPER_MODE == TRUE || CheckHitKey(KEY_INPUT_RIGHT)) {
        if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            SceneManager::Exit();
        }
    }
}

void TitleScene::Draw()
{
    // タイトル画像の描画（現在のposYを使用）
    DrawRotaGraph(1920 / 2, (int)posY, 7, 0, titleimage, 1);

    // --- 4. 到着済み、かつ点滅タイミングの時だけ文字を表示 ---
    if (isArrived) {
        if (thikathika < 60) {
            SetFontSize(20); // フォントサイズの設定
            DrawExtendFormatStringToHandle(1920 / 3 - 230, 820, 4, 4,
                GetColor(0, 0, 0), GetDefaultFontHandle(), "PRESS THE SPACE KEY TO START");
        }
    }

    if (Screen::DEVELOPER_MODE == TRUE) {
    // デバッグ情報やシステム情報の表示
    extern const char* Version();
    DrawString(0, 20, Version(), GetColor(255, 255, 255));
    DrawString(0, 0, "TITLE SCENE", GetColor(255, 255, 255));
    DrawFormatString(100, 100, GetColor(255, 255, 255), "FPS:%4.1f", 1.0f / Time::DeltaTime());

    // ガイド用
    DrawString(100, 400, "Push Space To Menu", GetColor(0, 0, 0));
}
}