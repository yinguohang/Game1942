#include "bomb.h"

Bomb::Bomb(HGE* hge,float x1,float y1,float x2,float y2)
	:hgeSprite(0,0,0,0,0){
	frame=0;
	HTEXTURE tex=hge->Texture_Load("bomb.png");										//���ر�ըЧ��ͼƬ
	if (!tex) return;
	SetTexture(tex);
	SetTextureRect(0,0,hge->Texture_GetWidth(tex)/8,hge->Texture_GetHeight(tex));	//������������
	this->x1=x1;
	this->y1=y1;
	this->x2=x2;
	this->y2=y2;
}

void Bomb::Render(){
 	hgeSprite::RenderStretch(x1,y1,x2,y2);//�ڹ涨��Χ���
	frame+=1;
	int temp=frame;
	SetTextureRect(GetWidth()*(int)temp,0,GetWidth(),GetHeight());//�任�������� ������һ֡
}

bool Bomb::need_delete(){
	return (frame>=8);//���֡��>8��ô����Ҫdelete
}