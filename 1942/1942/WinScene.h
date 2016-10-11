#ifndef WINSCENE
#define WINSCENE



#include "scene.h"
#include <hgeFont.h>
/*��߷ֽ���*/
class WinScene:public Scene{
private:
	hgeFont* fnt;
	HGE* hge;
	bool back;		//�ж��Ƿ񷵻�������
	float t;
	hgeSprite* cup;	//��������
	bool new_mode;	//��¼�Ƿ�����¹ؿ�
	int state;		//��¼��ҵ�ǰ�򵽵ڼ���
public:
	WinScene(HGE* hge);	//���캯��
	bool initialize();			//��ʼ������
	bool render();				//���ƺ���
	bool logic_update();		//�߼�����
	bool change();				//�ж��Ƿ�Ӧ��ת������
	int get_change_type();		//�õ�Ӧ��ת���ĳ���
	float get_gap();			//�õ���ǰ�Ѿ�ת���˶��
	bool is_changing();			//�ж��Ƿ�����ת��
	~WinScene();
};



#endif