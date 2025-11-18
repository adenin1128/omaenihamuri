#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "BootScene.h"
#include "TitleScene.h"
#include "PlayScene1.h"
#include "PlayScene2.h"
#include "PlayScene3.h"
#include "../Source/Mainmenu.h"


SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	if (name == "TITLE")
	{
		return new TitleScene();
	}
	if (name == "MENU")
	{
		return new MainmenuScene();
	}
	if (name == "PLAY1")
	{
		return new PlayScene1();
	}
	if (name == "PLAY2")
	{
		return new PlayScene2();
	}
	if (name == "PLAY3")
	{
		return new PlayScene3();
	}
	MessageBox(NULL, ("éüÇÃÉVÅ[ÉìÇÕÇ†ÇËÇ‹ÇπÇÒ\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
