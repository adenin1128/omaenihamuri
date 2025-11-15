#include "Clear.h"
#include "field.h"
#include "Gameover.h"

Clear::Clear()
{
	clearImage =  LoadGraph("data/image/culear.png");
	Field* field = FindGameObject<Field>();
	deathCount = field->GetDeathCount();

}

Clear::~Clear()
{
}

void Clear::Update()
{

}

void Clear::Draw()
{
	DrawRotaGraph(990, 540, 0.5, 0., clearImage, TRUE, FALSE);
	DrawExtendFormatStringToHandle(870, 560, 2, 2, GetColor(0, 0, 0), GetDefaultFontHandle(), "ïâÇØÇΩâÒêî %dâÒ", deathCount - 1);
}