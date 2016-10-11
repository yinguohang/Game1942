#include "boss.h"
#include <cmath>
#include "drawer.h"

Boss1::Boss1(HGE* hge,const char* s,float x,float y,float vv,float att,float freq,float hp):
	Enemy(hge,s,x,y,vv,att,freq,hp){
		pos_y-=GetHeight();
		delete b_pos;
		//设置boss子弹的位置
		b_num=5;
		b_pos=new Point[5];
		b_pos[0].x=0;	b_pos[0].y=GetHeight()/2+5;
		b_pos[0].vx=0;	b_pos[0].vy=1;
		b_pos[1].x=GetWidth()/4;	b_pos[1].y=GetHeight()/2;
		b_pos[1].vx=1;	b_pos[1].vy=1;
		b_pos[2].x=-GetWidth()/4;	b_pos[2].y=GetHeight()/2;
		b_pos[2].vx=-1;	b_pos[2].vy=1;
		b_pos[3].x=GetWidth()/2;	b_pos[3].y=0;
		b_pos[3].vx=1;	b_pos[3].vy=0;
		b_pos[4].x=-GetWidth()/2;	b_pos[4].y=0;
		b_pos[4].vx=-1;	b_pos[4].vy=0;
		d=1;
	}

void Boss1::move(float t){
	//移动 下降到100之后左右移动
	if (pos_y>=100){
		if (pos_x<20) d=1;
		if (pos_x>380-GetWidth()) d=-1;
		pos_x+=d*v*t/FPS;
		return;
	} 
	pos_y+=t*v/FPS;
}

Boss2::Boss2(HGE* hge,const char* s,float x,float y,float vv,float att,float freq,float hp):
	Enemy(hge,s,x,y,vv,att,freq,hp){
		//设置boss子弹的位置
		pos_y-=GetHeight();
		delete b_pos;
		b_num=8;
		b_pos=new Point[8];
		for (int i=0;i<8;i++)
		{
			float temp=i*3.14/4;
			b_pos[i].x=cos(temp)*(GetWidth()/2+10);
			b_pos[i].y=sin(temp)*GetHeight()/2;
			b_pos[i].vx=cos(temp);
			b_pos[i].vy=sin(temp);
		}
		this->freq=3;
		d=1;
	}

void Boss2::move(float t){
	//移动 下降到100之后左右移动
	if (pos_y>=100){
		if (pos_x<20) d=1;
		if (pos_x>380-GetWidth()) d=-1;
		pos_x+=d*v*t/FPS;
		return;
	} 
	pos_y+=t*v/FPS;
}

Boss3::Boss3(HGE* hge,const char* s,float x,float y,float vv,float att,float freq,float hp):
	Enemy(hge,s,x,y,vv,att,freq,hp){
		//设置boss子弹的位置
		pos_y-=GetHeight();
		delete b_pos;
		b_num=5;
		b_pos=new Point[5];
		for (int i=0;i<5;i++)
		{
			float temp=i*3.14/4;
			b_pos[i].x=20*(i-2);
			b_pos[i].y=GetHeight()/2+5;
			b_pos[i].vx=0;
			b_pos[i].vy=0;
		}
		this->freq=1;
		d=1;
	}

void Boss3::move(float t){
	//移动 下降到100之后左右移动
	if (pos_y>=100){
		if (pos_x<20) d=1;
		if (pos_x>380-GetWidth()) d=-1;
		pos_x+=d*v*t/FPS;
		return;
	} 
	pos_y+=t*v/FPS;
}

Boss4::Boss4(HGE* hge,const char* s,float x,float y,float vv,float att,float freq,float hp):
	Enemy(hge,s,x,y,vv,att,freq,hp){
		//设置boss子弹的位置
		pos_y-=GetHeight();
		this->freq=10;
		pos=0;
		d=1;
		v=100;
	}

void Boss4::move(float t){
	//移动 下降到100之后左右移动
	if (pos_y>=100){
		if (pos_x<20) d=1;
		if (pos_x>380-GetWidth()) d=-1;
		pos_x+=d*v*t/FPS;
		return;
	} 
	pos_y+=t*v/FPS;
}

bool Boss4::attack(){
	//攻击函数
	if (Data::frames-t>FPS/freq){
		float r=sqrt(GetWidth()*GetWidth()+GetHeight()*GetHeight())/2;
		float rad=3.14/4+pos/8.0*3.14;
		if (rad>=3.14*3/4) rad=3.14*3/2-rad;
		b_pos[0].x=r*cos(rad);
		b_pos[0].y=r*sin(rad);
		b_pos[0].vx=cos(rad);
		b_pos[0].vy=sin(rad);
		t=Data::frames;
		pos=(pos+1)%8;
		return true;
	}
	return false;
}