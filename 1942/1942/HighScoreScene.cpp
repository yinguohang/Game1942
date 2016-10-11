#include "HighScoreScene.h"
#include "default.h"
#include <fstream>
#include <string>
using namespace std;

HighScoreScene::HighScoreScene(HGE* hge){
	this->hge=hge;
	type=HIGHSCORE;
	back=false;
}

bool HighScoreScene::initialize(){
	//加载资源 初始化成员变量
	fnt=new hgeFont("Font1.fnt");
	string s="highest.txt";
	ifstream ist(s.c_str());
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
	return true;
}

bool HighScoreScene::logic_update(){
	if (hge->Input_GetKeyState(HGEK_SPACE)){
		back=true;
		t=hge->Timer_GetTime();
	}
	return false;
}

bool HighScoreScene::render(){
	//绘制高分榜
	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(50,50,HGETEXT_LEFT,"High Scores");
	switch (num){
	case 5:
		fnt->printf(50,300,HGETEXT_LEFT,"5th:%d", scores[4]);
	case 4:
		fnt->printf(50,250,HGETEXT_LEFT,"4th:%d", scores[3]);
	case 3:
		fnt->printf(50,200,HGETEXT_LEFT,"3rd:%d", scores[2]);
	case 2:
		fnt->printf(50,150,HGETEXT_LEFT,"2nd:%d", scores[1]);
	case 1:
		fnt->printf(50,100,HGETEXT_LEFT,"1st:%d", scores[0]);
	}
	fnt->printf(50,500,HGETEXT_LEFT,"Press space to go back!");
	return false;
}

bool HighScoreScene::change(){
	return (back&&(hge->Timer_GetTime()-t>0.5));
}

int HighScoreScene::get_change_type(){
	return START;
}

float HighScoreScene::get_gap(){
	return hge->Timer_GetTime()-t;
}

bool HighScoreScene::is_changing(){
	return back;
}

HighScoreScene::~HighScoreScene(){
	delete scores;
}