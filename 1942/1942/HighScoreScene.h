#ifndef HIGHSCORESCENE
#define HIGHSCORESCENE

#include "scene.h"
#include <hgeFont.h>
/*��߷ֽ���*/
class HighScoreScene:public Scene{
private:
	hgeFont* fnt;
	HGE* hge;
	bool back;	//�ж��Ƿ񷵻�������
	float t;
	int num;
	int* scores;
public:
	HighScoreScene(HGE* hge);	//���캯��
	bool initialize();			//��ʼ������
	bool render();				//���ƺ���
	bool logic_update();		//�߼�����
	bool change();				//�ж��Ƿ�Ӧ��ת������
	int get_change_type();		//�õ�Ӧ��ת���ĳ���
	float get_gap();			//�õ���ǰ�Ѿ�ת���˶��
	bool is_changing();			//�ж��Ƿ�����ת��
	~HighScoreScene();
};

#endif