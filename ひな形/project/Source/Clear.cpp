#include "Clear.h"

Clear::Clear()
{
}

Clear::~Clear()
{
}

void Clear::Update()
{

}

void Clear::Draw()
{
	DrawRotaGraph(990, 540, 0.5, 0., loseImage, TRUE, FALSE);
	DrawExtendFormatStringToHandle(870, 560, 2, 2, GetColor(0, 0, 0), GetDefaultFontHandle(), "•‰‚¯‚½‰ñ” %d‰ñ", deathCount);
}