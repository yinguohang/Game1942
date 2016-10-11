#include "bomb.h"

Bomb::Bomb(HGE* hge,float x1,float y1,float x2,float y2)
	:hgeSprite(0,0,0,0,0){
	frame=0;
	HTEXTURE tex=hge->Texture_Load("bomb.png");										//加载爆炸效果图片
	if (!tex) return;
	SetTexture(tex);
	SetTextureRect(0,0,hge->Texture_GetWidth(tex)/8,hge->Texture_GetHeight(tex));	//设置纹理坐标
	this->x1=x1;
	this->y1=y1;
	this->x2=x2;
	this->y2=y2;
}

void Bomb::Render(){
 	hgeSprite::RenderStretch(x1,y1,x2,y2);//在规定范围填充
	frame+=1;
	int temp=frame;
	SetTextureRect(GetWidth()*(int)temp,0,GetWidth(),GetHeight());//变换纹理坐标 移至下一帧
}

bool Bomb::need_delete(){
	return (frame>=8);//如果帧数>8那么则需要delete
}