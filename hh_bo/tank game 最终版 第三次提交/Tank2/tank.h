#ifndef _TANK_H_
#define _TANK_H_

#include<Windows.h>

#define ENEMY_DEAD 0
#define TANK_COMPLETE 1
#define TANK_ERROR 2
#define TANK_GET_SCORE 3
#define ENEMY_MOVED 4
#define TANK_MOVED 5
#define BULLET_MOVED 6
#define BULLET1_MOVED 7

// 坦克的方向
typedef enum _direction
{
	TANK_UP,
	TANK_DOWN,
	TANK_LEFT,
	TANK_RIGHT,
}direction;

//敌人的方向
typedef enum _direction1
{
	ENEMY_UP,
	ENEMY_DOWN,
	ENEMY_LEFT,
	ENEMY_RIGHT,
}direction1;



//游戏坐标
typedef struct _coord
{
	short x;
	short y;
}game_coord,*Pgame_coord;



game_coord tank[7];
game_coord enemy[6];
game_coord enemy1[6];
game_coord enemy2[6];
game_coord enemy3[7];
game_coord bullet;
game_coord bullet1;
game_coord wall1[7];
game_coord wall2[7];
game_coord wall3[18];


//边界
game_coord boundary;
//坦克移动方向
direction tank_dir;
direction1 enemy_dir;
direction1 enemy1_dir;
direction1 enemy2_dir;
direction1 enemy3_dir;
//游戏函数声明

//设置边界坐标
void SetBoundary();
//获得边界坐标
Pgame_coord GetBoundary();

//生成坦克
void CreateTank();
//获得坦克坐标
Pgame_coord GetTank(int x);
//坦克移动
int TankMove();
//坦克得分
int TankGetScore();
//改变坦克移动方向
void SetDirection(direction dir);
//获得坦克当前移动方向
direction GetDirection();


//生成敌方坦克
void CreateEnemy();
void CreateEnemy1();
void CreateEnemy2();
void CreateEnemy3();
//敌方坦克移动
int EnemyMove();
int Enemy1Move();
int Enemy2Move();

//销毁敌方坦克
void DistroyEnemy();
void DistroyEnemy1();
void DistroyEnemy2();
void DistroyEnemy3();
//获得敌方坦克的坐标
Pgame_coord GetEnemy(int x);
Pgame_coord GetEnemy1(int x);
Pgame_coord GetEnemy2(int x);
Pgame_coord GetEnemy3(int x);

void CreateBullet();
Pgame_coord GetBullet();
int BulletMove();

void CreateBullet1();
Pgame_coord GetBullet1();
int Bullet1Move();

void CreateWall1();
Pgame_coord GetWall1(int i);

void CreateWall2();
Pgame_coord GetWall2(int i);

void CreateWall3();
Pgame_coord GetWall3(int i);

void IsEnemyDead();
void IsEnemy1Dead();
void IsEnemy2Dead();
void IsEnemy3Dead();
int GetScore();
//生成空白区域
void CreateEmpty();
//获取空白区域坐标
Pgame_coord GetEmpty();
void OnTimer(HWND hwnd);
void OnTimer1(HWND hwnd);
void OnTimer2(HWND hwnd);
void OnKeyDown(DWORD vk);
void CreateGame(HWND hwnd, // 主窗口句柄
	DWORD dwInitTimerElapse, //
	direction init_dir);
void GamePaint(HWND hwnd);
#endif