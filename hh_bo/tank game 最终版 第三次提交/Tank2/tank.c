#include"tank.h"

void SetBoundary()
{
	boundary.x = 49;
	boundary.y = 19;
}

Pgame_coord GetBoundary()
{
	return &boundary;
}



//创建坦克
void CreateTank()
{
	tank[0].x=25;
	tank[0].y=19;
	tank[1].x=25;
	tank[1].y=18;
	tank[2].x=26;
	tank[2].y=18;
	tank[3].x=27;
	tank[3].y=18;
	tank[4].x=27;
	tank[4].y=19;
	tank[5].x=26;
	tank[5].y=17;
	tank[6].x=26;
	tank[6].y=16;
}
//获得坦克坐标
Pgame_coord GetTank(int i)
{
	switch (i)
	{
		case 1:
			return &tank[0];
		case 2:
			return &tank[1];
		case 3:
			return &tank[2];
		case 4:
			return &tank[3];
		case 5:
			return &tank[4];
		case 6:
			return &tank[5];
		case 7:
			return &tank[6];
	}	
}
int TankMove()
{
	
	switch (tank_dir)
	{
		int i;
	case TANK_UP:
		
		for(i=0;i<7;i++)
		{
			tank[i].y=tank[i].y-1;
			tank[i].x=tank[i].x;
		}
		break;
	case TANK_DOWN:

		for(i=0;i<7;i++)
		{
			tank[i].y=tank[i].y+1;
			tank[i].x=tank[i].x;
		}
		break;
	case TANK_LEFT:
		
		for(i=0;i<7;i++)
		{
			tank[i].x=tank[i].x-1;
			tank[i].y=tank[i].y;
		}
		break;
	case TANK_RIGHT:
		
		for(i=0;i<7;i++)
		{
			tank[i].x=tank[i].x+1;
			tank[i].y=tank[i].y;
		}
		break;
	}

	return TANK_MOVED;
}




//创建敌方坦克
void CreateEnemy()
{
	
	enemy[0].x=49;
	enemy[0].y=0;
	enemy[1].x=49;
	enemy[1].y=1;
	enemy[2].x=48;
	enemy[2].y=1;
	enemy[3].x=47;
	enemy[3].y=1;
	enemy[4].x=47;
	enemy[4].y=0;
	enemy[5].x=48;
	enemy[5].y=2;
}
//获得坦克坐标
Pgame_coord GetEnemy(int i)
{
	switch (i)
	{
		case 1:
			return &enemy[0];
		case 2:
			return &enemy[1];
		case 3:
			return &enemy[2];
		case 4:
			return &enemy[3];
		case 5:
			return &enemy[4];
		case 6:
			return &enemy[5];
	}	
}

//
int EnemyMove()
{
	if(!ENEMY_DEAD)
	{
	switch (enemy_dir)
	{
		int i;
	case ENEMY_UP:
		
		for(i=0;i<6;i++)
		{
			enemy[i].y=enemy[i].y+1;
			enemy[i].x=enemy[i].x;
			if(enemy[i].y>9)
			{
				enemy[0].y=enemy[4].y=0;
				enemy[1].y=enemy[2].y=enemy[3].y=0;
				enemy[5].x=enemy[5].y=0;
			}
		}
		break;
	case ENEMY_DOWN:

		for(i=0;i<6;i++)
		{
			enemy[i].y=enemy[i].y-1;
			enemy[i].x=enemy[i].x;
		}
		break;
	case ENEMY_LEFT:
		
		for(i=0;i<6;i++)
		{
			enemy[i].x=enemy[i].x-1;
			enemy[i].y=enemy[i].y;
		}
		break;
	case ENEMY_RIGHT:
		
		for(i=0;i<6;i++)
		{
			enemy[i].x=enemy[i].x+1;
			enemy[i].y=enemy[i].y;
		}
		break;
	}
	
	return ENEMY_MOVED;
	}
}

//创建敌方坦克
void CreateEnemy2()
{
	
	enemy2[0].x=49;
	enemy2[0].y=9;
	enemy2[1].x=48;
	enemy2[1].y=9;
	enemy2[2].x=48;
	enemy2[2].y=8;
	enemy2[3].x=48;
	enemy2[3].y=7;
	enemy2[4].x=49;
	enemy2[4].y=7;
	enemy2[5].x=47;
	enemy2[5].y=8;
}
//获得坦克坐标
Pgame_coord GetEnemy2(int i)
{
	switch (i)
	{
		case 1:
			return &enemy2[0];
		case 2:
			return &enemy2[1];
		case 3:
			return &enemy2[2];
		case 4:
			return &enemy2[3];
		case 5:
			return &enemy2[4];
		case 6:
			return &enemy2[5];
	}	
}

//
int Enemy2Move()
{
	int i;
		
		for(i=0;i<6;i++)
		{
			enemy2[i].x=enemy2[i].x-1;
			enemy2[i].y=enemy2[i].y;
		}
		if(enemy2[5].x<0)
		{
			enemy2[0].x=enemy2[4].x=2;
			enemy2[1].x=enemy2[2].x=enemy2[3].x=1;
			enemy2[5].x=0;
		}
		
	return ENEMY_MOVED;
	
}











//创建敌方坦克
void CreateEnemy1()
{
	
	enemy1[0].x=0;
	enemy1[0].y=1;
	enemy1[1].x=1;
	enemy1[1].y=1;
	enemy1[2].x=1;
	enemy1[2].y=2;
	enemy1[3].x=1;
	enemy1[3].y=3;
	enemy1[4].x=0;
	enemy1[4].y=3;
	enemy1[5].x=2;
	enemy1[5].y=2;
}
//获得坦克坐标
Pgame_coord GetEnemy1(int i)
{
	switch (i)
	{
		case 1:
			return &enemy1[0];
		case 2:
			return &enemy1[1];
		case 3:
			return &enemy1[2];
		case 4:
			return &enemy1[3];
		case 5:
			return &enemy1[4];
		case 6:
			return &enemy1[5];
	}	
}

//
int Enemy1Move()
{
	    int i;
		for(i=0;i<6;i++)
		{
			enemy1[i].x=enemy1[i].x+1;
			enemy1[i].y=enemy1[i].y;
		}
		if(enemy1[5].x>21)
		{
			enemy1[0].x=enemy1[4].x=0;
			enemy1[1].x=enemy1[2].x=enemy1[3].x=0;
			enemy1[5].y=enemy1[5].x=0;
		}
	
	return ENEMY_MOVED;
	
}


//创建敌方坦克
void CreateEnemy3()
{
	
	enemy3[0].x=21;
	enemy3[0].y=1;
	enemy3[1].x=21;
	enemy3[1].y=2;
	enemy3[2].x=20;
	enemy3[2].y=2;
	enemy3[3].x=19;
	enemy3[3].y=2;
	enemy3[4].x=19;
	enemy3[4].y=1;
	enemy3[5].x=20;
	enemy3[5].y=3;
	enemy3[6].x=20;
	enemy3[6].y=4;
}
//获得坦克坐标
Pgame_coord GetEnemy3(int i)
{
	switch (i)
	{
		case 1:
			return &enemy3[0];
		case 2:
			return &enemy3[1];
		case 3:
			return &enemy3[2];
		case 4:
			return &enemy3[3];
		case 5:
			return &enemy3[4];
		case 6:
			return &enemy3[5];
		case 7:
			return &enemy3[6];
	}	
}









void CreateBullet()
{
	bullet=tank[6];
}

Pgame_coord GetBullet()
{
	return &bullet;
}

int BulletMove()
{
	bullet.x=bullet.x;
	bullet.y=bullet.y-1;
	return BULLET_MOVED;
}

void CreateBullet1()
{
	bullet1=enemy3[6];
}

Pgame_coord GetBullet1()
{
	return &bullet1;
}

int Bullet1Move()
{
	bullet1.y=bullet1.y+1;
	bullet1.x=bullet1.x;
	if(bullet1.y>19)
	{
		CreateBullet1();
	}
	return BULLET1_MOVED;
}



 //改变坦克移动的方向
void SetDirection(direction dir)
{
	tank_dir = dir;
}


// 获得当前坦克的方向
direction GetDirection()
{
	return tank_dir;
}

void CreateWall1()
{
	int i;
   wall1[0].x=49;
   wall1[1].x=48;
   wall1[2].x=47;
   wall1[3].x=46;
   wall1[4].x=45;
   wall1[5].x=44;
   wall1[6].x=43;
  
   for(i=0;i<7;i++)
   {
	   wall1[i].y=10;
   }
}

Pgame_coord GetWall1(int i)
{
	switch (i)
	{
		case 1:
			return &wall1[0];
		case 2:
			return &wall1[1];
		case 3:
			return &wall1[2];
		case 4:
			return &wall1[3];
		case 5:
			return &wall1[4];
		case 6:
			return &wall1[5];
		case 7:
			return &wall1[6];
	}	
}

void CreateWall2()
{
	int i;
   wall2[0].y=0;
   wall2[1].y=1;
   wall2[2].y=2;
   wall2[3].y=3;
   wall2[4].y=4;
   wall2[5].y=5;
   wall2[6].y=6;
  
   for(i=0;i<7;i++)
   {
	   wall2[i].x=22;
   }
}

Pgame_coord GetWall2(int i)
{
	switch (i)
	{
		case 1:
			return &wall2[0];
		case 2:
			return &wall2[1];
		case 3:
			return &wall2[2];
		case 4:
			return &wall2[3];
		case 5:
			return &wall2[4];
		case 6:
			return &wall2[5];
		case 7:
			return &wall2[6];
	}	
}

void CreateWall3()
{
	int i;
   wall3[0].x=0;
   wall3[1].x=1;
   wall3[2].x=2;
   wall3[3].x=3;
   wall3[4].x=4;
   wall3[5].x=5;
   for(i=0;i<6;i++)
   {
	   wall3[i].y=11;
   }
   wall3[6].x=0;
   wall3[7].x=1;
   wall3[8].x=2;
   wall3[9].x=3;
   wall3[10].x=4;
   wall3[11].x=5;
   for(i=6;i<12;i++)
   {
	   wall3[i].y=12;
   }
   wall3[12].x=0;
   wall3[13].x=1;
   wall3[14].x=2;
   wall3[15].x=3;
   wall3[16].x=4;
   wall3[17].x=5;
   for(i=12;i<18;i++)
   {
	   wall3[i].y=13;
   }

}

Pgame_coord GetWall3(int i)
{
	switch (i)
	{
		case 1:
			return &wall3[0];
		case 2:
			return &wall3[1];
		case 3:
			return &wall3[2];
		case 4:
			return &wall3[3];
		case 5:
			return &wall3[4];
		case 6:
			return &wall3[5];
		case 7:
			return &wall3[6];
        case 8:
			return &wall3[7];
		case 9:
			return &wall3[8];
		case 10:
			return &wall3[9];
		case 11:
			return &wall3[10];
		case 12:
			return &wall3[11];
		case 13:
			return &wall3[12];
		case 14:
			return &wall3[13];
		case 15:
			return &wall3[14];
		case 16:
			return &wall3[15];
		case 17:
			return &wall3[16];
		case 18:
			return &wall3[17];
	}	
}