#include "drawer.h"
#include <time.h>

int WINAPI WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPreInstance,
		LPSTR IpCmdLine,
		int nShowCmd
	)
{
	srand(time(0));
	Drawer* drawer=new Drawer(); //�����ܿ�����ʵ������
	drawer->start();
	drawer->end();
	return 0;
}