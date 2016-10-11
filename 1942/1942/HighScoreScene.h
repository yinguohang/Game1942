#ifndef HIGHSCORESCENE
#define HIGHSCORESCENE

#include "scene.h"
#include <hgeFont.h>
/*最高分界面*/
class HighScoreScene:public Scene{
private:
	hgeFont* fnt;
	HGE* hge;
	bool back;	//判断是否返回主界面
	float t;
	int num;
	int* scores;
public:
	HighScoreScene(HGE* hge);	//构造函数
	bool initialize();			//初始化函数
	bool render();				//绘制函数
	bool logic_update();		//逻辑更新
	bool change();				//判断是否应该转换场景
	int get_change_type();		//得到应该转换的场景
	float get_gap();			//得到当前已经转换了多久
	bool is_changing();			//判断是否正在转换
	~HighScoreScene();
};

#endif