#ifndef ITEM
#define ITEM

#include <hgeSprite.h>

enum ItemType{
	HP_PLUS=0,
	PROTECT,
	POISON,
	CLEAR,
	UPGRADE
};

/*��Ʒ*/
class Item:public hgeSprite{
private:
	ItemType type;
	int value;
	HGE* hge;
	float x,y;
public:
	Item(HGE* hge,ItemType t,float x,float y);
	void Render();//��Ⱦ����
	void move(float dt);//��Ʒ�ƶ�(tΪʱ����)
	bool is_out();//�ж��Ƿ����
	float get_x(){return x;}//�õ�����x����
	float get_y(){return y;}//�õ�����y����
	ItemType get_type(){return type;}
	int get_value(){return value;}

};
/*��Ʒ�ڵ�*/
struct ItemNode{
	ItemNode* forward;
	Item* item;
	ItemNode* next;
	ItemNode():forward(NULL),item(NULL),next(NULL){}
};

#endif