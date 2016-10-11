#ifndef WINSCENE
#define WINSCENE



#include "scene.h"
#include <hgeFont.h>
/*最高分界面*/
class WinScene:public Scene{
private:
	hgeFont* fnt;
	HGE* hge;
	bool back;		//判断是否返回主界面
	float t;
	hgeSprite* cup;	//奖杯精灵
	bool new_mode;	//记录是否解锁新关卡
	int state;		//记录玩家当前打到第几关
public:
	WinScene(HGE* hge);	//构造函数
	bool initialize();			//初始化函数
	bool render();				//绘制函数
	bool logic_update();		//逻辑更新
	bool change();				//判断是否应该转换场景
	int get_change_type();		//得到应该转换的场景
	float get_gap();			//得到当前已经转换了多久
	bool is_changing();			//判断是否正在转换
	~WinScene();
};



#endif