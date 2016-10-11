#ifndef MODESELECTSCENE
#define MODESELECTSCENE

#include "scene.h"
#include <hgeFont.h>
#include <hgeSprite.h>

class ModeSelectScene:public Scene{
private:
	HGE* hge;
	bool back;
	float t;
	hgeFont* fnt;
	int selected;
	bool up,down;				//记录之前up键和down键的状态
	hgeSprite* lock;
	int state;		//记录玩家当前打到第几关
public:
	ModeSelectScene(HGE* hge);	//构造函数
	bool initialize();			//初始化函数
	bool render();				//绘制函数
	bool logic_update();		//逻辑更新
	bool change();				//判断是否应该转换场景
	int get_change_type();		//得到应该转换的场景
	float get_gap();			//得到当前已经转换了多久
	bool is_changing();			//判断是否正在转换
	~ModeSelectScene();
};
#endif