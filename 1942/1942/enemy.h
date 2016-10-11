#ifndef ENEMY
#define ENEMY

#include <hgeSprite.h>
#include "default.h"

struct Point{
	float x,y,vx,vy;
	Point(float xx=0,float yy=0,float v_x=0,float v_y=1):x(xx),y(yy),vx(v_x),vy(v_y){}
	//vx=vy=0��Ϊ׷�ٵ�
};

/*����*/
class Enemy:public hgeSprite{
protected:
	float hp,hp_max;		//Ѫ���������ֵ
	float pos_x,pos_y;		//Enemy����
	float att;				//Enemy������	
	float v;				//�ƶ��ٶ�
	float t;				//��ʱ��
	float freq;				//�ӵ�Ƶ��
	int b_num;				//�ӵ���Ŀ
	Point *b_pos;			//�ӵ�λ��
public:
	Enemy(HGE* hge,const char* s,float x,float y,float vv=ENEMYV,float att=ENEMYATTACK,float freq=ENEMYBULLETFREQ,float hp=ENEMYHP);
	void set_position(float x,float y);	//���õ�������
	virtual void move(float t);			//�����ƶ�(tΪʱ����)
	void Render();						//��Ⱦ����
	void Render(float,float);			//���ض�λ����Ⱦ����
	bool is_out();						//�ж��Ƿ����
	float get_x();						//�õ�����x����
	float get_y();						//�õ�����y����
	float get_hp();						//�õ�����Ѫ��
	float get_hp_max();					//�õ�����Ѫ�����ֵ
	bool attacked(int x);				//��������Ϊx���ӵ�������
	virtual bool attack();				//�ж�ʱ��Ӧ�ù���
	int get_b_num();					//�õ�����ʱ�ӵ�����
	Point get_b_pos(int x);				//�õ���i���ӵ�λ��
	float get_middle_x();				//�õ���������λ��x����
	float get_middle_y();				//�õ���������λ��y����
	~Enemy();							//��������
};

class Enemy2:public Enemy{
public:
	Enemy2(HGE* hge,const char* s,float x,float y,float vv=ENEMYV,float att=ENEMYATTACK,float freq=ENEMYBULLETFREQ,float hp=ENEMYHP);
};

/*���˽ڵ�*/	
struct EnemyNode{
	EnemyNode* forward;
	Enemy* enemy;
	EnemyNode* next;
	EnemyNode():forward(NULL),enemy(NULL),next(NULL){}
};

#endif