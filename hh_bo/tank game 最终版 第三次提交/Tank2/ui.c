#include <windows.h> // Windows���ڳ����̣���Ҫ����ͷ�ļ� Windows.h
#include "tank.h"
#include  <tchar.h>

// ��ͼʱʹ�õı�ʾ̹�˺��ӵ���Բ�ε�ֱ�����ص������
#define CELL_PIXEL			20
// ��ʱ��ID��
#define TIMER_ID 12340

// ������ͼ����ɫ
#define COLOR_TANK          RGB(255,215,0)//��ɫ
#define COLOR_ENEMY         RGB(186,85,211)//��ɫ
#define COLOR_BULLET        RGB(255,0,0)//��ɫ
#define COLOR_WALL          RGB(205,197,191)//��ɫ
#define COLOR_BULLET1       RGB(32,178,170)//����ɫ
#define COLOR_BOUNDARY		RGB(139, 134, 130)
#define COLOR_TEXT			RGB(173,216,230)

// ��Ϸ�Ĳ��������� 
#define INIT_TIMER_ELAPSE	500	// ��ʼ��ʱ�����ڣ�ȷ����Ϸ��ʼ�ٶ�
#define SPEEDUP_RATIO		0.8 // �����Ժ�ʱ�����ڣ�ȷ����Ϸ�ٶȣ���ߵı�����
#define MAX_X		18	// ��Ϸ�����С
#define MAX_Y		20	// ��Ϸ�����С
#define INIT_DIR	TANK_LEFT	// ̹�˵ĳ�ʼ����

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


// ȫ�ֱ���
HINSTANCE hinst; /// HINSTANCE��������ʾ��������ʵ���ľ����ĳЩAPI������ʹ�õ����������
RECT rectBoundary;



// ����Ʒ֣���ʼΪ0
  int score = 0;

/************** �������� ****************/
// ���ػ���
 int GetScore(){return score;}
 


 //�ж������Ƿ��غ�
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




// ��������

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(
	HINSTANCE hinstance, // ����ʵ��������ڳ������У����̴������ɲ���ϵͳ��Ӧ�ó�����
	HINSTANCE hPrevInstance, // �����̵ĳ���ʵ�����
	LPSTR lpCmdLine,  // �����в�������λ����������C����main��������argc��argv,����û�а��ո�����з�
	int nCmdShow)   // ����ָ�������Ƿ���Ҫ��ʾ�Ĳ�����
{

	WNDCLASS wc;
	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
	//HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	// ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
	wc.lpfnWndProc = MainWndProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon��Ա����ָ�����ڵ�ͼ��
	// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	// Cursor������꣬�������趨����������ʽ��
	// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
	// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// ���ڵĲ˵�����Դ����
	wc.lpszMenuName = _T("MainMenu");
	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�
	wc.lpszClassName = _T("MainWClass");

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL,_T( "��������classʧ��"), _T("����"), MB_ICONERROR | MB_OK);
		return -1;
	}
	// ����ע��ɹ����������С�
	if(score==2)
 {
			KillTimer(hwnd, TIMER_ID);
			// ֪ͨ��ң��˳����̣�������Ϸ��
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
 }

	// Create the main window. 

	hwnd = CreateWindow(
		_T("MainWClass"),			// �����������������Ѿ�ע���˵Ĵ�����
		TEXT("tank game"),		// title-bar string 
		WS_CAPTION | WS_SYSMENU,	// ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, _T("��������ʧ��"), _T("����"), MB_ICONERROR | MB_OK);
		return -1;
	}

	// ���ڴ����ɹ����������С�

	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwnd, nCmdShow);

	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwnd);


	// ���½�����Ϣѭ������ȡ��Ϣ--������Ϣ--������Ϣ���ɴ��ڵ���Ϣ��������������Ϣ��
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

	// ������Ҫ�õ���PEN��BRUSH
	// RGB��ɫ��ʵ��BRUSH
	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN�� PS_NULL��ʾ���ɼ�
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
	* #############  ������  ################
	*
	*******************************************************************************/
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	
	
    /*******************************************************************************
	* #############  ��̹��  ################
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
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
		Rectangle(hdcmem,
			Tank[i]->x * CELL_PIXEL + rectBoundary.left,
			Tank[i]->y * CELL_PIXEL + rectBoundary.top,
			(Tank[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Tank[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}
	}
	/*******************************************************************************
	* #############  ���з�̹��  ################
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
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
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
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
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
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
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
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
		Rectangle(hdcmem,
			Enemy3[i]->x * CELL_PIXEL + rectBoundary.left,
			Enemy3[i]->y * CELL_PIXEL + rectBoundary.top,
			(Enemy3[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Enemy3[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}
	}
	}

    /*******************************************************************************
	* #############  ���ӵ� ################
	*
	*******************************************************************************/
	
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushBULLET);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	
		Bullet = GetBullet();
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
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
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
		Rectangle(hdcmem,
			Bullet1->x * CELL_PIXEL + rectBoundary.left,
			Bullet1->y * CELL_PIXEL + rectBoundary.top,
			(Bullet1->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Bullet1->y + 1)*CELL_PIXEL + rectBoundary.top);
		
	}
	

	/*******************************************************************************
	* #############  ���ϰ���  ################
	*
	*******************************************************************************/

	
	hOldBrush = (HBRUSH)SelectObject(hdcmem, hBrushWALL1);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for ( i = 0;i < 7;i++)
	{
		Wall1[i] = GetWall1(i+1);
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
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
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
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
		// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
		Rectangle(hdcmem,
			Wall3[i]->x * CELL_PIXEL + rectBoundary.left,
			Wall3[i]->y * CELL_PIXEL + rectBoundary.top,
			(Wall3[i]->x + 1)*CELL_PIXEL + rectBoundary.left,
			(Wall3[i]->y + 1)*CELL_PIXEL + rectBoundary.top);
	}




	/*******************************************************************************
	* #############  ��ǽ  ################
	*
	*******************************************************************************/

	SelectObject(hdcmem, hPenBoundary);

	// ��PEN�ƶ�����Ҫ���Ƶķ�������Ͻ�
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
	// ����һ��������ʾLineTo����
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);

	/*******************************************************************************
	* #############  дһ����  ################
	*
	*******************************************************************************/

	// ������һ���������
	hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

	// �����FONT�������DC��
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		//wsprintf(szSourceInfo, TEXT("Score:"));
		wsprintf(szSourceInfo, "Score %d ", GetScore());
		// ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		// ����ַ�����
		TextOut(hdcmem, rectBoundary.left + 3, rectBoundary.bottom + 3,
			szSourceInfo, lstrlen(szSourceInfo));
		// �����ɣ���ԭ�����������Ż�DC��
		SelectObject(hdcmem, hOldFont);
	}

	// ���ڴ�DC�л��꣬һ������Ĵ���DC�ϡ�
	BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);

	/*******************************************************************************
	* #############  ���պ��ͷ���Դ  ################
	*
	*******************************************************************************/
	// ������Դ
	// DeleteObject �ͷ�GDI����
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	DeleteObject(hBrushTANK);
	DeleteObject(hBrushENEMY);
	DeleteObject(hBrushBULLET);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	/*******************************************************************************
	* #############  ReleaseDC ����  ################
	* �ͷ�ռ�õ�DC��ϵͳ��Դ��
	*******************************************************************************/
	ReleaseDC(hwnd, hdc);
}


/*******************************************************************************
* ##########   ������Ϸ���������ϵ��С������Ϸ���ڴ�С    ##########
*******************************************************************************/

void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// ���Ͻ�
	POINT ptRightBottom;	// ���½�
	RECT rectWindow;
	Pgame_coord pCoordBoundary = GetBoundary();

	// ������Ϸ�߽�
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x + 1);
	rectBoundary.bottom = 10 + CELL_PIXEL*(pCoordBoundary->y + 1);

	// �����������ҽǵ�λ��
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// ������ˣ����ô��ڴ�С��
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left, // ����߽���������߱߿���ȡ�
		rectBoundary.bottom + 120, //��������Ϣ������ʾ�ռ䡣
		TRUE);
}

// �����ڲ���ʱ���е��߼�����
// ����Ϸֻʹ�õ��˼����������Ҽ����ơ�

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
	// ��ʱ����ʱ�Ժ󣬵з�̹���ƶ�һ����
	// �����Ժ��Ժ��״̬�����к�������
	switch (EnemyMove())
	{
	
	 //����ӵ������˵з�̹��
	case ENEMY_DEAD:
		// �Ʒ֣�
		IsEnemyDead();
		if(enemy[5].y==0)
		{	
		// �����µĵ��ˡ�
		CreateEnemy();
		// ̹�˵÷ֵĺ���״̬��
		switch (GetScore())
		{
			// ���Ӯ�ˣ�ֹͣ��ʱ����
		case TANK_COMPLETE:
			if(GetScore()>1)
			//KillTimer(hwnd, TIMER_ID);
			// ֪ͨ��ң��˳����̣�������Ϸ��
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
			break;
			// ��������ֹͣ��ʱ�������˳���
		case TANK_ERROR:
			//KillTimer(hwnd, TIMER_ID);
			MessageBox(hwnd, "Error!!", "Error!1", MB_OK);
			ExitProcess(0);
			break;
			// û�н�����Ҳû�д��������÷֡�
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
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam) // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
{
	// ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��
		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		//CreateGame(hwnd);
		CreateGame(hwnd,
			INIT_TIMER_ELAPSE,
			INIT_DIR);
		           
		ReSizeGameWnd(hwnd);
		break;

		// ��ϵͳ��Ϊ�����ϵ�GDI����Ӧ�ñ��ػ�ʱ�����򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ��ȻӦ�ó���Ҳ����ͨ������ UpateWindow�������򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ����ʹ��GDI�ڴ����ϻ���ͼ�εĳ��� �����롱 д�����
		// ���������WM_PAINT��Ϣ�Ĵ�������л���GDIͼ�Σ���ô�ڴ���ˢ��ʱ�ͻᱻ�±�Ĩ���͸���
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