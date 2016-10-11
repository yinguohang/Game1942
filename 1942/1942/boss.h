#ifndef BOSS
#define BOSS

#include <hgesprite.h>
#include "enemy.h"
#include "exception.h"

#define BOSSATTACK 20
#define BOSSHP 1000
#define BOSSV 100
#define BOSSFREQ 1

class Boss1:public Enemy{
private:
	int d;
public:
	Boss1(HGE* hge,const char* s,float x,float y,float vv=BOSSV,float att=BOSSATTACK,float freq=BOSSFREQ,float hp=BOSSHP);//构造函数
	void move(float t);	//移动
};

class Boss2:public Enemy{
private:
	int d;
public:
	Boss2(HGE* hge,const char* s,float x,float y,float vv=BOSSV,float att=BOSSATTACK,float freq=BOSSFREQ,float hp=BOSSHP);//构造函数
	void move(float t);	//移动
};

class Boss3:public Enemy{
private:
	int d;
public:
	Boss3(HGE* hge,const char* s,float x,float y,float vv=BOSSV,float att=BOSSATTACK,float freq=BOSSFREQ,float hp=BOSSHP);//构造函数
	void move(float t);	//移动
};

class Boss4:public Enemy{
private:
	int d;
	int pos;
public:
	Boss4(HGE* hge,const char* s,float x,float y,float vv=BOSSV,float att=BOSSATTACK,float freq=BOSSFREQ,float hp=BOSSHP);//构造函数
	void move(float t);	//移动
	bool attack();	//攻击
	
};


#endif