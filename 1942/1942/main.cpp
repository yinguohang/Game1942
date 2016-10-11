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
	Drawer* drawer=new Drawer(); //生成总控制类实例对象
	drawer->start();
	drawer->end();
	return 0;
}