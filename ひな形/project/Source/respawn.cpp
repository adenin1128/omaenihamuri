#include "respawn.h"
#include "Player.h"
#include "field.h"

respawn::respawn(int px, int py)
{
	hataImage = LoadGraph("data/image/hata.png");
	//// --- 追加: サウンドの読み込み ---
	//seHandle = LoadSoundMem("data/sound/TYUKANN.mp3"); // パスは環境に合わせて調整してください
	x = px;
	y = py;
}

respawn::~respawn()
{
	DeleteGraph(hataImage);
	//// --- 追加: サウンドのメモリ解放 ---
	//DeleteSoundMem(seHandle);
}
a
void respawn::Update()
{
	Player* player = FindGameObject<Player>();
	VECTOR2 pPos = player->GetPosition();
	pPos.x += 32;
	pPos.y += 32;

	int diffX = pPos.x - x;
	diffX = diffX * diffX;
	int diffY = pPos.y - y;
	diffY = diffY * diffY;
	int diff = sqrtf(diffX + diffY);
	if (player->GetState() == STATE_NORMAL) {
		if (diff < 64) {
			//// --- 追加: サウンドの再生 ---
			//PlaySoundMem(seHandle, DX_PLAYTYPE_BACK);
			Field* field = FindGameObject<Field>();
			field->ChangeRespawnPoint(x / 64, y / 64);
			DestroyMe();
		}
	}
}

void respawn::Draw()
{
	DrawGraph(x, y, hataImage, true);
}