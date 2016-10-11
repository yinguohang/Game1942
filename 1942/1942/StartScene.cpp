#include "StartScene.h"
#include "default.h"
#include "menuitem.h"
#include <cmath>
#include "drawer.h"

float StartScene::p_t=0;
int StartScene::p_id=-1;

StartScene::StartScene(HGE* hge){
	this->hge=hge;
	type=START;
	p_t=0;
	p_id=-1;
}

bool StartScene::render(){
	bg->Render();
	gui->Render();
	return false;
}

bool StartScene::initialize(){
	p_t=hge->Timer_GetTime();
	p_id=-1;
	bg=new Background(hge,"bg.png");
	tex=hge->Texture_Load("cursor.png");
	snd=hge->Effect_Load("menu.wav");
	if (!tex||!snd)
	{
		MessageBoxA(NULL, "Can't load CURSOR.PNG or MENU.WAV", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		hge->System_Shutdown();
		hge->Release();
		return false;
	}
	
	//加载字体和鼠标
	fnt=new hgeFont("font1.fnt");
	spr=new hgeSprite(tex,0,0,32,32);

	//创造并初始化GUI
	gui=new hgeGUI();

	gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,SCREENWIDTH/2,200,0.0f,"Play"));
	gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,SCREENWIDTH/2,240,0.1f,"Mode Select"));
	gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,SCREENWIDTH/2,280,0.2f,"Instructions"));
	gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,SCREENWIDTH/2,320,0.3f,"High Score"));
	gui->AddCtrl(new hgeGUIMenuItem(6,fnt,snd,SCREENWIDTH/2,360,0.4f,"Load"));
	gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,SCREENWIDTH/2,400,0.5f,"Exit"));

	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(1);
	gui->Enter();
}

bool StartScene::logic_update(){
	float dt=hge->Timer_GetDelta();
		static float t=0.0f;
		int id;
		static int lastid=0;

		if(hge->Input_GetKeyState(HGEK_ESCAPE)) 
			{ 
				lastid=5; 
				gui->Leave(); 
		}
	
		id=gui->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 6:
					gui->SetFocus(1);
					gui->Enter();
					break;

				case 5: return true;
			}
		}
		else if(id) { lastid=id; gui->Leave(); }

		return false;
}

bool StartScene::change(){
	bool temp=((p_id>=1&&p_id<=4||p_id==6)&&(hge->Timer_GetTime()-p_t>0.5));
	return temp;
}

int StartScene::get_change_type(){
	switch (p_id){
	case 1:
		Data::is_loading=false;
		return GAME;
	case 2:
		return MODESELECT;
	case 3:
		return INSTRUCTIONS;
	case 4:
		return HIGHSCORE;
	case 6:
		Data::is_loading=true;
		return GAME;
	}
}

bool StartScene::is_changing(){
	return (p_id>=1&&p_id<=4||p_id==6);
}

float StartScene::get_gap(){
	return hge->Timer_GetTime()-p_t;
}