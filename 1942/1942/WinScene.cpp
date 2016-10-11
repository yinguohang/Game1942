#include "WinScene.h"
#include "default.h"
#include <string>
#include <fstream>
#include "drawer.h"
using namespace std;

WinScene::WinScene(HGE* hge){
	this->hge=hge;
	type=WIN;
	back=false;
}

bool WinScene::initialize(){
	//加载资源 初始化成员变量
	fnt=new hgeFont("Font1.fnt");
	HTEXTURE tex=hge->Texture_Load("cup2.png");
	cup=new hgeSprite(tex,0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
	string s="state.save";//加载当前状态
	ifstream ist(s.c_str());
	if (ist.is_open()){
		ist>>state;
		ist.close();
	}else{
		ist.close();
		state=0;
	}
	if (state==Data::mode) {
		Data::mode=(GameMode)(state+1);
		ofstream ost(s.c_str());
		ost<<Data::mode;
		ost.close();
		new_mode=true;
	}
	else 
		new_mode=false;
	return true;
}

bool WinScene::logic_update(){
	if (hge->Input_GetKeyState(HGEK_ENTER)){
		back=true;
		t=hge->Timer_GetTime();
	}
	return false;
}

bool WinScene::render(){
	//绘制高分榜
	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(50,50,HGETEXT_LEFT,"Congratulations!");
	fnt->printf(50,100,HGETEXT_LEFT,"You pass the game!");
	cup->Render(100,150);
	if (new_mode){
		fnt->SetColor(0xFFFF0000);
		switch(state){
		case 0:
			fnt->printf(50,450,HGETEXT_LEFT,"Normal Mode");
			break;
		case 1:
			fnt->printf(50,450,HGETEXT_LEFT,"Difficult Mode");
			break;
		case 2:
			fnt->printf(50,450,HGETEXT_LEFT,"Endless Mode");
			break;
		}
		fnt->SetColor(0xFFFFFFFF);
		fnt->printf(210,450,HGETEXT_LEFT,"Unlocked!");
	}
	fnt->printf(50,500,HGETEXT_LEFT,"Press Enter to go back!");
	return false;
}

bool WinScene::change(){
	return (back&&(hge->Timer_GetTime()-t>0.5));
}

int WinScene::get_change_type(){
	return START;
}

float WinScene::get_gap(){
	return hge->Timer_GetTime()-t;
}

bool WinScene::is_changing(){
	return back;
}

WinScene::~WinScene(){
}