#include "ModeSelectScene.h"
#include "default.h"
#include "drawer.h"
#include <string>
#include <fstream>
using namespace std;

ModeSelectScene::ModeSelectScene(HGE* hge){
	this->hge=hge;
	type=MODESELECT;
	back=false;
	selected=Data::mode;
	down=false;
	up=false;
}

bool ModeSelectScene::initialize(){
	//加载资源 初始化成员变量
	fnt=new hgeFont("font1.fnt");
	HTEXTURE tex=hge->Texture_Load("lock.png");
	lock=new hgeSprite(tex,0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
	//读档当前游戏进度
	string s="state.save";//加载当前状态
	ifstream ist(s.c_str());
	if (ist.is_open()){
		ist>>state;
		ist.close();
	}else{
		ist.close();
		state=0;
		ofstream ost(s.c_str());
		ost<<0;
		ost.close();
	}
	return true;
}

bool ModeSelectScene::logic_update(){
	//按空格键返回
	if (hge->Input_GetKeyState(HGEK_SPACE)){
		back=true;
		Data::mode=(GameMode)selected;
		t=hge->Timer_GetTime();
	}
	//按上下键切换选择的mode
	if (hge->Input_GetKeyState(HGEK_UP)==false&&up) selected--;
	if (hge->Input_GetKeyState(HGEK_DOWN)==false&&down) selected++;
	if (selected<0) selected++;
	if (selected>state) selected--;
	up=hge->Input_GetKeyState(HGEK_UP);
	down=hge->Input_GetKeyState(HGEK_DOWN);
	return false;
}

bool ModeSelectScene::render(){
	fnt->SetScale(1.4);
	fnt->printf(50,20,HGETEXT_LEFT,"Mode Select");
	hgeQuad temp;
	temp.tex=0;
	temp.v[0].x=40; temp.v[0].y=90+selected*50;
	temp.v[1].x=350;temp.v[1].y=90+selected*50;
	temp.v[2].x=350;temp.v[2].y=140+selected*50;
	temp.v[3].x=40;temp.v[3].y=140+selected*50;
	for (int i=0;i<4;i++){
		temp.v[i].z=0.5;
		temp.v[i].col=0xFFFFFF00;
	}
	temp.blend=BLEND_COLORMUL|BLEND_ALPHABLEND|BLEND_NOZWRITE;
	hge->Gfx_RenderQuad(&temp);
	temp.v[0].x=45; temp.v[0].y=95+selected*50;
	temp.v[1].x=345;temp.v[1].y=95+selected*50;
	temp.v[2].x=345;temp.v[2].y=135+selected*50;
	temp.v[3].x=45;temp.v[3].y=135+selected*50;
	for (int i=0;i<4;i++){
		temp.v[i].z=0.6;
		temp.v[i].col=0xFF000000;
	}
	hge->Gfx_RenderQuad(&temp);
	fnt->SetScale(1);
	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(50,100,HGETEXT_LEFT,"Easy Mode");
	if (state<GameMode::NORMAL){ 
		fnt->SetColor(0xFF888888);
		lock->Render(305,145);
	}
	fnt->printf(50,150,HGETEXT_LEFT,"Normal Mode");
	if (state<GameMode::DIFFICULT) {
		fnt->SetColor(0xFF888888);
		lock->Render(305,195);
	}
	fnt->printf(50,200,HGETEXT_LEFT,"Difficult Mode");
	if (state<GameMode::ENDLESS) {
		fnt->SetColor(0xFF888888);
		lock->Render(305,245);
	}
	fnt->printf(50,250,HGETEXT_LEFT,"Endless Mode");
	fnt->SetColor(0xFFFFFFFF);
	fnt->SetScale(0.6);
	fnt->printf(20,450,HGETEXT_LEFT,"Press Key UP or DOWN to change mode");
	fnt->printf(20,500,HGETEXT_LEFT,"Press space to go back");
	return false;
}

bool ModeSelectScene::change(){
	return (back&&(hge->Timer_GetTime()-t>0.5));
}

int ModeSelectScene::get_change_type(){
	return START;
}

float ModeSelectScene::get_gap(){
	return hge->Timer_GetTime()-t;
}

bool ModeSelectScene::is_changing(){
	return back;
}

ModeSelectScene::~ModeSelectScene(){
}