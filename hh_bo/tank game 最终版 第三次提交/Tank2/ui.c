#include <windows.h> // Windows窗口程序编程，需要引用头文件 Windows.h
#include "tank.h"
#include  <tchar.h>

// 画图时使用的表示坦克和子弹的圆形的直径像素点个数。
#define CELL_PIXEL			20
// 计时器ID。
#define TIMER_ID 12340

// 用来绘图的颜色
#define COLOR_TANK          RGB(255,215,0)//黄色
#define COLOR_ENEMY         RGB(186,85,211)//紫色
#define COLOR_BULLET        RGB(255,0,0)//红色
#define COLOR_WALL          RGB(205,197,191)//灰色
#define COLOR_BULLET1       RGB(32,178,170)//青蓝色
#define COLOR_BOUNDARY		RGB(139, 134, 130)
#define COLOR_TEXT			RGB(173,216,230)

// 游戏的参数的设置 
#define INIT_TIMER_ELAPSE	500	// 初始的时钟周期，确定游戏初始速度
#define SPEEDUP_RATIO		0.8 // 升级以后时间周期（确定游戏速度）提高的比例。
#define MAX_X		18	// 游戏界面大小
#define MAX_Y		20	// 游戏界面大小
#define INIT_DIR	TANK_LEFT	// 坦克的初始方向

HWND hwnd;
Pgame_coord Tank[6];
Pgame_coord Enemy[6];
Pgame_coord Enemy1[6];
Pgame_coord Enemy2[6];
Pgame_coord Enemy3[6];
Pgame_coord Bullet;
Pgame_coord Bullet1;
Pgame_coord Wall1[7];
Pgame_coord Wall2[7];
Pgame_coord Wall3[18];


// 全局变量
HINSTANCE hinst; /// HINSTANCE是用来表示程序运行实例的句柄，某些API函数会使用到这个变量。
RECT rectBoundary;



// 保存计分，初始为0
  int score = 0;

/************** 函数定义 ****************/
// 返回积分
 int GetScore(){return score;}
 


 //判断坐标是否重合
int CoordEqual(game_coord a, game_coord b);

int CoordEqual(game_coord a, game_coord b)
{
	if (a.x == b.x&&a.y == b.y)
		return 1;
	return 0;
}

 void IsEnemyDead()
{
	if(CoordEqual(bullet,enemy[0])||CoordEqual(bullet,enemy[1])||
	   CoordEqual(bullet,enemy[2])||CoordEqual(bullet,enemy[3])||
	   CoordEqual(bullet,enemy[4])||CoordEqual(bullet,enemy[5])
		)
	{
		int i;
		for(i=0;i<6;i++)
		{
			enemy[i].x=0;
			enemy[i].y=0;
		}
		score++;
	}
	
}

void IsEnemy1Dead()
{
	if(CoordEqual(bullet,enemy1[0])||CoordEqual(bullet,enemy1[1])||
	   CoordEqual(bullet,enemy1[2])||CoordEqual(bullet,enemy1[3])||
	   CoordEqual(bullet,enemy1[4])||CoordEqual(bullet,enemy1[5])
		)
	{
		int i;
		for(i=0;i<6;i++)
		{
			enemy1[i].x=0;
			enemy1[i].y=0;
		}
		score++;
	}
	
}

void IsEnemy2Dead()
{
	if(CoordEqual(bullet,enemy2[0])||CoordEqual(bullet,enemy2[1])||
	   CoordEqual(bullet,enemy2[2])||CoordEqual(bullet,enemy2[3])||
	   CoordEqual(bullet,enemy2[4])||CoordEqual(bullet,enemy2[5])
		)
	{
		int i;
		for(i=0;i<6;i++)
		{
			enemy2[i].x=0;
			enemy2[i].y=0;
		}
		score++;
	}
	
}

void IsEnemy3Dead()
{
	if(CoordEqual(bullet,enemy3[0])||CoordEqual(bullet,enemy3[1])||
	   CoordEqual(bullet,enemy3[2])||CoordEqual(bullet,enemy3[3])||
	   CoordEqual(bullet,enemy3[4])||CoordEqual(bullet,enemy3[5])
		)
	{
		int i;
		for(i=0;i<6;i++)
		{
			enemy3[i].x=0;
			enemy3[i].y=0;
		}
		score++;
	}
	
}
void IsTankDead()
{
	if(CoordEqual(bullet1,tank[0])||CoordEqual(bullet1,tank[1])||
	   CoordEqual(bullet1,tank[2])||CoordEqual(bullet1,tank[3])||
	   CoordEqual(bullet1,tank[4])||CoordEqual(bullet1,tank[5])
		)
	{
		int i;
		for(i=0;i<6;i++)
		{
			tank[i].x=0;
			tank[i].y=0;
		}
		KillTimer(hwnd, TIMER_ID);
		MessageBox(0, "Game Over!", "Game Over", 0);
		ExitProcess(0);
	}
	else
	{
		if (score==2)
		{
		KillTimer(hwnd, TIMER_ID);
		MessageBox(0, "You Win!", "You Win", 0);
		ExitProcess(0);
		}
	}
	
}




// 函数声明

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(
	HINSTANCE hinstance, // 程序实例句柄，在程序运行，进程创建后，由操作系统向应用程序传入
	HINSTANCE hPrevInstance, // 父进程的程序实例句柄
	LPSTR lpCmdLine,  // 命令行参数，地位和作用类似C语言main函数参数argc和argv,但是没有按空格进行切分
	int nCmdShow)   // 用于指明窗口是否需要显示的参数。
{

	WNDCLASS wc;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。
	//HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	// 窗口类的样式，这里设置的样式表示窗口在大小变化是需要重绘
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 一个函数指针，这个函数用来处理窗口消息。 详见 MainWndProc函数的注释。
	wc.lpfnWndProc = MainWndProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon成员用来指定窗口的图标
	// 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	// Cursor是鼠标光标，这里是设定了鼠标光标的样式。
	// 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HAND等样式 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
	// 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// 窗口的菜单的资源名。
	wc.lpszMenuName = _T("MainMenu");
	// 给窗口类起一个名字，在创建窗口时需要这个名字。
	wc.lpszClassName = _T("MainWClass");

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL,_T( "创建窗口class失败"), _T("错误！"), MB_ICONERROR | MB_OK);
		return -1;
	}
	// 窗口注册成功，继续运行。
	if(score==2)
 {
			KillTimer(hwnd, TIMER_ID);
			// 通知玩家，退出进程，结束游戏。
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
 }

	// Create the main window. 

	hwnd = CreateWindow(
		_T("MainWClass"),			// 窗口类名，必须是已经注册了的窗口类
		TEXT("tank game"),		// title-bar string 
		WS_CAPTION | WS_SYSMENU,	// 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 

	if (!hwnd)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, _T("创建窗口失败"), _T("错误！"), MB_ICONERROR | MB_OK);
		return -1;
	}

	// 窗口创建成功，继续运行。

	// 显示窗口，WinMain函数的nCmdShow参数在这里发挥作用，一般都设置为SW_SHOW
	ShowWindow(hwnd, nCmdShow);

	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwnd);


	// 以下进入消息循环。获取消息--翻译消息--分配消息（由窗口的消息处理函数来处理消息）
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void GamePaint(HWND hwnd)
{
	HPEN hpen;
	HDC hdc, hdcmem;
	HBITMAP hbmMem;

	HPEN hPenBoundary;
	HPEN hOldPen;

	
	HBRUSH hBrushTANK;
	HBRUSH hBrushENEMY;
	HBRUSH hBrushBULLET;
	HBRUSH hBrushBULLET1;
	HBRUSH hBrushENEMY1;
	HBRUSH hBrushENEMY2;
	HBRUSH hBrushENEMY3;
	HBRUSH hBrushWALL1;
	HBRUSH hBrushWALL2;
	HBRUSH hBrushWALL3;
	HBRUSH hOldBrush;

	HFONT hFont, hOldFont;

	RECT rect;

	int i, m;

	GetClientRect(hwnd, &rect);

	hdc = GetDC(hwnd);
	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,
		rect.right - rect.left, rect.bottom - rect.top);

	SelectObject(hdcmem, hbmMem);

	// 创建需要用到的PEN和BRUSH
	// RGB颜色，实心BRUSH
	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN， PS_NULL表示不可见
	hBrushTANK = CreateSolidBrush(COLOR_TANK);
	hBrushENEMY = CreateSolidBrush(COLOR_ENEMY);
	hBrushBULLET = CreateSolidBrush(COLOR_BULLET);
	hBrushBULLET1 = CreateSolidBrush(COLOR_BULLET1);
	hBrushENEMY1 = CreateSolidBrush(COLOR_ENEMY);
	hBrushENEMY2 = CreateSolidBrush(COLOR_ENEMY);
	hBrushENEMY3 = CreateSolidBrush(COLOR_ENEMY);
	hBrushWALL1 = CreateSolidBrush(COLOR_WALL);
	hBrushWALL2 = CreateSolidBrush(COLOR_WALL);
	hBrushWALL3 = CreateSolidBrush(COLOR_WALL);
	hPenBoundary = CreatePen(0, 3, COLOR_BOUNDARY);


	/*******************************************************************************
	* #############  画背景  ################
	*
	*******************************************************************************/
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	
	
    /*******************************************************************************
	* #############  画坦克  ################
	*
	*******************************************************************************/
	IsTankDead();
	if(tank[5].x!=0)
	{
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushTANK);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for ( i = 0;i < 6;i++)
	{
		Tank[i] = GetTank(i+1);
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Tank[i]->x * CELL_PIXEL + rectBoundary.left,
			Tank[i]->y * CELL_PIXEL + rectBoundary.top,
			(Tank[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Tank[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}
	}
	/*******************************************************************************
	* #############  画敌方坦克  ################
	*
	*******************************************************************************/

	IsEnemyDead();
	if(enemy[5].x!=0)
	{
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushENEMY);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for ( i = 0;i < 6;i++)
	{
		Enemy[i] = GetEnemy(i+1);
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Enemy[i]->x * CELL_PIXEL + rectBoundary.left,
			Enemy[i]->y * CELL_PIXEL + rectBoundary.top,
			(Enemy[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Enemy[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}
	}
	else
	{
       IsEnemy2Dead();
	if(enemy2[5].y!=0)
	{
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushENEMY2);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for ( i = 0;i < 6;i++)
	{
		Enemy2[i] = GetEnemy2(i+1);
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Enemy2[i]->x * CELL_PIXEL + rectBoundary.left,
			Enemy2[i]->y * CELL_PIXEL + rectBoundary.top,
			(Enemy2[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Enemy2[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}
	} 
	}

	IsEnemy1Dead();
	if(enemy1[5].y!=0)
	{
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushENEMY1);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for ( i = 0;i < 6;i++)
	{
		Enemy1[i] = GetEnemy1(i+1);
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Enemy1[i]->x * CELL_PIXEL + rectBoundary.left,
			Enemy1[i]->y * CELL_PIXEL + rectBoundary.top,
			(Enemy1[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Enemy1[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}
	}
	else
	{
         IsEnemy3Dead();
	if(enemy3[5].y!=0)
	{
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushENEMY3);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for ( i = 0;i < 6;i++)
	{
		Enemy3[i] = GetEnemy3(i+1);
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Enemy3[i]->x * CELL_PIXEL + rectBoundary.left,
			Enemy3[i]->y * CELL_PIXEL + rectBoundary.top,
			(Enemy3[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Enemy3[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}
	}
	}

    /*******************************************************************************
	* #############  画子弹 ################
	*
	*******************************************************************************/
	
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushBULLET);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	
		Bullet = GetBullet();
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Bullet->x * CELL_PIXEL + rectBoundary.left,
			Bullet->y * CELL_PIXEL + rectBoundary.top,
			(Bullet->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Bullet->y + 1)*CELL_PIXEL + rectBoundary.top);
	if(enemy3[5].x==20&&enemy3[5].y==3)
	{
		
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushBULLET1);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	    //CreateBullet1();
		Bullet1 = GetBullet1();
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Bullet1->x * CELL_PIXEL + rectBoundary.left,
			Bullet1->y * CELL_PIXEL + rectBoundary.top,
			(Bullet1->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Bullet1->y + 1)*CELL_PIXEL + rectBoundary.top);
		
	}
	

	/*******************************************************************************
	* #############  画障碍物  ################
	*
	*******************************************************************************/

	
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushWALL1);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for ( i = 0;i < 7;i++)
	{
		Wall1[i] = GetWall1(i+1);
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Wall1[i]->x * CELL_PIXEL + rectBoundary.left,
			Wall1[i]->y * CELL_PIXEL + rectBoundary.top,
			(Wall1[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Wall1[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}

	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushWALL2);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for ( i = 0;i < 7;i++)
	{
		Wall2[i] = GetWall2(i+1);
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Wall2[i]->x * CELL_PIXEL + rectBoundary.left,
			Wall2[i]->y * CELL_PIXEL + rectBoundary.top,
			(Wall2[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Wall2[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushWALL3);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for ( i = 0;i < 18;i++)
	{
		Wall3[i] = GetWall3(i+1);
		// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
		Rectangle(hdcmem,
			Wall3[i]->x * CELL_PIXEL + rectBoundary.left,
			Wall3[i]->y * CELL_PIXEL + rectBoundary.top,
			(Wall3[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Wall3[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}




	/*******************************************************************************
	* #############  画墙  ################
	*
	*******************************************************************************/

	SelectObject(hdcmem, hPenBoundary);

	// 将PEN移动到需要绘制的方框的左上角
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
	// 画了一个方框。演示LineTo函数
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);

	/*******************************************************************************
	* #############  写一行字  ################
	*
	*******************************************************************************/

	// 创建了一个字体对象
	hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

	// 将这个FONT对象放入DC中
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		//wsprintf(szSourceInfo, TEXT("Score:"));
		wsprintf(szSourceInfo, "Score %d ", GetScore());
		// 设置输出颜色
		SetTextColor(hdcmem, COLOR_TEXT);
		// 输出字符串。
		TextOut(hdcmem, rectBoundary.left + 3, rectBoundary.bottom + 3,
			szSourceInfo, lstrlen(szSourceInfo));
		// 输出完成，将原来的字体对象放回DC中
		SelectObject(hdcmem, hOldFont);
	}

	// 在内存DC中画完，一次输出的窗口DC上。
	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	/*******************************************************************************
	* #############  回收和释放资源  ################
	*
	*******************************************************************************/
	// 回收资源
	// DeleteObject 释放GDI对象
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	DeleteObject(hBrushTANK);
	DeleteObject(hBrushENEMY);
	DeleteObject(hBrushBULLET);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	/*******************************************************************************
	* #############  ReleaseDC 函数  ################
	* 释放占用的DC等系统资源。
	*******************************************************************************/
	ReleaseDC(hwnd, hdc);
}


/*******************************************************************************
* ##########   根据游戏界面的坐标系大小设置游戏窗口大小    ##########
*******************************************************************************/

void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// 左上角
	POINT ptRightBottom;	// 右下角
	RECT rectWindow;
	Pgame_coord pCoordBoundary = GetBoundary();

	// 设置游戏边界
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x + 1);
	rectBoundary.bottom = 10 + CELL_PIXEL*(pCoordBoundary->y + 1);

	// 计算上下左右角的位置
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// 计算好了，设置窗口大小。
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left, // 保存边界和左右两边边框相等。
		rectBoundary.bottom + 120, //给积分信息留出显示空间。
		TRUE);
}

// 当用于操作时进行的逻辑处理。
// 本游戏只使用到了键盘上下左右键控制。

void OnKeyDown(DWORD vk)
{
	int i=0;
	switch (vk) // virtual key value
	{
	case VK_LEFT:
		SetDirection(TANK_LEFT);

		break;
	case VK_RIGHT:
		SetDirection(TANK_RIGHT);
		break;
	case VK_UP:
		SetDirection(TANK_UP);
		break;
	case VK_DOWN:
		SetDirection(TANK_DOWN);
		break;
	case 'T':
		if (HIWORD(GetKeyState('T')))
		{
			
			CreateBullet();
		}
		else if (HIWORD(GetKeyState(VK_DOWN)))
		{
			for(i=0;i<7;i++)
			{
			  Tank[i]->y += 1;
			  if (Tank[i]->y > 19)
				Tank[i]->y = 19;
			}
		}
		else if (HIWORD(GetKeyState(VK_UP)))
		{
			for(i=0;i<7;i++)
			Tank[i]->y -= 1;
			if (Tank[i]->y < 0)
				Tank[i]->y = 0;
		}
		else if (HIWORD(GetKeyState(VK_LEFT)))
		{
			for(i=0;i<7;i++)
			{
			Tank[i]->x -= 1;
			if (Tank[i]->x < 0)
				Tank[i]->x = 0;
			}
		}
		else if (HIWORD(GetKeyState(VK_RIGHT)))
		{
			for(i=0;i<7;i++)
			{
			Tank[i]->x += 1;
			if (Tank[i]->x > 49)
				Tank[i]->x = 49;
			}
		}
		
		GamePaint(hwnd);
	}
	TankMove();
	return;
}

void OnTimer(HWND hwnd)
{
	// 计时器到时以后，敌方坦克移动一步。
	// 根据以后以后的状态，进行后续处理。
	switch (EnemyMove())
	{
	
	 //如果子弹击中了敌方坦克
	case ENEMY_DEAD:
		// 计分；
		IsEnemyDead();
		if(enemy[5].y==0)
		{	
		// 创建新的敌人。
		CreateEnemy();
		// 坦克得分的后续状态。
		switch (GetScore())
		{
			// 玩家赢了，停止计时器。
		case TANK_COMPLETE:
			if(GetScore()>1)
			//KillTimer(hwnd, TIMER_ID);
			// 通知玩家，退出进程，结束游戏。
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
			break;
			// 发生错误，停止计时器，并退出。
		case TANK_ERROR:
			//KillTimer(hwnd, TIMER_ID);
			MessageBox(hwnd, "Error!!", "Error!1", MB_OK);
			ExitProcess(0);
			break;
			// 没有结束，也没有错误，正常得分。
			break;
		} 
		}
		break;
	case ENEMY_MOVED:
		break;
	}
	Enemy1Move();
	Enemy2Move();
	Bullet1Move();
	return;

}

LRESULT CALLBACK MainWndProc(
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
	LPARAM lParam) // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
{
	// 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		//CreateGame(hwnd);
		CreateGame(hwnd,
			INIT_TIMER_ELAPSE,
			INIT_DIR);
		           
		ReSizeGameWnd(hwnd);
		break;

		// 当系统认为窗口上的GDI对象应该被重绘时，会向窗口发送一个WM_PAINT消息。
		// 当然应用程序也可以通过调用 UpateWindow来主动向窗口发送一个WM_PAINT消息。
		// 所有使用GDI在窗口上绘制图形的程序都 “必须” 写在这里。
		// 如果不是在WM_PAINT消息的处理过程中绘制GDI图形，那么在窗口刷新时就会被新被抹除和覆盖
	case WM_PAINT:
		GamePaint(hwnd);
		break;

	case WM_KEYDOWN:

		OnKeyDown(wParam);
		GamePaint(hwnd);
		break;


	case WM_TIMER:

		OnTimer(hwnd);
		OnTimer1(hwnd);
		OnTimer2(hwnd);
		GamePaint(hwnd);
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;



	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}