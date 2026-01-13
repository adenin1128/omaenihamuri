#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "BootScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "Result.h"
#include "StageNumber.h"
#include "../Source/Mainmenu.h"


SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	StageNumber* stageNum = FindGameObject<StageNumber>();
	if (name == "TITLE")
	{
		return new TitleScene();
	}
	if (name == "MENU")
	{
		return new MainmenuScene();
	}
	if(name == "RESULT")
	{
		return new Result();
	}
	if (stageNum->stagenum == 1)
	{
		return new PlayScene();
	}
	if (stageNum->stagenum == 2)
	{
		return new PlayScene();
	}
	if (stageNum->stagenum == 3)
	{
		return new PlayScene();
	}
	if (stageNum->stagenum == 4)
	{
		return new PlayScene();
	}
	if (stageNum->stagenum == 6)
	{
		return new PlayScene();
	}
	MessageBox(NULL, ("éüÇÃÉVÅ[ÉìÇÕÇ†ÇËÇ‹ÇπÇÒ\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
