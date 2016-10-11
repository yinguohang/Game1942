#ifndef BOMB
#define BOMB

#include <hgeSprite.h>

class Bomb:public hgeSprite{
/*��ըЧ����:��Ҫʵ�ֵл�׹�ٺ�ı�ը����*/
private:
	float x1,x2,y1,y2;	//(x1,y1)Ϊ��ըЧ�����Ͻ����� (x2,y2)Ϊ��ըЧ�����½�����
	float frame;	//��ǰ֡��
public:
	Bomb(HGE* hge,float x1,float y1,float x2,float y2);//(x1,y1)Ϊ��ըЧ�����Ͻ����� (x2,y2)Ϊ��ըЧ�����½�����
	void Render();		//��Ⱦ��ǰ��ըЧ�� ���������������ó���һ֡
	bool need_delete();	//�жϵ�ǰ��ը�Ƿ���Ҫdelete(�������)
}; 
/*GameScene�д洢��ըЧ�������ݽṹ(����)*/
struct BombNode{
	BombNode* forward;	//ǰһ��
	Bomb* bomb;			//��Ӧ�ı�ըЧ��
	BombNode* next;		//��һ��
	BombNode():forward(NULL),bomb(NULL),next(NULL){}
};

#endif