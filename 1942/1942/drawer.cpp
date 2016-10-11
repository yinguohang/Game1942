#include "drawer.h"
#include "logic.h"
#include "draw.h"
#include "EndScene.h"
#include "StartScene.h"
#include "default.h"

HGE *Drawer::hge = NULL;

Logic* Drawer::logic=NULL;
Draw* Drawer::draw=NULL;
Scene* Drawer::scene=NULL;

int Data::player_hp=0;
int Data::player_attack=0;
int Data::player_v=0;
int Data::player_bullet_freq=0;
int Data::enemy_hp=0;
int Data::enemy_attack=0;
int Data::enemy_v=0;
int Data::enemy_bullet_freq=0;
int Data::frames=0;
GameMode Data::mode=GameMode::EASY;
bool Data::is_loading=false;

Drawer::Drawer(){
	//设置hge必须参数
	Data::player_hp=PLAYERHP;
	Data::player_attack=PLAYERATTACK;
	Data::player_v=PLAYERV;
	Data::player_bullet_freq=PLAYERBULLETFREQ;
	Data::enemy_hp=ENEMYHP;
	Data::enemy_attack=ENEMYATTACK;
	Data::enemy_v=ENEMYV;
	Data::enemy_bullet_freq=ENEMYBULLETFREQ;
	hge=hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_SCREENWIDTH,SCREENWIDTH);
	hge->System_SetState(HGE_SCREENHEIGHT,SCREENHEIGHT);
	hge->System_SetState(HGE_FRAMEFUNC,FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC,RenderFunc);
	hge->System_SetState(HGE_SHOWSPLASH,false);
	hge->System_SetState(HGE_FPS,FPS);
	hge->System_SetState(HGE_WINDOWED,true);
	hge->System_SetState(HGE_USESOUND,true);
	hge->System_SetState(HGE_TITLE,"1942");
	logic=new Logic();
	draw=new Draw();
	scene=new StartScene(hge);
	if (!hge->System_Initiate()){
		MessageBoxA(NULL,hge->System_GetErrorMessage(),"Error",MB_OK|MB_ICONERROR|MB_APPLMODAL);	
	}
	if (!scene->initialize()){return;}
}
//帧逻辑函数
bool Drawer::FrameFunc(){
	Data::frames++;
	if (logic->Update()) return true;
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;	
	return false;
}
//绘画函数
bool Drawer::RenderFunc(){
	if (draw->draw()) return true;
	return false;//总是返回false 
}
//开始游戏
void Drawer::start(){
	hge->System_Start();
}
//结束游戏
void Drawer::end(){
	hge->System_Shutdown();
	hge->Release();
}

