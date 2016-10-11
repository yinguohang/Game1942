#include "background.h"
#include "exception.h"

Background::Background(HGE* hge,const char* s):
	hgeSprite(0,0,0,0,0)
{
	this->hge=hge;							//初始化hge
	t_y=hge->Timer_GetTime();				//初始化时间控制参数
	v=50;									//初始化背景滚动速度
	HTEXTURE temp=hge->Texture_Load(s);		//载入当前背景纹理
	if (!temp) {
		//如果没有成功载入纹理 报异常
		MessageBoxA(NULL,hge->System_GetErrorMessage(),"Error",MB_OK|MB_ICONERROR|MB_APPLMODAL);
		throw(Exception(0));
		return;
	}
	/*设置纹理坐标*/
	SetTexture(temp);
	SetTextureRect(0,t_y
		,hge->Texture_GetWidth(temp),hge->Texture_GetHeight(temp));
}

void Background::Render(){
	hgeSprite::Render(0,0);													//渲染当前背景
	SetTextureRect(0,(hge->Timer_GetTime()-t_y)*v,GetWidth(),GetHeight());	//移动背景纹理坐标以实现滚动效果
}
