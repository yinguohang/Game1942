#ifndef PLAYER
#define PLAYER

#include <hgeSprite.h>
#include "drawer.h"
#include "enemy.h"

class Player:public hgeSprite{
private:
	float x,y;//��������
	float lasttime;
	float p_t;//����Ĥ��ʼʱ�� -1��ʾû�д��ڱ���Ĥ״̬
	float p_l_t;//����Ĥ����ʱ��
	float b_t;//�ӵ�������ʼʱ�� -1��ʾû�д��ڱ���Ĥ״̬
	float b_l_t;//�ӵ���������ʱ��
	int b_freq;//1����ٷ��ӵ�
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
	float get_x();//�õ�����x����
	float get_y();//�õ�����y����
	float get_middle_x();//�õ���������λ��x����
	float get_meddle_y();//�õ���������λ��y����
	float get_attack();//�õ�player������
	bool is_attack();//�õ��ڵ�ǰʱ���Ƿ񹥻�
	bool attacked(int x);//��������Ϊx���ӵ�������
	float get_v();
	bool is_protected();//�ж��Ƿ��ڱ���Ĥ״̬
	void protect(float t);//��������t�ı���Ĥ
	bool is_upgraded();
	void upgrade(float t);//��������t�ı���Ĥ
	void add_hp(int x){hp+=x;if (hp>hp_max) hp=hp_max;}
	int get_b_num();
	Point get_b_pos(int x);

};

#endif