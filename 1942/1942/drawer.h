#ifndef DRAWER
#define DRAWER
#include <hgesprite.h>
#include "scene.h"

enum GameMode{
	EASY=0,
	NORMAL,
	DIFFICULT,
	ENDLESS
};

/*游戏数据总控制*/
struct Data{
	static int player_hp;
	static int player_attack;
	static int player_v;
	static int player_bullet_freq;

	static int enemy_hp;
	static int enemy_attack;
	static int enemy_v;
	static int enemy_bullet_freq;
	static int frames;

	static bool is_loading;
	static GameMode mode;
};

/*游戏总类*/
class Drawer{
	/*资源管理*/
	/*友元*/
	friend class Draw;
	friend class Logic;
private:
	static HGE* hge;
	static Logic* logic;
	static Draw* draw;
	static Scene* scene;
public:
	//构造函数
	Drawer();
	//帧绘制函数
	static bool FrameFunc();
	static bool RenderFunc();
	void start();
	void end();
};
#endif