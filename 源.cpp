#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<time.h>

enum My
{
	WIDTH = 480,//定义的窗口宽度和高度
	HEIGHT = 700,
	BULLLET_NUM = 10,//子弹数
	ENEMY1_NUM = 100,//敌人数
	BIG,
	SMALL
};

//图片加载进程序
IMAGE bk;
IMAGE img_role[2];
IMAGE img_bull[2];
IMAGE img_enemy1[2][2];



struct Plance//飞机结构
{
	double x;
	double y;
	bool live;//飞机存活
	double width;
	double height;//宽和高
	int type;//类型
	int hp;
}player,enemy1[ENEMY1_NUM],bull[BULLLET_NUM];



void loadImg()//加载图片
{
	loadimage(&bk, "background.png");
	loadimage(&img_role[0], "we3.png");
	loadimage(&img_role[1], "me4.png");
	loadimage(&img_bull [0] , "bullet3.png");
	loadimage(&img_bull[1], "bullet4.png");
	loadimage(&img_enemy1[0][0], "enemy222.png");
	loadimage(&img_enemy1[1][0], "enemy111.png");
	loadimage(&img_enemy1[0][1], "enemy2222.png");
	loadimage(&img_enemy1[1][1], "enemy1111.png");

}

void ememyHP(int i)
{
	for (int i = 0;i < ENEMY1_NUM;i++)
	{
		if (rand() % 10 >6)//0~9
		{
			enemy1[i].type = BIG;
			enemy1[i].hp = 3;
			enemy1[i].width = 69;
			enemy1[i].height = 99;
		}
		else
		{
			enemy1[i].type = SMALL;
			enemy1[i].hp = 1;
			enemy1[i].width = 51;
			enemy1[i].height = 57;
		}
	}
}
void GameInit()//初始化
{
	loadImg();
	player.x = WIDTH / 2;
	player.y = HEIGHT - 20;
	player.live = true;
	for (int i = 0;i < BULLLET_NUM;i++)//初始化子弹
	{
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].live = false;
	}
	for (int i = 0;i < ENEMY1_NUM;i++)//初始化敌机
	{
		enemy1[i].x = 0;
		enemy1[i].y = 0;
		enemy1[i].live = false;
		ememyHP(i);
	}
}




void GameDraw()//贴图
{
	//贴背景图
	putimage(0, 0, &bk);
	putimage(player.x,player.y, &img_role[0],NOTSRCERASE);
	putimage(player.x, player.y, &img_role[1],SRCINVERT);
	
	for (int i = 0;i < BULLLET_NUM;i++)//贴子弹图
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &img_bull[0], NOTSRCERASE);
			putimage(bull[i].x, bull[i].y, &img_bull [1] , SRCINVERT);
		}
		
	}
	
	for (int i = 0;i < ENEMY1_NUM;i++)//贴敌人图
	{
		if (enemy1[i].live&&enemy1[i].type==SMALL)
		{
			putimage(enemy1[i].x, enemy1[i].y, &img_enemy1[0][0], NOTSRCERASE);
			putimage(enemy1[i].x, enemy1[i].y, &img_enemy1[1][0], SRCINVERT);

		}
		else if (enemy1[i].live && enemy1[i].type == BIG)
		{
			putimage(enemy1[i].x, enemy1[i].y, &img_enemy1[0][1], NOTSRCERASE);
			putimage(enemy1[i].x, enemy1[i].y, &img_enemy1[1][1], SRCINVERT);
		}

	}
}
void createBullet()//子弹产生 
{
	for (int i = 0;i < BULLLET_NUM;i++)
	{
		if (!bull[i].live)
		{
			bull[i].x = player.x + 50;
			bull[i].y = player.y;
			bull[i].live = true;
			break;
		}
	}

}

void BulletMove(double speed)//子弹移动
{

	for (int i = 0;i < BULLLET_NUM;i++)
	{
		if (bull[i].live)
		{
			bull[i].y -= speed;
			if(bull[i].y<=0)
			{
				bull[i].live = false;
			}
		}
	}

}

void createEnemy1()//敌人1产生
{

	for (int i = 0;i < ENEMY1_NUM;i++)
	{
		if (!enemy1[i].live)
		{
			enemy1[i].x = rand() % WIDTH;
			enemy1[i].y = -100;
			enemy1[i].live = true;
			if (enemy1[i].type == BIG)
			{
				enemy1[i].hp = 3;
			}
				
			else if (enemy1[i].type == SMALL)
			{
				enemy1[i].hp = 1;
			}
			break;
		}
		
	}
}

void Enemy1Move(double speed)//敌人1移动
{
	for (int i = 0;i < ENEMY1_NUM;i++)
	{
		if (enemy1[i].live)
		{
			enemy1[i].y += speed;
			
			if (enemy1[i].y >= HEIGHT)
			{
				enemy1[i].live = false;
				printf("ok");
			}
		}
	}
	
}

void playerMove(double speed)//玩家移动
{
	//检测是否有键盘按下，如果有返回真，没有返回假，解决了阻塞问题
	// 另外一种解决阻塞的办法是使用#if GetAsyncKeyState(VK_UP)
	// 非阻塞函数，很丝滑
	//1,_getch()阻塞函数，没输入就会卡住，需要头函数conio.h
#if 0//这个输入函数必须用大写字母
	if (_kbhit())
	{
		char key = _getch();//读取键盘操作
		switch (key)
		{
		case 'w':
		case'W':
			if (player.y >= 0)
				player.y -= speed;
			break;
		case 's':
		case'S':
			if (player.y <= HEIGHT - 120)
				player.y += speed;
			break;
		case'a':
		case'A':
			if (player.x >= -60)
				player.x -= speed;
			break;
		case'd':
		case'D':
			if (player.x <= WIDTH - 60)
				player.x += speed;
			break;
		}
}

#elif 1
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	{
		if (player.y >= 0)
			player.y -= speed;
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (player.y <= HEIGHT -60)
			player.y += speed;
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (player.x >= -55)
			player.x -= speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if (player.x <= WIDTH - 50)
			player.x += speed;
	}


#endif
	static DWORD t1 = 0, t2 = 0,t3=0,t4=0;
	if (GetAsyncKeyState(VK_SPACE)&&t2-t1>300)//创建子弹
	{
		createBullet();
		t1 = t2;
	}
	t2 = GetTickCount();

	if (t4 - t3 > 1000)//创建敌人
	{
		createEnemy1();
		t3 = t4;
		printf("创建1\n");
	}
	t4 = GetTickCount();

}

void playPlance()//判断击中
{
	for (int i = 0;i < ENEMY1_NUM;i++)
	{
		if (!enemy1[i].live)
			continue;
		for (int k = 0;k < BULLLET_NUM;k++)
		{
			if (bull[k].live&&bull[k].x > enemy1[i].x && bull[k].x<enemy1[i].x + enemy1[i].width && 
				bull[k].y>enemy1[i].y && bull[k].y < enemy1[i].y + enemy1[i].height)
			{
				bull[k].live = false;
				enemy1[i].hp--;
				printf("die");
			}
			
		}
		if (enemy1[i].hp <= 0)
		{
			enemy1[i].live = false;
		}
	}
}


int main()
{
	//创建窗口
	initgraph(WIDTH,HEIGHT,SHOWCONSOLE);
	GameInit();
	BeginBatchDraw();//开始双缓冲
	while (1)
	{
		GameDraw();//贴图
		FlushBatchDraw();//执行未完成的绘制任务
		playerMove(0.05);//玩家移动
		Enemy1Move(0.03);//敌人1移动
		BulletMove(0.1);//子弹移动
		playPlance();//判断击中
		
	}
	EndBatchDraw();//结束双缓冲
	return 0;

}