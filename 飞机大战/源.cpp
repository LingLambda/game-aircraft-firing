#include<stdio.h>
#include<conio.h>
#include<graphics.h>

enum My
{
	WIDTH = 480,//����Ĵ��ڿ�Ⱥ͸߶�
	HEIGHT = 700
};

//ͼƬ���ؽ�����
IMAGE bk;
IMAGE img_role[2];

struct Plance//�ɻ��ṹ
{
	int x;
	int y;
	bool live;//�ɻ����
}player;

void loadImg()
{
	//����ͼƬ
	loadimage(&bk, "background.png");
	loadimage(&img_role[0], "we3.png");
	loadimage(&img_role[1], "me4.png");
}

void GameInit()//��ʼ��
{
	loadImg();
	player.x = WIDTH / 2;
	player.y = HEIGHT - 120;
	player.live = true;
}


void GameDraw()
{
	//������ͼ
	putimage(0, 0, &bk);
	putimage(player.x,player.y, &img_role[0],NOTSRCERASE);
	putimage(player.x, player.y, &img_role[1],SRCINVERT);
	
}

void playerMove(int speed)//����ƶ�
{
	//1,_getch()����������û����ͻῨס����Ҫͷ����conio.h
	char key = _getch();//��ȡ���̲���
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
	//��������
	initgraph(WIDTH,HEIGHT,SHOWCONSOLE);
	GameInit();
	BeginBatchDraw();//��ʼ˫����
	while (1)
	{
		GameDraw();
		EndBatchDraw();
		playerMove(5);
	}
	return 0;

}