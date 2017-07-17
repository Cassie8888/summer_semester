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

// ̹�˵ķ���
typedef enum _direction
{
	TANK_UP,
	TANK_DOWN,
	TANK_LEFT,
	TANK_RIGHT,
}direction;

//���˵ķ���
typedef enum _direction1
{
	ENEMY_UP,
	ENEMY_DOWN,
	ENEMY_LEFT,
	ENEMY_RIGHT,
}direction1;



//��Ϸ����
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


//�߽�
game_coord boundary;
//̹���ƶ�����
direction tank_dir;
direction1 enemy_dir;
direction1 enemy1_dir;
direction1 enemy2_dir;
direction1 enemy3_dir;
//��Ϸ��������

//���ñ߽�����
void SetBoundary();
//��ñ߽�����
Pgame_coord GetBoundary();

//����̹��
void CreateTank();
//���̹������
Pgame_coord GetTank(int x);
//̹���ƶ�
int TankMove();
//̹�˵÷�
int TankGetScore();
//�ı�̹���ƶ�����
void SetDirection(direction dir);
//���̹�˵�ǰ�ƶ�����
direction GetDirection();


//���ɵз�̹��
void CreateEnemy();
void CreateEnemy1();
void CreateEnemy2();
void CreateEnemy3();
//�з�̹���ƶ�
int EnemyMove();
int Enemy1Move();
int Enemy2Move();

//���ٵз�̹��
void DistroyEnemy();
void DistroyEnemy1();
void DistroyEnemy2();
void DistroyEnemy3();
//��õз�̹�˵�����
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
//���ɿհ�����
void CreateEmpty();
//��ȡ�հ���������
Pgame_coord GetEmpty();
void OnTimer(HWND hwnd);
void OnTimer1(HWND hwnd);
void OnTimer2(HWND hwnd);
void OnKeyDown(DWORD vk);
void CreateGame(HWND hwnd, // �����ھ��
	DWORD dwInitTimerElapse, //
	direction init_dir);
void GamePaint(HWND hwnd);
#endif