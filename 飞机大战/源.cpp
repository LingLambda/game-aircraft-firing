#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<time.h>

enum My
{
	WIDTH = 480,//����Ĵ��ڿ�Ⱥ͸߶�
	HEIGHT = 700,
	BULLLET_NUM = 10,//�ӵ���
	ENEMY1_NUM = 100,//������
	BIG,
	SMALL
};

//ͼƬ���ؽ�����
IMAGE bk;
IMAGE img_role[2];
IMAGE img_bull[2];
IMAGE img_enemy1[2][2];



struct Plance//�ɻ��ṹ
{
	double x;
	double y;
	bool live;//�ɻ����
	double width;
	double height;//��͸�
	int type;//����
	int hp;
}player,enemy1[ENEMY1_NUM],bull[BULLLET_NUM];



void loadImg()//����ͼƬ
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
void GameInit()//��ʼ��
{
	loadImg();
	player.x = WIDTH / 2;
	player.y = HEIGHT - 20;
	player.live = true;
	for (int i = 0;i < BULLLET_NUM;i++)//��ʼ���ӵ�
	{
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].live = false;
	}
	for (int i = 0;i < ENEMY1_NUM;i++)//��ʼ���л�
	{
		enemy1[i].x = 0;
		enemy1[i].y = 0;
		enemy1[i].live = false;
		ememyHP(i);
	}
}




void GameDraw()//��ͼ
{
	//������ͼ
	putimage(0, 0, &bk);
	putimage(player.x,player.y, &img_role[0],NOTSRCERASE);
	putimage(player.x, player.y, &img_role[1],SRCINVERT);
	
	for (int i = 0;i < BULLLET_NUM;i++)//���ӵ�ͼ
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &img_bull[0], NOTSRCERASE);
			putimage(bull[i].x, bull[i].y, &img_bull [1] , SRCINVERT);
		}
		
	}
	
	for (int i = 0;i < ENEMY1_NUM;i++)//������ͼ
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
void createBullet()//�ӵ����� 
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

void BulletMove(double speed)//�ӵ��ƶ�
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

void createEnemy1()//����1����
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

void Enemy1Move(double speed)//����1�ƶ�
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

void playerMove(double speed)//����ƶ�
{
	//����Ƿ��м��̰��£�����з����棬û�з��ؼ٣��������������
	// ����һ�ֽ�������İ취��ʹ��#if GetAsyncKeyState(VK_UP)
	// ��������������˿��
	//1,_getch()����������û����ͻῨס����Ҫͷ����conio.h
#if 0//������뺯�������ô�д��ĸ
	if (_kbhit())
	{
		char key = _getch();//��ȡ���̲���
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
	if (GetAsyncKeyState(VK_SPACE)&&t2-t1>300)//�����ӵ�
	{
		createBullet();
		t1 = t2;
	}
	t2 = GetTickCount();

	if (t4 - t3 > 1000)//��������
	{
		createEnemy1();
		t3 = t4;
		printf("����1\n");
	}
	t4 = GetTickCount();

}

void playPlance()//�жϻ���
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
	//��������
	initgraph(WIDTH,HEIGHT,SHOWCONSOLE);
	GameInit();
	BeginBatchDraw();//��ʼ˫����
	while (1)
	{
		GameDraw();//��ͼ
		FlushBatchDraw();//ִ��δ��ɵĻ�������
		playerMove(0.05);//����ƶ�
		Enemy1Move(0.03);//����1�ƶ�
		BulletMove(0.1);//�ӵ��ƶ�
		playPlance();//�жϻ���
		
	}
	EndBatchDraw();//����˫����
	return 0;

}