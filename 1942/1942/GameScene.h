#ifndef GAMESCENE
#define GAMESCENE

#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "background.h"
#include <hgeFont.h>
#include "bomb.h"
#include "Item.h"
#include <fstream>
using namespace std;

#define SPACE 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class GameScene:public Scene{
	//游戏场景
private:
	/*GameScene持有的对象*/
	HGE* hge;
	Player* player;		//玩家
	Background* background;	//背景
	BulletNode* b_head; //子弹链表头
	EnemyNode* e_head;	//敌机链表头
	BulletNode* e_b_head;	//敌机子弹链表头
	BombNode* bomb_head;	//爆炸效果
	ItemNode* i_head;		//物品链表头
	/*Boss相关参数*/
	Enemy* boss;			//Boss
	bool last_boss;			//是否是当前boss的最后一个
	/*分数等级及相关控件*/
	hgeFont* fnt;			//Score HP 的字体
	hgeFont* fnt_level;		//Level的字体
	int score;				//当前分数
	int level;				//当前等级
	float level_up_time;	//升级时间点.
	/*音效*/
	HSTREAM bgm;			//bgm
	HEFFECT snd;			//子弹发射声
	/*界面转换*/
	float d_t;				//控制界面转换的时间参数
	bool gameover;			//记录是否要转换界面
	int next_scene;			//记录下一个场景是什么
	float timer;			//EnemyMaker的计时器
	int keys[5];			//当前键盘状态 1-按下 0-松开
	ifstream* ist_keys;
	ifstream* ist_random;
	ofstream* ost_keys;
	ofstream* ost_random;
public:
	//碰撞检测
	bool IsCollision(hgeSprite* spr1, float x1, float y1, hgeSprite* spr2, float x2, float y2, HTEXTURE hot1 = 0, HTEXTURE hot2 = 0, DWORD airColor = 0x00ffffff);
	GameScene(HGE* hge);//构造函数
	/*对链表进行的增删操作*/
	void add_bullet(BulletNode** tp);
	void remove_bullet(BulletNode** tp);

	void add_bomb(BombNode** tp);
	void remove_bomb(BombNode** tp);

	void add_item(ItemNode** tp);
	void remove_item(ItemNode** tp);

	void add_enemy(EnemyNode** tp);
	void remove_enemy(EnemyNode** tp);

	void add_enemy_bullet(BulletNode** tp);
	void remove_enemy_bullet(BulletNode** tp);

	void get_keys();
	int get_random(int x);

	bool initialize();//初始化
	void EnemyMake();//生成敌人
	void make_item(float x,float y);//生成掉落物品
	bool logic_update();	//逻辑更新
	bool render();			//绘制
	bool change();			//得到场景是否转换
	int get_change_type();  //得到应该转换的场景
	bool is_changing();		//判断是否正在转换场景
	float get_gap();        //得到当前已经转换了多久
	int get_change_information(){return score;};
	~GameScene();			//析构函数

	
};

#endif