#ifndef INSTRUCTIONSSCENE
#define INSTRUCTIONSSCENE

#include "scene.h"
#include "hge.h"
#include <hgeSprite.h>

class InstructionsScene:public Scene{
private:
	HGE* hge;
	bool back;
	hgeSprite* spr;
	float t;
	bool space;
	int now;
public:
	InstructionsScene(HGE* hge);	//���캯��
	bool initialize();			//��ʼ������
	bool render();				//���ƺ���
	bool logic_update();		//�߼�����
	bool change();				//�ж��Ƿ�Ӧ��ת������
	int get_change_type();		//�õ�Ӧ��ת���ĳ���
	float get_gap();			//�õ���ǰ�Ѿ�ת���˶��
	bool is_changing();			//�ж��Ƿ�����ת��
	~InstructionsScene();
};

#endif