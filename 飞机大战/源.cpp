#include<stdio.h>
#include<conio.h>
#include<graphics.h>

enum My
{
	WIDTH = 480,//定义的窗口宽度和高度
	HEIGHT = 700
};

//图片加载进程序
IMAGE bk;
IMAGE img_role[2];

struct Plance//飞机结构
{
	int x;
	int y;
	bool live;//飞机存活
}player;

void loadImg()
{
	//加载图片
	loadimage(&bk, "background.png");
	loadimage(&img_role[0], "we3.png");
	loadimage(&img_role[1], "me4.png");
}

void GameInit()//初始化
{
	loadImg();
	player.x = WIDTH / 2;
	player.y = HEIGHT - 120;
	player.live = true;
}


void GameDraw()
{
	//贴背景图
	putimage(0, 0, &bk);
	putimage(player.x,player.y, &img_role[0],NOTSRCERASE);
	putimage(player.x, player.y, &img_role[1],SRCINVERT);
	
}

void playerMove(int speed)//玩家移动
{
	//1,_getch()阻塞函数，没输入就会卡住，需要头函数conio.h
	char key = _getch();//读取键盘操作
	switch(key)
	{
		case 'w':
		case'W':
			if (player.y >= 0 && player.y <= HEIGHT)
			player.y -= speed;
			break;
		case 's':
		case'S':
			if (player.y >= 0 && player.y <= HEIGHT)
			player.y += speed;
			break;
		case'a':
		case'A':
			if (player.x >= 0 && player.x <= WIDTH)
			player.x -= speed;
			break;
		case'd':
		case'D':
			if (player.x >= 0 && player.x <= WIDTH)
			player.x += speed;
			break;
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
		GameDraw();
		EndBatchDraw();
		playerMove(5);
	}
	return 0;

}