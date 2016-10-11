#ifndef BULLET
#define BULLET

#include <cmath>
#include <hgeSprite.h>
#include "default.h"

/*子弹*/
class Bullet:public hgeSprite{
private:
	float v;			//速度
	float dir_x,dir_y;	//(dir_x,dir_y)单位方向向量
	float pos_x,pos_y;	//(pos_x,pos_y)左上角坐标
	float norm(float x,float y){
		return(sqrt(x*x+y*y));
	}//向量的模
	float damage;		//子弹伤害值
public:
	//构造器
	Bullet(HGE* hge,const char* s,float direction_x,float direction_y,float d,float vv=BULLETV,float position_x=NOT_SET_POS,float position_y=NOT_SET_POS);
	void move(float t);	//移动
	void Render();		//绘制该子弹
	void Render(float x,float y);	//在指定位置绘制该子弹
	bool set_v(float vv);	//设置速度
	void set_position(float px,float py);	//设置子弹位置
	bool is_out();		//判断是否出界
	float get_x();		//得到子弹的pos_x值
	float get_y();		//得到子弹的pos_y值
	float get_damage();	//得到子弹的damage(伤害)值
};

/*子弹节点*/
struct BulletNode{
	BulletNode* forward;	//前一节点
	Bullet* bullet;			//子弹
	BulletNode* next;		//后一节点
	BulletNode():forward(NULL),bullet(NULL),next(NULL){}
};

#endif