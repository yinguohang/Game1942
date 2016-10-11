#ifndef PLAYER
#define PLAYER

#include <hgeSprite.h>
#include "drawer.h"
#include "enemy.h"

class Player:public hgeSprite{
private:
	float x,y;//精灵坐标
	float lasttime;
	float p_t;//保护膜开始时间 -1表示没有处于保护膜状态
	float p_l_t;//保护膜持续时间
	float b_t;//子弹升级开始时间 -1表示没有处于保护膜状态
	float b_l_t;//子弹升级持续时间
	int b_freq;//1秒多少发子弹
	int b_num;
	Point* b_pos;
	float v;
	int hp,hp_max;
	float att;
public:
	Player(HGE* hge,const char* s,float v ,float att, float freq, float hp);
	void Render();
	void Render(float xx,float yy);
	void set_position(float xx,float yy);
	float get_x();//得到敌人x坐标
	float get_y();//得到敌人y坐标
	float get_middle_x();//得到敌人中心位置x坐标
	float get_meddle_y();//得到敌人中心位置y坐标
	float get_attack();//得到player攻击力
	bool is_attack();//得到在当前时间是否攻击
	bool attacked(int x);//被攻击力为x的子弹攻击到
	float get_v();
	bool is_protected();//判断是否处于保护膜状态
	void protect(float t);//开启持续t的保护膜
	bool is_upgraded();
	void upgrade(float t);//开启持续t的保护膜
	void add_hp(int x){hp+=x;if (hp>hp_max) hp=hp_max;}
	int get_b_num();
	Point get_b_pos(int x);

};

#endif