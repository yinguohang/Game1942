#ifndef STARTSCENE
#define STARTSCENE

#include "scene.h"
#include <hgefont.h>
#include <hgeGUI.h>
#include "background.h"

class StartScene:public Scene{
	friend class hgeGUIMenuItem;
private:
	HEFFECT snd;
	HTEXTURE tex;
	Background* bg;
	hgeGUI *gui;
	hgeFont *fnt;
	hgeSprite *spr;
	static float p_t;
	static int p_id;
	HGE* hge;
public:
	StartScene(HGE* hge);//���캯��
	bool initialize();//��ʼ������
	bool logic_update();//�߼�����
	bool render();//���ƺ���
	bool change();//�ж��Ƿ�Ӧ��ת������
	int get_change_type();//�õ�Ӧ��ת���ĳ���
	bool is_changing();//�ж��Ƿ�����ת��
	float get_gap();//�õ���ǰ�Ѿ�ת���˶��
};

#endif