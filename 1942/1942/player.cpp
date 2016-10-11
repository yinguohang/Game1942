#include "player.h"
#include "default.h"
#include "exception.h"

bool Player::attacked(int x){
	if (hp<=0) return false;//已经死掉了
	if (!is_protected())
		hp-=x;
	if (hp<=0) return true;
	return false;
}

float Player::get_v(){
	return v;
}

Player::Player(HGE* hge,const char* s,float v ,float att, float freq, float hp):
	hgeSprite(0,0,0,0,0)
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
	set_position((hge->System_GetState(HGE_SCREENWIDTH)-hge->Texture_GetWidth(temp))/2,500);
	b_num=2;
	b_pos=new Point[2];
	b_pos[0].x=-10;
	b_pos[0].y=-22;
	b_pos[0].vx=0;
	b_pos[0].vy=1;
	b_pos[1].x=-1;
	b_pos[1].y=-22;
	b_pos[1].vx=0;
	b_pos[1].vy=-1;
	lasttime=Data::frames;
	this->v=v;
	this->att=att;
	b_freq=freq;
	this->hp=hp;
	hp_max=hp;
	p_t=-1;
}
void Player::Render(){
	hgeSprite::Render(x,y);
	//绘制血条
	hgeQuad temp;
	temp.v[0].x=38; temp.v[0].y=580;
	temp.v[1].x=142; temp.v[1].y=580;
	temp.v[2].x=142; temp.v[2].y=600;
	temp.v[3].x=38; temp.v[3].y=600;
	temp.tex=0;
	temp.blend=BLEND_COLORADD|BLEND_ALPHAADD|BLEND_NOZWRITE;
	temp.v[0].col=0x22999999;
	temp.v[1].col=0x22999999;
	temp.v[2].col=0x22999999;
	temp.v[3].col=0x22999999;
	temp.v[0].z=0.5f;
	temp.v[1].z=0.5f;
	temp.v[2].z=0.5f;
	temp.v[3].z=0.5f;
	hge->Gfx_RenderQuad(&temp);
	if (hp<0) return;
	temp.v[0].x=40; temp.v[0].y=582;
	temp.v[1].x=40+hp; temp.v[1].y=582;
	temp.v[2].x=40+hp; temp.v[2].y=598;
	temp.v[3].x=40; temp.v[3].y=598;
	temp.tex=0;
	temp.v[0].col=0xFFFF0000;
	temp.v[1].col=0xFFFFFF00;
	temp.v[2].col=0xFFFFFF00;
	temp.v[3].col=0xFFFF0000;
	temp.v[0].z=0.6f;
	temp.v[1].z=0.6f;
	temp.v[2].z=0.6f;
	temp.v[3].z=0.6f;
	hge->Gfx_RenderQuad(&temp);
}
void Player::Render(float xx,float yy){
	hgeSprite::Render(xx,yy);
}
void Player::set_position(float xx,float yy){
	x=xx;
	y=yy;
}

float Player::get_x(){return x;}
float Player::get_y(){return y;}
float Player::get_middle_x(){return x+GetWidth()/2;}
float Player::get_meddle_y(){return y+GetHeight()/2;}
bool Player::is_attack(){
	if (Data::frames-lasttime>=FPS/b_freq) {
		lasttime=Data::frames;
		return true;
	}
	return false;
}

float Player::get_attack(){
	return att;
}

void Player::protect(float dt){
	HTEXTURE tex=hge->Texture_Load("plane_protected.png");
	SetTexture(tex);
	p_t=Data::frames;
	p_l_t=dt;
}

bool Player::is_protected(){
	if (p_t==-1) return false;
	if (Data::frames-p_t>p_l_t){
		HTEXTURE tex=hge->Texture_Load("plane1.png");
		SetTexture(tex);
		p_t=-1;
		return false;
	}
	return true;
}

void Player::upgrade(float dt){
	b_num=3;
	delete b_pos;
	b_pos=new Point[3];
	b_pos[0].x=-14;
	b_pos[0].y=-22;
	b_pos[0].vx=0;
	b_pos[0].vy=1;
	b_pos[1].x=2;
	b_pos[1].y=-22;
	b_pos[1].vx=0;
	b_pos[1].vy=-1;
	b_pos[2].x=-6;
	b_pos[2].y=-22;
	b_pos[2].vx=0;
	b_pos[2].vy=-1;
	b_t=Data::frames;
	b_l_t=dt;
}

bool Player::is_upgraded(){
	if (b_t==-1) return false;
	if (Data::frames-b_t>b_l_t){
		delete b_pos;
		b_num=2;
		b_pos=new Point[2];
		b_pos[0].x=-10;
		b_pos[0].y=-22;
		b_pos[0].vx=0;
		b_pos[0].vy=1;
		b_pos[1].x=-1;
		b_pos[1].y=-22;
		b_pos[1].vx=0;
		b_pos[1].vy=-1;
		b_t=-1;
		return false;
	}
	return true;
}

int Player::get_b_num(){
	is_upgraded();
	return b_num;
}

Point Player::get_b_pos(int x){
	return b_pos[x];
}
