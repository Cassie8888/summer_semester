#include<Windows.h>
#include"tank.h"



/************** �궨�� ****************/
// ��ʱ��ID��
#define TIMER_ID 12340

/************** ȫ�ֱ��� ****************/
// ��ʱ����ʱ���
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


// ��Ϸ�ĳ�ʼ����
// ������Ϸ���ڲ����ݽṹ��ϵͳ����
void CreateGame(HWND hwnd, // �����ھ��
	DWORD dwInitTimerElapse, //
	direction init_dir)
{
	// �������������
	// ��Ҫʹ�����������ʳ���λ�õȡ�
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
	// ����һ����ʱ��
	// ÿ���� dwTimerElapse ���룬hwnd���ڣ������ڣ��ͻ��յ�һ��WM_TIMER��Ϣ��
	// ��ʱ������������Ϸ���е���Ҫʱ���ߡ�
	// dwTimerElapse����Ӱ����Ϸ���еĿ����仯��
	SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);

}