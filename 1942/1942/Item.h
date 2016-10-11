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

/*物品*/
class Item:public hgeSprite{
private:
	ItemType type;
	int value;
	HGE* hge;
	float x,y;
public:
	Item(HGE* hge,ItemType t,float x,float y);
	void Render();//渲染敌人
	void move(float dt);//物品移动(t为时间间隔)
	bool is_out();//判断是否出界
	float get_x(){return x;}//得到敌人x坐标
	float get_y(){return y;}//得到敌人y坐标
	ItemType get_type(){return type;}
	int get_value(){return value;}

};
/*物品节点*/
struct ItemNode{
	ItemNode* forward;
	Item* item;
	ItemNode* next;
	ItemNode():forward(NULL),item(NULL),next(NULL){}
};

#endif