#include "bullet.h"
#include "exception.h"

Bullet::Bullet(HGE* hge,const char* s,float direction_x,float direction_y,float d,float vv,float position_x,float position_y)
	:hgeSprite(0,0,0,0,0)
{
	/*���õ�λ��������*/
	if (direction_x==0&&direction_y==0) {
		dir_x=0;
		dir_y=0;
	}else{
		float n=norm(direction_x,direction_y);
		dir_x=direction_x/n;
		dir_y=direction_y/n;
		pos_x=position_x;
		pos_y=position_y;
	}
	v=vv;
	damage=d;
	/*����ͼƬ*/
	HTEXTURE temp=hge->Texture_Load(s);
	if (!temp) {
		MessageBoxA(NULL,hge->System_GetErrorMessage(),"Error",MB_OK|MB_ICONERROR|MB_APPLMODAL);
		throw(Exception(0));
		return;
	}
	SetTexture(temp);//������������������
	SetTextureRect(0,0
		,hge->Texture_GetWidth(temp),hge->Texture_GetHeight(temp));
}
void Bullet::move(float t){
	//�ط������������ƶ�
	pos_x+=dir_x*v*t/FPS;
	pos_y+=dir_y*v*t/FPS;
}

void Bullet::Render(){
	//����
	if (pos_x==NOT_SET_POS||pos_y==NOT_SET_POS) return;
	hgeSprite::Render(pos_x,pos_y);
}
void Bullet::Render(float x,float y){
	//����
	hgeSprite::Render(x,y);
}
bool Bullet::set_v(float vv){
	if (vv>0){
		v=vv;
		return true;
	}
	return false;
}
void Bullet::set_position(float px,float py){
	pos_x=px;
	pos_y=py;
}	
bool Bullet::is_out(){
	if (pos_x>SCREENWIDTH||pos_y>SCREENHEIGHT||pos_x<-GetWidth()||pos_y<-GetHeight())
	{
		return true;
	}
	return false;
}
float Bullet::get_x(){return pos_x;}
float Bullet::get_y(){return pos_y;}
float Bullet::get_damage(){return damage;}