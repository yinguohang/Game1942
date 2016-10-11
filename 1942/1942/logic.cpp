#include "logic.h"
#include "WinScene.h"
#include "drawer.h"
#include "StartScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "HighScoreScene.h"
#include "InstructionsScene.h"
#include "ModeSelectScene.h"

Logic::Logic()
{
}

bool Logic::Update()
{
	int temp;
	if (Drawer::scene->change())//判断场景转换
	{
		switch (Drawer::scene->get_change_type()){
		case START:
			delete Drawer::scene;
			Drawer::scene=new StartScene(Drawer::hge);
			break;
		case GAME:
			delete Drawer::scene;
			Drawer::scene=new GameScene(Drawer::hge);
			break;
		case END:
			temp=Drawer::scene->get_change_information();
			delete Drawer::scene;
			Drawer::scene=new EndScene(Drawer::hge,temp);
			break;
		case HIGHSCORE:
			delete Drawer::scene;
			Drawer::scene=new HighScoreScene(Drawer::hge);
			break;
		case INSTRUCTIONS:
			delete Drawer::scene;
			Drawer::scene=new InstructionsScene(Drawer::hge);
			break;
		case MODESELECT:
			delete Drawer::scene;
			Drawer::scene=new ModeSelectScene(Drawer::hge);
			break;
		case WIN:
			delete Drawer::scene;
			Drawer::scene=new WinScene(Drawer::hge);
			break;
		} 
		if (!Drawer::scene->initialize()) return true;
		return false;
	}
	return (Drawer::scene->logic_update());//逻辑更新
}


