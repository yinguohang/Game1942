#ifndef BACKGROUND
#define BACKGROUND

#include <hgeSprite.h>

class Background:public hgeSprite{
/*������ ��GameScene����ʵ������*/
private:
	float t_y;	//���Ƶ�ǰ��������һ����������ʱ��(����)
	float v;	//�������¹������ٶ�
	HGE* hge;	//��ǰ���������ڵ�hge����
public:	
	void Render();	//��Ⱦ��ǰ������ ���任����������ʵ�ֱ�������
	Background(HGE* hge,const char* s);//���캯��
	/*sΪ�ļ���*/
};

#endif