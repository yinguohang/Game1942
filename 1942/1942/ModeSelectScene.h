#ifndef MODESELECTSCENE
#define MODESELECTSCENE

#include "scene.h"
#include <hgeFont.h>
#include <hgeSprite.h>

class ModeSelectScene:public Scene{
private:
	HGE* hge;
	bool back;
	float t;
	hgeFont* fnt;
	int selected;
	bool up,down;				//��¼֮ǰup����down����״̬
	hgeSprite* lock;
	int state;		//��¼��ҵ�ǰ�򵽵ڼ���
public:
	ModeSelectScene(HGE* hge);	//���캯��
	bool initialize();			//��ʼ������
	bool render();				//���ƺ���
	bool logic_update();		//�߼�����
	bool change();				//�ж��Ƿ�Ӧ��ת������
	int get_change_type();		//�õ�Ӧ��ת���ĳ���
	float get_gap();			//�õ���ǰ�Ѿ�ת���˶��
	bool is_changing();			//�ж��Ƿ�����ת��
	~ModeSelectScene();
};
#endif