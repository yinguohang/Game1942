#include "InstructionsScene.h"
#include "default.h"

InstructionsScene::InstructionsScene(HGE* hge){
	this->hge=hge;
	type=INSTRUCTIONS;
	back=false;
	space=false;
	now=0;
}

bool InstructionsScene::initialize(){
	//加载资源 初始化成员变量
	HTEXTURE tex=hge->Texture_Load("instructions1.jpg");
	spr=new hgeSprite(tex,0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
	return true;
}

bool InstructionsScene::logic_update(){
	if ((!hge->Input_GetKeyState(HGEK_SPACE))&&space){
		if (now==0){
			now++;
			HTEXTURE tex=hge->Texture_Load("instructions2.jpg");
			spr->SetTexture(tex);
		}else{
			back=true;
			t=hge->Timer_GetTime();
		}
	}
	space=hge->Input_GetKeyState(HGEK_SPACE);
	return false;
}

bool InstructionsScene::render(){
	spr->Render(0,0);
	return false;
}

bool InstructionsScene::change(){
	return (back&&(hge->Timer_GetTime()-t>0.5));
}

int InstructionsScene::get_change_type(){
	return START;
}

float InstructionsScene::get_gap(){
	return hge->Timer_GetTime()-t;
}

bool InstructionsScene::is_changing(){
	return back;
}

InstructionsScene::~InstructionsScene(){
	delete spr;
}