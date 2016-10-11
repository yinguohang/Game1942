#include"enemy.h"
#include "exception.h"
#include "drawer.h"

float Enemy::get_hp(){
	return hp;
}

Enemy::Enemy(HGE* hge,const char* s,float x,float y,float vv,float att,float freq,float hp)
		:hgeSprite(0,0,0,0,0)
{
	//加载图片资源
	HTEXTURE temp=hge->Texture_Load(s);
	if (!temp) {
		MessageBoxA(NULL,hge->System_GetErrorMessage(),"Error",MB_OK|MB_ICONERROR|MB_APPLMODAL);
		throw(Exception(0));
		return;
	}
	SetTexture(temp);
	SetTextureRect(0,0
		,hge->Texture_GetWidth(temp),hge->Texture_GetHeight(temp));
	//设置初始参数
	v=vv;
	this->freq=freq;
	pos_x=x;
	pos_y=y;
	this->hp=hp;
	hp_max=hp;
	t=Data::frames;
	this->att=att;
	b_num=1;
	b_pos=new Point(0,1+GetHeight()/200);
}
void Enemy::set_position(float x,float y){pos_x=x;pos_y=y;}
void Enemy::move(float t){
	pos_y+=t*v/FPS;
}
void Enemy::Render(){
	hgeSprite::Render(pos_x,pos_y);
	//血条绘制
	hgeQuad temp;
	temp.v[0].x=pos_x+5; temp.v[0].y=pos_y-10;
	temp.v[1].x=pos_x+hp/hp_max*GetWidth(); temp.v[1].y=pos_y-10;
	temp.v[2].x=pos_x+hp/hp_max*GetWidth(); temp.v[2].y=pos_y-3;
	temp.v[3].x=pos_x+5; temp.v[3].y=pos_y-3;
	temp.tex=0;
	temp.v[0].col=0xFFFF0000;
	temp.v[1].col=0xFFFF0000;
	temp.v[2].col=0xFFFF0000;
	temp.v[3].col=0xFFFF0000;
	temp.v[0].z=0.5f;
	temp.v[1].z=0.5f;
	temp.v[2].z=0.5f;
	temp.v[3].z=0.5f;
	hge->Gfx_RenderQuad(&temp);
}
void Enemy::Render(float x,float y){
	hgeSprite::Render(x,y);
}
bool Enemy::is_out(){
	if (pos_y>SCREENHEIGHT) {
		return true;
	}
	return false;
}
float Enemy::get_x(){return pos_x;}
float Enemy::get_y(){return pos_y;}
float Enemy::get_hp_max(){return hp_max;}

bool Enemy::attacked(int x){
	hp-=x;
	if (hp<=0) return true;
	return false;
}
bool Enemy::attack(){
	if (Data::frames-t>FPS/freq){
		t=Data::frames;
		return true;
	}
	return false;
}


int Enemy::get_b_num(){return b_num;}
Point Enemy::get_b_pos(int x){return b_pos[x];}
float Enemy::get_middle_x(){return pos_x+GetWidth()/2;}
float Enemy::get_middle_y(){return pos_y+GetHeight()/2;}

Enemy::~Enemy(){
	delete b_pos;
}

Enemy2::Enemy2(HGE* hge,const char* s,float x,float y,float vv,float att,float freq,float hp)
:Enemy(hge,s,x,y,vv,att,freq,hp){
	b_pos[0].vx=0;
	b_pos[0].vy=0;
}