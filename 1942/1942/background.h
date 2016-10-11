#ifndef BACKGROUND
#define BACKGROUND

#include <hgeSprite.h>

class Background:public hgeSprite{
/*背景类 在GameScene生成实例对象*/
private:
	float t_y;	//控制当前场景到下一场景持续的时间(渐变)
	float v;	//背景向下滚动的速度
	HGE* hge;	//当前背景类所在的hge环境
public:	
	void Render();	//渲染当前背景类 并变换纹理坐标以实现背景滚动
	Background(HGE* hge,const char* s);//构造函数
	/*s为文件名*/
};

#endif