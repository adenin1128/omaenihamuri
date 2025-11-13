#include "Clear.h"
#include <assert.h>

Clear::Clear()
{
	hImage = LoadGraph("data/image/clear.png");
	assert(hImage > 0);
}

Clear::~Clear()
{
}

void Clear::Update()
{
}

void Clear::Draw()
{
	DrawGraph(200, 100, hImage, TRUE);
}
