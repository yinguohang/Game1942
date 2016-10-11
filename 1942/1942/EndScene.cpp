#include "EndScene.h"
#include "default.h"
#include <fstream>
#include <string>
using namespace std;

bool EndScene::initialize(){
	//加载对应图片 字体资源
	fnt=new hgeFont("font1.fnt");
	fnt_score=new hgeFont("font2.fnt");
	gui=new hgeGUI();
	fnt->SetScale(2);
	fnt_score->SetScale(2);
	if	(!(tex=hge->Texture_Load("die.jpg"))) return false;
	spr=new hgeSprite(tex,0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
	if	(!(tex=hge->Texture_Load("new.png"))) return false;
	spr_new=new hgeSprite(tex,0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
	if	(!(tex=hge->Texture_Load("restart.png"))) return false;
	but=new hgeGUIButton(11,50,420,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex),tex,0,0);
	if	(!(tex=hge->Texture_Load("cursor.png"))) return false;
	cur=new hgeSprite(tex,0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex));
	gui->SetCursor(cur);
	gui->AddCtrl(but);
	gui->Enter();
	//加载高分榜
	string s="highest.txt";
	ifstream ist(s.c_str());
	//从文件中读出当前高分榜内容
	if (ist.is_open()){
		int i=0;
		scores=new int[5];
		while (i<5&&(ist>>scores[i])){
			i++;
		}
		ist.close();
		num=i;
		for (int j=0;j<num;j++){
			for (int k=j+1;k<num;k++){
				if (scores[j]<scores[k]){
					int temp=scores[j];
					scores[j]=scores[k];
					scores[k]=temp;
				}
			}
		}
	}else{
		ist.close();
		num=0;
		scores=new int[5];
	}
	//计算当前玩家得分排名
	int i;
	for (i=0;i<num;i++)
	{
		if (score>scores[i]) break; 
	}
	if (num<5){
		for (int j=num;j>i;j--){
			scores[j+1]=scores[j];
		}
		scores[i]=score;
		num++;
	}else{
		for (int j=num-1;j>=i;j--){
			scores[j+1]=scores[j];
		}
		if (i!=5) scores[i]=score;
	}
	ranking=i;
	//更新高分榜
	ofstream ost(s.c_str());
	for (int k=0;k<num;k++){
		ost<<scores[k]<<endl;
	}
	ost.close();
	return true;
}

bool EndScene::logic_update(){
	//逻辑更新
	gui->Update(hge->Timer_GetTime());
	if (but->GetState()||hge->Input_GetKeyState(HGEK_ENTER)){
		gameover=true;
		d_t=hge->Timer_GetTime();
	}
	return false;
}

bool EndScene::render(){
	//绘制
	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(50, 50, HGETEXT_LEFT,"Game Over!",score);
	spr->Render(50,100);
	but->Render();
	gui->Render();
	fnt_score->SetColor(0xFFFF0000);
	fnt_score->printf(50, 380, HGETEXT_LEFT,"SCORE: %d",score);
	if (ranking!=5) {
		spr_new->RenderStretch(330,330,380,380);
	}
	return false;
}

EndScene::EndScene(HGE* hge,int x){
	this->hge=hge;
	score=x;
	d_t=0;
	gameover=false;
	type=END;
}

bool EndScene::change(){
	bool temp=gameover&&(hge->Timer_GetTime()-d_t>0.5);
	return temp;
}

int EndScene::get_change_type(){
	return START;
}

bool EndScene::is_changing(){
	return gameover;
}

float EndScene::get_gap(){
	return hge->Timer_GetTime()-d_t;
}