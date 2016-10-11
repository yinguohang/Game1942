#include "draw.h"
#include "drawer.h"
#include "hgeSprite.h"
#include "default.h"


bool Draw::draw(){
	Drawer::hge->Gfx_BeginScene();//开始渲染 
	Drawer::hge->Gfx_Clear(0x00000000);//以某颜色清屏，OxFF000000为透明度为0的黑色 
	bool temp=Drawer::scene->render();
	if (temp) return temp;
	if (Drawer::scene->is_changing()){
		//正在改变的时候 形成屏幕主键变暗效果
		hgeQuad temp;
		temp.v[0].x=0; temp.v[0].y=0;
		temp.v[1].x=SCREENWIDTH; temp.v[1].y=0;
		temp.v[2].x=SCREENWIDTH; temp.v[2].y=SCREENHEIGHT;
		temp.v[3].x=0; temp.v[3].y=SCREENHEIGHT;
		temp.tex=0;
		temp.blend=BLEND_COLORADD|BLEND_ALPHABLEND|BLEND_NOZWRITE;
		for (int i=0;i<4;i++){
			temp.v[i].col=(int)(0xFF*Drawer::scene->get_gap()/0.5)<<24;
			temp.v[i].z=1;
		}
		Drawer::hge->Gfx_RenderQuad(&temp);
	}
	Drawer::hge->Gfx_EndScene();//结束渲染
	return temp;
}