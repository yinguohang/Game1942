#include "GameScene.h"
#include "exception.h"
#include <algorithm>
#include "boss.h"
#include "drawer.h"
#include <fstream>
using namespace std;

#define SCOREPERLEVER 12000


GameScene::GameScene(HGE* hge){
	this->hge=hge;
	timer=Data::frames;
	b_head=new BulletNode();
	e_head=new EnemyNode();
	e_b_head=new BulletNode();
	bomb_head=new BombNode();
	i_head=new ItemNode();
	type=GAME;
	d_t=0;
	gameover=false;
	score=0;
	boss=NULL;
	level=0;
	level_up_time=hge->Timer_GetTime();
	for (int i=0;i<5;i++) keys[i]=0;
	last_boss=false;
	next_scene=END;
}

bool GameScene::initialize(){
	if (Data::is_loading){
		ist_keys=new ifstream("record_keys.save");
		int temp;
		(*ist_keys)>>temp;
		Data::mode=(GameMode)temp;
		ist_random=new ifstream("record_random.save");
	}
	else{
		ost_keys=new ofstream("record_keys.save");
		(*ost_keys)<<Data::mode<<endl;
		ost_random=new ofstream("record_random.save");
	}
	try{
		player=new Player(hge,"plane1.png",Data::player_v,Data::player_attack,Data::player_bullet_freq,Data::player_hp);
		background=new Background(hge,"space.jpg");
		bgm=hge->Stream_Load("bg1.mp3");
		snd=hge->Effect_Load("launch.wav");
		fnt=new hgeFont("font1.fnt");
		fnt_level=new hgeFont("font1.fnt");
		fnt_level->SetScale(2);
	}catch(Exception e){
		return false;
	}
	hge->Stream_Play(bgm,true);
	return true;
}

GameScene::~GameScene(){
	hge->Stream_Free(bgm);
	EnemyNode *p=e_head;
	while (p->next)
	{
		delete p->enemy;
		p=p->next;
		delete p->forward;
	}
	delete p;
	BulletNode *q=b_head;
	while (q->next)
	{
		delete q->bullet;
		q=q->next;
		delete q->forward;
	}
	delete q;
	q=e_b_head;
	while (q->next)
	{
		delete q->bullet;
		q=q->next;
		delete q->forward;
	}
	delete q;
	if (Data::is_loading) {
		ist_keys->close();
		ist_random->close();
		delete ist_keys;
		delete ist_random;
	}else{
		ost_keys->close();
		ost_random->close();
		delete ost_keys;
		delete ost_random;		
	}
}

void GameScene::EnemyMake(){
	/*��,����,����ģʽ*/
	if (Data::mode<=GameMode::DIFFICULT){
		if (level!=(this->score+1)/SCOREPERLEVER+1){
			level_up_time=hge->Timer_GetTime();
			level=(this->score+1)/SCOREPERLEVER+1;
		}
		int score=this->score%SCOREPERLEVER;
		if (score<2000&&score>=1000&&(!boss)){boss=new Boss1(hge,"boss1.png",100,0);}
		if (score<5000&&score>=4000&&(!boss)){boss=new Boss2(hge,"boss2.png",100,0);}
		if (score<8000&&score>=7000&&(!boss)){boss=new Boss3(hge,"boss3.png",100,0);}
		if (score<11000&&score>=10000&&(!boss)){boss=new Boss4(hge,"boss4.png",100,0);last_boss=true;}
		if (Data::frames-timer>FPS*ENEMYMAKEGAP&&(!boss)){
			timer=Data::frames;
			EnemyNode* p=new EnemyNode();
			switch(Data::mode){
			case GameMode::EASY:
				p->enemy=new Enemy(hge,"enemy1.png",get_random(SCREENWIDTH),0,Data::enemy_v,Data::enemy_attack,Data::enemy_bullet_freq,Data::enemy_hp);//�����µ���
				break;
			case GameMode::NORMAL:
				if (get_random(2)==1){
					p->enemy=new Enemy(hge,"enemy1.png",get_random(SCREENWIDTH),0,
						Data::enemy_v,Data::enemy_attack,Data::enemy_bullet_freq,Data::enemy_hp);//�����µ���
				}else{
					p->enemy=new Enemy2(hge,"enemy2.png",get_random(SCREENWIDTH),0,
						Data::enemy_v,Data::enemy_attack,Data::enemy_bullet_freq,Data::enemy_hp);//�����µ���
				}
				break;
			case GameMode::DIFFICULT:
				p->enemy=new Enemy2(hge,"enemy2.png",get_random(SCREENWIDTH),0,Data::enemy_v,Data::enemy_attack,Data::enemy_bullet_freq,Data::enemy_hp);//�����µ���
				break;
			}
			add_enemy(&p);
		}
		return;
	}

	//�޾�ģʽ
	//���µ�ǰ�ȼ�
	if (level!=(this->score+1)/SCOREPERLEVER+1){
		level_up_time=hge->Timer_GetTime();
		level=(this->score+1)/SCOREPERLEVER+1;
	}
	int score=this->score%SCOREPERLEVER;
	if (score<2000&&score>=1000&&(!boss)){boss=new Boss1(hge,"boss1.png",100,0);}
	if (score<5000&&score>=4000&&(!boss)){boss=new Boss2(hge,"boss2.png",100,0);}
	if (score<8000&&score>=7000&&(!boss)){boss=new Boss3(hge,"boss3.png",100,0);}
	if (score<11000&&score>=10000&&(!boss)){boss=new Boss4(hge,"boss4.png",100,0);}

	switch(level){
	case 1:
		if (Data::frames-timer>ENEMYMAKEGAP*FPS&&(!boss)){
			timer=Data::frames;
			EnemyNode* p=new EnemyNode();
			p->enemy=new Enemy(hge,"enemy1.png",get_random(SCREENWIDTH),0,Data::enemy_v,Data::enemy_attack,Data::enemy_bullet_freq,Data::enemy_hp);//�����µ���
			GameScene::add_enemy(&p);
		}
		break;
	case 2:
		if (Data::frames-timer>ENEMYMAKEGAP*FPS&&(!boss)){
			timer=Data::frames;
			EnemyNode* p=new EnemyNode();
			if (get_random(2)==1)
				p->enemy=new Enemy(hge,"enemy1.png",get_random(SCREENWIDTH),0,
					Data::enemy_v,Data::enemy_attack,Data::enemy_bullet_freq,Data::enemy_hp);//�����µ���
			else
				p->enemy=new Enemy2(hge,"enemy2.png",get_random(SCREENWIDTH),0,
					Data::enemy_v,Data::enemy_attack,Data::enemy_bullet_freq,Data::enemy_hp);//�����µ���
			GameScene::add_enemy(&p);
		}
		break;
	case 3:
		if (Data::frames-timer>ENEMYMAKEGAP*FPS&&(!boss)){
			timer=Data::frames;
			EnemyNode* p=new EnemyNode();
			p->enemy=new Enemy2(hge,"enemy2.png",get_random(SCREENWIDTH),0,Data::enemy_v,Data::enemy_attack,Data::enemy_bullet_freq,Data::enemy_hp);//�����µ���
			GameScene::add_enemy(&p);
		}
		break;
	default:
		if (Data::frames-timer>1/(1.0/ENEMYMAKEGAP*FPS+(level-3)*0.2)&&(!boss)){
			timer=Data::frames;
			EnemyNode* p=new EnemyNode();
			p->enemy=new Enemy2(hge,"enemy2.png",get_random(SCREENWIDTH),0,Data::enemy_v,Data::enemy_attack,Data::enemy_bullet_freq,Data::enemy_hp);//�����µ���
			GameScene::add_enemy(&p);
		}
		break;
	}
}

void GameScene::get_keys(){
	if (gameover) return;
	if (Data::is_loading){
		for (int i=0;i<5;i++){
			(*ist_keys)>>keys[i];	
			if (keys[i]==-1) {
				gameover=true;
				d_t=hge->Timer_GetTime();
				break;
			}
		}
		return;
	}
	keys[SPACE]=hge->Input_GetKeyState(HGEK_SPACE);
	keys[UP]=hge->Input_GetKeyState(HGEK_UP);
	keys[DOWN]=hge->Input_GetKeyState(HGEK_DOWN);
	keys[LEFT]=hge->Input_GetKeyState(HGEK_LEFT);
	keys[RIGHT]=hge->Input_GetKeyState(HGEK_RIGHT);
	//������Ұ�����¼
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) {
		(*ost_keys)<<"-1\n";
		gameover=true;
		d_t=hge->Timer_GetTime();
	}else{
		for (int i=0;i<5;i++)
			(*ost_keys)<<keys[i]<<" ";
		(*ost_keys)<<endl;
	}
}

bool GameScene::logic_update(){
	/*
	1.�ƶ��л� (Boss) ���жϵл��Ƿ����
	2.�л������ӵ�
	(3.Boss�����ӵ�)
	4.�����������: ��ҷ����ӵ�
	5.���������ӵ�λ��
	6.�ж���ײ����
		(1)����ӵ���л�
		(2)�������Ʒ
		(3)�����л�
		(4)�����л��ӵ�(����Boss���ӵ�)
		((5)�����Boss,����ӵ���Boss)
	7.��������ƶ�����
	8.�ж���Ʒ����
	9.�ж����ʤ������
	*/
	get_keys();						//���ؼ���״̬(ѡ��Ӽ��̻����ļ�)
	if (gameover) return false;		//�����Ϸ�������ٽ����߼�����
	float dx=0;						
	float dy=0;
	EnemyMake();					//���ɵ���
	player->is_protected();			//���µ�ǰս��״̬(�Ƿ��ڱ���״̬)
 	/*1.�ƶ��л�,Boss �������ĵл�*/
	if (boss) boss->move(1);
	EnemyNode* q=e_head;
	EnemyNode* temp2;
	while (q->next!=0)
	{ 
		q->enemy->move(1);
		temp2=q->next;
		if (q->enemy->is_out()) {
			remove_enemy(&q);
			delete q->enemy;
			delete q;
		}
		q=temp2;
	}
	/*2.���˷����ӵ�*/
	q=e_head;
	while (q->next!=0)
	{
		if (q->enemy->attack()){ 
			BulletNode* p3;
			for (int i=0;i<q->enemy->get_b_num();i++){	
				p3=new BulletNode();
				//�����ӵ�(�涨����)
				if (q->enemy->get_b_pos(i).vx!=0||q->enemy->get_b_pos(i).vy!=0)
				p3->bullet=new Bullet(hge,"bullet2.png",
					q->enemy->get_b_pos(i).vx,q->enemy->get_b_pos(i).vy,
					20,150,
					q->enemy->get_middle_x()+q->enemy->get_b_pos(i).x,q->enemy->get_middle_y()+q->enemy->get_b_pos(i).y);
				else
				//����׷�ٵ�
				p3->bullet=new Bullet(hge,"bullet3.png",
					player->get_x()-(q->enemy->get_middle_x()+q->enemy->get_b_pos(i).x),
					player->get_y()-(q->enemy->get_middle_y()+q->enemy->get_b_pos(i).y),
					20,150,
					q->enemy->get_middle_x()+q->enemy->get_b_pos(i).x,q->enemy->get_middle_y()+q->enemy->get_b_pos(i).y);
				add_enemy_bullet(&p3);
			}
		}
		q=q->next;
	}
	/*3.boss�����ӵ�*/
	if (boss) if (boss->attack()){ 
		BulletNode* p3;
		for (int i=0;i<boss->get_b_num();i++){	
			p3=new BulletNode();
			if (boss->get_b_pos(i).vx!=0||boss->get_b_pos(i).vy!=0)
				p3->bullet=new Bullet(hge,"bullet2.png",
					boss->get_b_pos(i).vx,boss->get_b_pos(i).vy,
					20,150,
					boss->get_middle_x()+boss->get_b_pos(i).x,boss->get_middle_y()+boss->get_b_pos(i).y);
			else 
				p3->bullet=new Bullet(hge,"bullet3.png",
					player->get_x()-(boss->get_middle_x()+boss->get_b_pos(i).x),
					player->get_y()-(boss->get_middle_y()+boss->get_b_pos(i).y),
					20,150,
					boss->get_middle_x()+boss->get_b_pos(i).x,boss->get_middle_y()+boss->get_b_pos(i).y);	
				add_enemy_bullet(&p3);
		}
	}
	/*4.��ҷ��ӵ�*/
	if (keys[SPACE]){
		if (GameScene::player->is_attack()){
			//�ӵ�����
			//�����(player->get_middle_x(),player->get_y())
			for (int i=0;i<player->get_b_num();i++){
				BulletNode* p1=new BulletNode();
				p1->bullet=new Bullet(hge,"bullet.png",0,-1,player->get_attack());
				p1->bullet->set_position(player->get_middle_x()+player->get_b_pos(i).x,player->get_y()+player->get_b_pos(i).y);
				add_bullet(&p1);
			}
			hge->Effect_PlayEx(snd,20);
		}
	}
	/*5.�����ӵ�λ��*/
	BulletNode* p=b_head;
	BulletNode* temp;
	while (p->next!=0)
	{
		p->bullet->move(1);
		temp=p->next;
		if (p->bullet->is_out()) {
			remove_bullet(&p);
			delete p->bullet;
			delete p;
		}
		p=temp;
	}
	p=e_b_head;
	while (p->next!=0)
	{
		p->bullet->move(1);
		temp=p->next;
		if (p->bullet->is_out()) {
			remove_enemy_bullet(&p);
			delete p->bullet;
			delete p;
		}
		p=temp;
	}
	/*6.�ж���ײ����*/
	/*(1)����ӵ���л�*/
	p=b_head;
	while (p->next!=0)
	{
		temp=p->next;
		q=e_head;
		while (q->next!=0)
		{
			temp2=q->next;
			if (IsCollision(p->bullet,p->bullet->get_x(),p->bullet->get_y(),q->enemy,q->enemy->get_x(),q->enemy->get_y()))
			{
				score+=p->bullet->get_damage();//�Ʒ�ԭ��1:������ӵ��򵽵л�����ʱ ������л���ʧ������ֵ��ȵķ���
				if (q->enemy->attacked(p->bullet->get_damage())){
					BombNode* p1=new BombNode();
					p1->bomb=new Bomb(hge,q->enemy->get_x(),q->enemy->get_y(),q->enemy->get_x()+q->enemy->GetWidth(),q->enemy->get_y()+q->enemy->GetHeight());
					add_bomb(&p1);
					score+=q->enemy->get_hp_max();//�Ʒ�ԭ��3:������ӵ�����л�ʱ ���ϵл��ķ��� 
					make_item(q->enemy->get_x(),q->enemy->get_y());//��������
					remove_enemy(&q);
					delete q->enemy;
					delete q;
				}
				remove_bullet(&p);
				delete p->bullet;
				delete p;
				break;
			}
			q=temp2;
		}
		p=temp;
	}
	/*(2)�������Ʒ*/
	ItemNode* i=i_head;
	ItemNode* tempi;
	while (i->next!=0){
		tempi=i->next;
		if (IsCollision(player,player->get_x(),player->get_y(),i->item,i->item->get_x(),i->item->get_y())){
			switch (i->item->get_type()){
			case ItemType::HP_PLUS:
				player->add_hp(i->item->get_value());
				break;
			case ItemType::PROTECT:
				player->protect(i->item->get_value()*FPS);
				break;
			case ItemType::POISON:
				if (player->attacked(i->item->get_value())){
					gameover=true;
					d_t=hge->Timer_GetTime();
				}
				break;
			case ItemType::CLEAR:{
				EnemyNode *q=e_head;
				/*ɾ�����е���*/
				while (q->next)
				{
					BombNode* p1=new BombNode();
					p1->bomb=new Bomb(hge,q->enemy->get_x(),q->enemy->get_y(),q->enemy->get_x()+q->enemy->GetWidth(),q->enemy->get_y()+q->enemy->GetHeight());
					add_bomb(&p1);
					delete q->enemy;
					q=q->next;
					delete q->forward;
				}
				delete q;
				e_head=new EnemyNode;
				break;
				}
			case ItemType::UPGRADE:
				player->upgrade(i->item->get_value()*FPS);
			}
			remove_item(&i);
			delete i->item;
			delete i;
		}
		i=tempi;
	}
	/*(3)�����л�*/
	q=e_head;
	while (q->next!=0){
		temp2=q->next;
		if (IsCollision(q->enemy,q->enemy->get_x(),q->enemy->get_y(),player,player->get_x(),player->get_y())){
			score+=q->enemy->get_hp();//�Ʒ�ԭ��2:�������л���ײ ������л���������ֵ��ȵķ���
			if (player->attacked(q->enemy->get_hp())){
				d_t=hge->Timer_GetTime();
				gameover=true;
			}
			make_item(q->enemy->get_x(),q->enemy->get_y());//��������
			remove_enemy(&q);
			delete q->enemy;
			delete q;
		}
		q=temp2;
	}
	/*(4)������ӵ�*/
	p=e_b_head;
	while (p->next!=0){
		temp=p->next;
		if (IsCollision(p->bullet,p->bullet->get_x(),p->bullet->get_y(),player,player->get_x(),player->get_y())){
			if (player->attacked(p->bullet->get_damage()))
			{
				d_t=hge->Timer_GetTime();
				gameover=true;
			}
			remove_enemy_bullet(&p);
			delete p->bullet;
			delete p;
		}
		p=temp;
	}
	/*(5)�ӵ���Boss,�����Boss*/
	if (boss){
		p=b_head;
		while (p->next){
			temp=p->next;
			if (IsCollision(p->bullet,p->bullet->get_x(),p->bullet->get_y(),boss,boss->get_x(),boss->get_y())){
				score+=p->bullet->get_damage();//�Ʒ�ԭ��1:������ӵ��򵽵л�����ʱ ������л���ʧ������ֵ��ȵķ���
				if (boss->attacked(p->bullet->get_damage())){
					//���뱬ըЧ��
					BombNode* p1=new BombNode();
					p1->bomb=new Bomb(hge,boss->get_x(),boss->get_y(),boss->get_x()+boss->GetWidth(),boss->get_y()+boss->GetHeight());
					add_bomb(&p1);
					score+=boss->get_hp_max();//�Ʒ�ԭ��3:������ӵ�����л�ʱ ���ϵл��ķ��� 
					delete boss;
					boss=NULL;
				}
				remove_bullet(&p);
				delete p->bullet;
				delete p;
				break;
			}
			p=temp;
		}
	}
	if (boss)
	if (IsCollision(player,player->get_x(),player->get_y(),boss,boss->get_x(),boss->get_y())){
		score+=boss->get_hp();//�Ʒ�ԭ��2:�������л���ײ ������л���������ֵ��ȵķ���
		d_t=hge->Timer_GetTime();
		gameover=true;
		delete boss;
		boss=NULL;
	}

	/*7.����player�ƶ�����*/
	if (keys[LEFT]){
		dx=-player->get_v()/FPS;
	}
	if (keys[RIGHT]){
		dx=+player->get_v()/FPS;
	}
	if (keys[UP]){
		dy=-player->get_v()/FPS;
	}
	if (keys[DOWN]){
		dy=+player->get_v()/FPS;
	}
	if (dx!=0||dy!=0){
		dx=player->get_x()+dx;
		dy=player->get_y()+dy;
		if (dx>=-(player->GetWidth()/2)
			&&	dx<=hge->System_GetState(HGE_SCREENWIDTH)-player->GetWidth()/2
			&&  dy>=0
			&&	dy<=hge->System_GetState(HGE_SCREENHEIGHT)-player->GetHeight()/2
			)
		player->set_position(dx,dy);
	}
	
	/*8.�ж���Ʒ����*/
	i=i_head;
	while (i->next!=0){
		tempi=i->next;
		i->item->move(1);
		if (i->item->is_out()){
			remove_item(&i);
			delete i->item;
			delete i;
		}
		i=tempi;
	}
	/*9.�ж����ʤ������*/
	if (Data::mode<=GameMode::DIFFICULT&&last_boss&&(!boss)){
		gameover=true;
		d_t=hge->Timer_GetTime();
		next_scene=WIN;
	}
	return false;
}

bool GameScene::render(){
	//���Ʊ���
	background->Render();
	fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
	/*��ǰ�ؿ�״̬*/
	if (Data::mode!=ENDLESS){
		char* c;
		switch (Data::mode){
		case GameMode::EASY:
			c="Easy Mode";
			break;
		case GameMode::NORMAL:
			c="Normal Mode";
			break;
		case GameMode::DIFFICULT:
			c="Difficult Mode";
			break;
		}
		//���Ƶ�ǰģʽ
		float del_t=hge->Timer_GetTime()-level_up_time;
		if (del_t<2){
			fnt_level->SetColor((int(del_t/2.0*0xff)<<24)+0xffffff);
			fnt_level->printf(50,50,HGETEXT_LEFT,c);
	
		}else if (del_t>=2&&del_t<4){
			fnt_level->SetColor(0xffffffff);
			fnt_level->printf(50,50,HGETEXT_LEFT,c);
		}else if (del_t>=4&&del_t<6){
			fnt_level->SetColor((int((6-del_t)/2.0*0xff)<<24)+0xffffff);
			fnt_level->printf(50,50,HGETEXT_LEFT,c);
		}
	}else{
		//���Ƶȼ�
		float del_t=hge->Timer_GetTime()-level_up_time;
		if (del_t<2){
			fnt_level->SetColor((int(del_t/2.0*0xff)<<24)+0xffffff);
			fnt_level->printf(50,50,HGETEXT_LEFT,"Level %d", level);
	
		}else if (del_t>=2&&del_t<4){
			fnt_level->SetColor(0xffffffff);
			fnt_level->printf(50,50,HGETEXT_LEFT,"Level %d", level);
		}else if (del_t>=4&&del_t<6){
			fnt_level->SetColor((int((6-del_t)/2.0*0xff)<<24)+0xffffff);
			fnt_level->printf(50,50,HGETEXT_LEFT,"Level %d", level);
		}
	}
	//���Ʒ���,Ѫ������
	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(0,520,HGETEXT_LEFT,"SCORE:\n%d",score);
	fnt->printf(0,580,HGETEXT_LEFT,"HP:");
	//������ҷɻ�
	player->Render();
	//����Boss
	if (boss) boss->Render();
	//��������ӵ�
	BulletNode* p=b_head;
	while (p->next!=0)
	{
		p->bullet->Render();
		p=p->next;
	}
	//���Ƶл��ӵ�
	p=e_b_head;
	while (p->next!=0)
	{
		p->bullet->Render();
		p=p->next;
	}
	//���Ƶл�
	EnemyNode* q=e_head;
	while (q->next!=0)
	{
		q->enemy->Render();
		q=q->next;
	}
	//���Ʊ�ըЧ��
	BombNode* b=bomb_head;
	BombNode* temp;
	while (b->next!=0){
        temp=b->next;
		b->bomb->Render();
		if (b->bomb->need_delete()){
			remove_bomb(&b);
			delete b->bomb;
			delete b;
		}
		b=temp;
	}
	//���Ƶ�����Ʒ
	ItemNode* i=i_head;
	while (i->next!=0){
		i->item->Render();
		i=i->next;
	}
	return false;
}

bool GameScene::change(){
	bool temp=gameover&&(hge->Timer_GetTime()-d_t>0.5);
	if (temp){
		gameover=false;
		d_t=hge->Timer_GetTime();
	}
	return temp;
}

int GameScene::get_change_type(){
	return next_scene;
}

bool GameScene::IsCollision(hgeSprite* spr1, float x1, float y1, hgeSprite* spr2, float x2, float y2, HTEXTURE hot1, HTEXTURE hot2, DWORD airColor)
{
    /** Set the rect */
    hgeRect r1, r2;
    r1.Set(x1, y1, x1 + spr1->GetWidth(), y1 + spr1->GetHeight());
    r2.Set(x2, y2, x2 + spr2->GetWidth(), y2 + spr2->GetHeight());

    /** Test for the intersect of rectangles */
    if(r1.Intersect(&r2))
    {
        int x[] = { x1, x2, x1 + spr1->GetWidth(), x2 + spr2->GetWidth() };
        int y[] = { y1, y2, y1 + spr1->GetHeight(), y2 + spr2->GetHeight() };
        std::sort(x, x + 4);
        std::sort(y, y + 4);
        hgeRect r;

        /** Set the rectangle area where the two rectangles intersected. */
        r.Set(x[1], y[1], x[2], y[2]);

        /** The start point of sprite1 and sprite2. (From the intersected area) */
        int sx1, sy1, sx2, sy2;
        sx1 = x[1] - x1;
        sy1 = y[1] - y1;
        sx2 = x[1] - x2;
        sy2 = y[1] - y2;

        /** Get the "hotspot" of texture */
        HTEXTURE hTex1 = hot1;
        HTEXTURE hTex2 = hot2;
        if(hTex1 == 0) hTex1 = spr1->GetTexture();
        if(hTex2 == 0) hTex2 = spr2->GetTexture();

        float tx1, ty1, tw1, th1, tx2, ty2, tw2, th2;
        int w1 = hge->Texture_GetWidth(hTex1), w2 = hge->Texture_GetWidth(hTex2);
        spr1->GetTextureRect(&tx1, &ty1, &tw1, &th1);
        spr2->GetTextureRect(&tx2, &ty2, &tw2, &th2);

        DWORD* color1 = new DWORD[(x[2] - x[1]) * (y[2] - y[1])];
        DWORD* color2 = new DWORD[(x[2] - x[1]) * (y[2] - y[1])];
        DWORD* color;

        /** Copy the effectivearea of texture 1 */
        color = hge->Texture_Lock(hTex1, true);
        for(int i = 0; i < y[2] - y[1]; i++)
        {
            for(int j = 0; j < x[2] - x[1]; j++)
            { 
                color1[i * (x[2] - x[1]) + j] = color[((int)ty1 + sy1) * w1 + (int)tx1 + sx1 + i * w1 + j];
            } 
        } 
        hge->Texture_Unlock(hTex1);

        /** Copy the effectivearea of texture 2 */
        color = hge->Texture_Lock(hTex2, true);
        for(int i = 0; i < y[2] - y[1]; i++)
        {
            for(int j = 0; j < x[2] - x[1]; j++) 
            { 
                color2[i * (x[2] - x[1]) + j] = color[((int)ty2 + sy2) * w2 + (int)tx2 + sx2 + i * w2 + j]; 
            } 
        } 
        hge->Texture_Unlock(hTex2);

        /** Test for the collision */
        for(int i = 0; i < y[2] - y[1]; i++)
        {
            for(int j = 0; j < x[2] - x[1]; j++)
            {
                if(color1[i * (x[2] - x[1]) + j] != airColor && color2[i * (x[2] - x[1]) + j] != airColor)
                {
                    delete []color1;
                    delete []color2;

                    return true;
                }
            }
        }
        delete []color1;
        delete []color2;
        return false;
    }
    else return false;
}

bool GameScene::is_changing(){
	return gameover;
}

float GameScene::get_gap(){
	return hge->Timer_GetTime()-d_t;
}

void GameScene::make_item(float x,float y){
	int type=get_random(10);
	ItemNode* p;
	switch(type){
	case 0:case 1:
		/*HP���ӵ���Ʒ*/
		p=new ItemNode();
		p->item=new Item(hge,ItemType::PROTECT,x,y);
		add_item(&p);
		return;
	case 2:case 3:
		/*P����Ĥ*/
		p=new ItemNode();
		p->item=new Item(hge,ItemType::HP_PLUS,x,y);
		add_item(&p);
		return;
	case 4:case 5:
		/*��ҩ*/
		p=new ItemNode();
		p->item=new Item(hge,ItemType::POISON,x,y);
		add_item(&p);
		return;
	case 6:
		/*�峡��*/
		p=new ItemNode();
		p->item=new Item(hge,ItemType::CLEAR,x,y);
		add_item(&p);
		return;
	case 7:
		/*�ӵ�����*/
		p=new ItemNode();
		p->item=new Item(hge,ItemType::UPGRADE,x,y);
		add_item(&p);
		return;
	}
}

int GameScene::get_random(int x){
	if (Data::is_loading==1){
		int temp;
		(*ist_random)>>temp;
		return temp;
	}
	int temp=rand()%x;
	(*ost_random)<<temp<<endl;
	return temp;
}


void GameScene::add_bullet(BulletNode** tp){
	BulletNode* p=*tp;
	p->next=b_head;
	b_head->forward=p;
	b_head=p;
}
void GameScene::remove_bullet(BulletNode** tp){
	BulletNode* p=*tp;
	p->next->forward=p->forward;
	if (p->forward) p->forward->next=p->next;
	else b_head=p->next;
}

void GameScene::add_bomb(BombNode** tp){
	BombNode* p=*tp;
	p->next=bomb_head;
	bomb_head->forward=p;
	bomb_head=p;
}
void GameScene::remove_bomb(BombNode** tp){
	BombNode* p=*tp;
	p->next->forward=p->forward;
	if (p->forward) p->forward->next=p->next;
	else bomb_head=p->next;
}

void GameScene::add_item(ItemNode** tp){
	ItemNode* p=*tp;
	p->next=i_head;
	i_head->forward=p;
	i_head=p;
}
void GameScene::remove_item(ItemNode** tp){
	ItemNode* p=*tp;
	p->next->forward=p->forward;
	if (p->forward) p->forward->next=p->next;
	else i_head=p->next;
}

void GameScene::add_enemy(EnemyNode** tp){
	EnemyNode* p=*tp;
	p->next=e_head;
	e_head->forward=p;
	e_head=p;
}
void GameScene::remove_enemy(EnemyNode** tp){
	EnemyNode* p=*tp;
	p->next->forward=p->forward;
	if (p->forward) p->forward->next=p->next;
	else e_head=p->next;
}

void GameScene::add_enemy_bullet(BulletNode** tp){
	BulletNode* p=*tp;
	p->next=e_b_head;
	e_b_head->forward=p;
	e_b_head=p;
}
void GameScene::remove_enemy_bullet(BulletNode** tp){
	BulletNode* p=*tp;
	p->next->forward=p->forward;
	if (p->forward) p->forward->next=p->next;
	else e_b_head=p->next;
}
