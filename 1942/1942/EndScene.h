#ifndef ENDSCENE
#define ENDSCENE

#include "scene.h"
#include <hgeSprite.h>
#include <hgeFont.h>
#include <hgeguictrls.h>

class EndScene:public Scene{
	//结束场景
private:
	HGE* hge;
	HTEXTURE tex;	//骷髅头像纹理
	hgeFont* fnt;	//字体
	hgeFont* fnt_score;	//分数字体
	hgeSprite* spr;	//骷髅精灵
	hgeSprite* spr_new;	//new标志
	hgeSprite* cur;	//鼠标
	hgeGUIButton* but;	//restart按钮
	hgeGUI* gui;	//gui(处理按钮的按下)
	float d_t;	//控制到下一个场景的时间
	bool gameover;	//记录游戏是否结束
	int score;		//记录玩家得分
	int* scores;	//记录高分榜中的得分
	int num;		//记录高分榜中分数数量
	int ranking;	//记录玩家得分排名
public:
	EndScene(HGE* hge,int x);	//构造函数
	bool initialize();			//初始化函数
	bool render();				//绘制函数
	bool logic_update();		//逻辑更新
	bool change();				//判断是否应该转换场景
	int get_change_type();		//得到应该转换的场景
	bool is_changing();			//判断是否正在转换
	float get_gap();			//得到当前已经转换了多久
};

#endif