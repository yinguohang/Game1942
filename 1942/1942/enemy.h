#ifndef ENEMY
#define ENEMY

#include <hgeSprite.h>
#include "default.h"

struct Point{
	float x,y,vx,vy;
	Point(float xx=0,float yy=0,float v_x=0,float v_y=1):x(xx),y(yy),vx(v_x),vy(v_y){}
	//vx=vy=0则为追踪弹
};

/*敌人*/
class Enemy:public hgeSprite{
protected:
	float hp,hp_max;		//血量及其最大值
	float pos_x,pos_y;		//Enemy坐标
	float att;				//Enemy攻击力	
	float v;				//移动速度
	float t;				//计时器
	float freq;				//子弹频率
	int b_num;				//子弹数目
	Point *b_pos;			//子弹位置
public:
	Enemy(HGE* hge,const char* s,float x,float y,float vv=ENEMYV,float att=ENEMYATTACK,float freq=ENEMYBULLETFREQ,float hp=ENEMYHP);
	void set_position(float x,float y);	//设置敌人坐标
	virtual void move(float t);			//敌人移动(t为时间间隔)
	void Render();						//渲染敌人
	void Render(float,float);			//在特定位置渲染敌人
	bool is_out();						//判断是否出界
	float get_x();						//得到敌人x坐标
	float get_y();						//得到敌人y坐标
	float get_hp();						//得到敌人血量
	float get_hp_max();					//得到敌人血量最大值
	bool attacked(int x);				//被攻击力为x的子弹攻击到
	virtual bool attack();				//判断时候应该攻击
	int get_b_num();					//得到攻击时子弹数量
	Point get_b_pos(int x);				//得到第i个子弹位置
	float get_middle_x();				//得到敌人中心位置x坐标
	float get_middle_y();				//得到敌人中心位置y坐标
	~Enemy();							//析构函数
};

class Enemy2:public Enemy{
public:
	Enemy2(HGE* hge,const char* s,float x,float y,float vv=ENEMYV,float att=ENEMYATTACK,float freq=ENEMYBULLETFREQ,float hp=ENEMYHP);
};

/*敌人节点*/	
struct EnemyNode{
	EnemyNode* forward;
	Enemy* enemy;
	EnemyNode* next;
	EnemyNode():forward(NULL),enemy(NULL),next(NULL){}
};

#endif