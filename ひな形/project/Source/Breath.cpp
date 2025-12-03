#include "Breath.h"
#include "BOAAAA.h"
#include <assert.h>

int buraGraphs[2];

Breath::Breath(int px, int py)
{
	buraimage= LoadGraph("data/image/BreathHead.png");
	LoadDivGraph("data/image/BreathHead.png", 2, 2, 1, 64, 64, buraGraphs);
	assert(buraimage > 0);
	state = STATE_START;
	x = px;
	y = py;
	frame2 = 0;
	timer2 = 0;
	angle = 0;//DX_PI_F/4:45‹
	                //DX_PI_F/2: 90‹
                    //DX_PI_F: 180‹
					//DX_PI_F*3/2 :270 
					//DX_PI_F*2 :360
	boaaa = nullptr;
}

Breath::~Breath()
{
	//DeleteGraph(buraimage);
}
void Breath::Update()
{
		if (state == STATE_START) {
			timer2++;
			{
				if (timer2 >= 120) {
					frame2 = 1;
					state = STATE_GO;
					boaaa = new Boaaa(x, y);
				}
			}
		}

		if (boaaa != nullptr) {
			boaaa->Update();//‚±‚ê‚È‚¢‚ÆƒNƒ‰ƒbƒVƒ…
		}
		//if (state == STATE_FIN) {
		//	DestroyMe();
		//}
}

void Breath::Draw()
{
	int frame2 = 0;
	if (state == STATE_START) {
		frame2 = 0;
	}

	if (state == STATE_GO) {
		frame2 = 1;
	}
	DrawRotaGraph(x * 64 + 32, y * 64 + 32, 4, angle, buraGraphs[frame2], TRUE, FALSE);
}
