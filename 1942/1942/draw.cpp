#include "draw.h"
#include "drawer.h"
#include "hgeSprite.h"
#include "default.h"


bool Draw::draw(){
	Drawer::hge->Gfx_BeginScene();//��ʼ��Ⱦ 
	Drawer::hge->Gfx_Clear(0x00000000);//��ĳ��ɫ������OxFF000000Ϊ͸����Ϊ0�ĺ�ɫ 
	bool temp=Drawer::scene->render();
	if (temp) return temp;
	if (Drawer::scene->is_changing()){
		//���ڸı��ʱ�� �γ���Ļ�����䰵Ч��
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
	Drawer::hge->Gfx_EndScene();//������Ⱦ
	return temp;
}