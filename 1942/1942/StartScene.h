#ifndef STARTSCENE
#define STARTSCENE

#include "scene.h"
#include <hgefont.h>
#include <hgeGUI.h>
#include "background.h"

class StartScene:public Scene{
	friend class hgeGUIMenuItem;
private:
	HEFFECT snd;
	HTEXTURE tex;
	Background* bg;
	hgeGUI *gui;
	hgeFont *fnt;
	hgeSprite *spr;
	static float p_t;
	static int p_id;
	HGE* hge;
public:
	StartScene(HGE* hge);//构造函数
	bool initialize();//初始化函数
	bool logic_update();//逻辑更新
	bool render();//绘制函数
	bool change();//判断是否应该转换场景
	int get_change_type();//得到应该转换的场景
	bool is_changing();//判断是否正在转换
	float get_gap();//得到当前已经转换了多久
};

#endif