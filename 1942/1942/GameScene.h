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
	//��Ϸ����
private:
	/*GameScene���еĶ���*/
	HGE* hge;
	Player* player;		//���
	Background* background;	//����
	BulletNode* b_head; //�ӵ�����ͷ
	EnemyNode* e_head;	//�л�����ͷ
	BulletNode* e_b_head;	//�л��ӵ�����ͷ
	BombNode* bomb_head;	//��ըЧ��
	ItemNode* i_head;		//��Ʒ����ͷ
	/*Boss��ز���*/
	Enemy* boss;			//Boss
	bool last_boss;			//�Ƿ��ǵ�ǰboss�����һ��
	/*�����ȼ�����ؿؼ�*/
	hgeFont* fnt;			//Score HP ������
	hgeFont* fnt_level;		//Level������
	int score;				//��ǰ����
	int level;				//��ǰ�ȼ�
	float level_up_time;	//����ʱ���.
	/*��Ч*/
	HSTREAM bgm;			//bgm
	HEFFECT snd;			//�ӵ�������
	/*����ת��*/
	float d_t;				//���ƽ���ת����ʱ�����
	bool gameover;			//��¼�Ƿ�Ҫת������
	int next_scene;			//��¼��һ��������ʲô
	float timer;			//EnemyMaker�ļ�ʱ��
	int keys[5];			//��ǰ����״̬ 1-���� 0-�ɿ�
	ifstream* ist_keys;
	ifstream* ist_random;
	ofstream* ost_keys;
	ofstream* ost_random;
public:
	//��ײ���
	bool IsCollision(hgeSprite* spr1, float x1, float y1, hgeSprite* spr2, float x2, float y2, HTEXTURE hot1 = 0, HTEXTURE hot2 = 0, DWORD airColor = 0x00ffffff);
	GameScene(HGE* hge);//���캯��
	/*��������е���ɾ����*/
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

	bool initialize();//��ʼ��
	void EnemyMake();//���ɵ���
	void make_item(float x,float y);//���ɵ�����Ʒ
	bool logic_update();	//�߼�����
	bool render();			//����
	bool change();			//�õ������Ƿ�ת��
	int get_change_type();  //�õ�Ӧ��ת���ĳ���
	bool is_changing();		//�ж��Ƿ�����ת������
	float get_gap();        //�õ���ǰ�Ѿ�ת���˶��
	int get_change_information(){return score;};
	~GameScene();			//��������

	
};

#endif