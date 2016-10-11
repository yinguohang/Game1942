#ifndef BOMB
#define BOMB

#include <hgeSprite.h>

class Bomb:public hgeSprite{
/*爆炸效果类:主要实现敌机坠毁后的爆炸动画*/
private:
	float x1,x2,y1,y2;	//(x1,y1)为爆炸效果左上角坐标 (x2,y2)为爆炸效果右下角坐标
	float frame;	//当前帧数
public:
	Bomb(HGE* hge,float x1,float y1,float x2,float y2);//(x1,y1)为爆炸效果左上角坐标 (x2,y2)为爆炸效果右下角坐标
	void Render();		//渲染当前爆炸效果 并将纹理坐标设置成下一帧
	bool need_delete();	//判断当前爆炸是否需要delete(播放完毕)
}; 
/*GameScene中存储爆炸效果的数据结构(链表)*/
struct BombNode{
	BombNode* forward;	//前一个
	Bomb* bomb;			//对应的爆炸效果
	BombNode* next;		//后一个
	BombNode():forward(NULL),bomb(NULL),next(NULL){}
};

#endif