#include "background.h"
#include "exception.h"

Background::Background(HGE* hge,const char* s):
	hgeSprite(0,0,0,0,0)
{
	this->hge=hge;							//��ʼ��hge
	t_y=hge->Timer_GetTime();				//��ʼ��ʱ����Ʋ���
	v=50;									//��ʼ�����������ٶ�
	HTEXTURE temp=hge->Texture_Load(s);		//���뵱ǰ��������
	if (!temp) {
		//���û�гɹ��������� ���쳣
		MessageBoxA(NULL,hge->System_GetErrorMessage(),"Error",MB_OK|MB_ICONERROR|MB_APPLMODAL);
		throw(Exception(0));
		return;
	}
	/*������������*/
	SetTexture(temp);
	SetTextureRect(0,t_y
		,hge->Texture_GetWidth(temp),hge->Texture_GetHeight(temp));
}

void Background::Render(){
	hgeSprite::Render(0,0);													//��Ⱦ��ǰ����
	SetTextureRect(0,(hge->Timer_GetTime()-t_y)*v,GetWidth(),GetHeight());	//�ƶ���������������ʵ�ֹ���Ч��
}
