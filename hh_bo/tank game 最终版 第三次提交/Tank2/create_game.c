#include<Windows.h>
#include"tank.h"



/************** 宏定义 ****************/
// 计时器ID。
#define TIMER_ID 12340

/************** 全局变量 ****************/
// 计时器到时间隔
DWORD dwTimerElapse;


void OnTimer1(HWND hwnd)
{
	BulletMove();
	
}

void OnTimer2(HWND hwnd)
{
	if(enemy3[5].x==20&&enemy3[5].y==3)
	Bullet1Move();
}


// 游戏的初始化，
// 创建游戏的内部数据结构和系统对象。
void CreateGame(HWND hwnd, // 主窗口句柄
	DWORD dwInitTimerElapse, //
	direction init_dir)
{
	// 设置随机数种子
	// 需要使用随机数生成食物的位置等。
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	srand(ft.dwLowDateTime);

	
	dwTimerElapse = dwInitTimerElapse;
	
	

	SetBoundary();
	CreateTank();
	if(!ENEMY_DEAD)
	{
	   CreateEnemy();
	   CreateEnemy1();
	   CreateEnemy2();
	   CreateEnemy3();
	}
	CreateBullet();
	CreateWall1();
	CreateWall2();
	CreateWall3();
	// 创建一个计时器
	// 每经过 dwTimerElapse 毫秒，hwnd窗口（主窗口）就会收到一个WM_TIMER消息。
	// 计时器是驱动本游戏进行的主要时间线。
	// dwTimerElapse变量影响游戏进行的快慢变化。
	SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);

}