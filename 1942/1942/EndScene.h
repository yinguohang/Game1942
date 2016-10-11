#ifndef ENDSCENE
#define ENDSCENE

#include "scene.h"
#include <hgeSprite.h>
#include <hgeFont.h>
#include <hgeguictrls.h>

class EndScene:public Scene{
	//��������
private:
	HGE* hge;
	HTEXTURE tex;	//����ͷ������
	hgeFont* fnt;	//����
	hgeFont* fnt_score;	//��������
	hgeSprite* spr;	//���þ���
	hgeSprite* spr_new;	//new��־
	hgeSprite* cur;	//���
	hgeGUIButton* but;	//restart��ť
	hgeGUI* gui;	//gui(����ť�İ���)
	float d_t;	//���Ƶ���һ��������ʱ��
	bool gameover;	//��¼��Ϸ�Ƿ����
	int score;		//��¼��ҵ÷�
	int* scores;	//��¼�߷ְ��еĵ÷�
	int num;		//��¼�߷ְ��з�������
	int ranking;	//��¼��ҵ÷�����
public:
	EndScene(HGE* hge,int x);	//���캯��
	bool initialize();			//��ʼ������
	bool render();				//���ƺ���
	bool logic_update();		//�߼�����
	bool change();				//�ж��Ƿ�Ӧ��ת������
	int get_change_type();		//�õ�Ӧ��ת���ĳ���
	bool is_changing();			//�ж��Ƿ�����ת��
	float get_gap();			//�õ���ǰ�Ѿ�ת���˶��
};

#endif