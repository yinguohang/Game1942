#ifndef BULLET
#define BULLET

#include <cmath>
#include <hgeSprite.h>
#include "default.h"

/*�ӵ�*/
class Bullet:public hgeSprite{
private:
	float v;			//�ٶ�
	float dir_x,dir_y;	//(dir_x,dir_y)��λ��������
	float pos_x,pos_y;	//(pos_x,pos_y)���Ͻ�����
	float norm(float x,float y){
		return(sqrt(x*x+y*y));
	}//������ģ
	float damage;		//�ӵ��˺�ֵ
public:
	//������
	Bullet(HGE* hge,const char* s,float direction_x,float direction_y,float d,float vv=BULLETV,float position_x=NOT_SET_POS,float position_y=NOT_SET_POS);
	void move(float t);	//�ƶ�
	void Render();		//���Ƹ��ӵ�
	void Render(float x,float y);	//��ָ��λ�û��Ƹ��ӵ�
	bool set_v(float vv);	//�����ٶ�
	void set_position(float px,float py);	//�����ӵ�λ��
	bool is_out();		//�ж��Ƿ����
	float get_x();		//�õ��ӵ���pos_xֵ
	float get_y();		//�õ��ӵ���pos_yֵ
	float get_damage();	//�õ��ӵ���damage(�˺�)ֵ
};

/*�ӵ��ڵ�*/
struct BulletNode{
	BulletNode* forward;	//ǰһ�ڵ�
	Bullet* bullet;			//�ӵ�
	BulletNode* next;		//��һ�ڵ�
	BulletNode():forward(NULL),bullet(NULL),next(NULL){}
};

#endif