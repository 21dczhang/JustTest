#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <graphics.h> 
#include <conio.h>   
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
int choose=0;
extern void main1();
extern void main2();
extern void main3();
void gotoxy(int x, int y) //将光标调整到(x,y)的位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor()  //隐藏光标显示
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void help()
{

	printf("                               用w控制蛇向上移动\n     ");
	printf("                          用s控制蛇向下移动\n     ");
	printf("                          用a控制蛇向左移动\n     ");
	printf("                          用d控制蛇向右移动\n     ");
	printf("                 输入1进入普通模式，输入2进入无尽模式\n");
}
void begin()
{
	IMAGE logo, help;
	initgraph(1280 + 170, 720);
	MOUSEMSG m;
	loadimage(&help, L"picture//提示.jpg");
	loadimage(&logo, L"picture//logo.jpg");
	putimage(415, 0, &logo);
	setlinecolor(WHITE);
	setfillcolor(BLACK);
	//在对应位置输出长方形
	fillrectangle(200, 350, 350, 420);
	fillrectangle(500, 350, 650, 420);
	fillrectangle(800, 350, 950, 420);
	fillrectangle(1100, 350, 1250, 420);
	settextstyle(31.25, 0, L"宋体");
	//在长方形里面输出文字
	outtextxy(215, 368.75, L"普通模式");
	outtextxy(515, 368.75, L"无尽模式");
	outtextxy(815, 368.75, L"特殊模式");
	outtextxy(1115, 368.75, L"操作提示");
	/*mciSendString(L"open music//bk.mp3 alias BKBGM",0,0,0);
	mciSendString(L"play BKBGM repeat", 0, 0, 0);*/
	mciSendString(L"open music//3.mp3 alias BGM1", 0, 0, 0);//播放音乐
	mciSendString(L"play BGM1 repeat", 0, 0, 0);
	while (!choose) {
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE://鼠标停在第四个长方形上，显示游戏提示
			if (m.x >= 1100 && m.x <= 1250 && m.y >= 350 && m.y <= 420)
			{
				putimage(115, 500, &help);
			}
			else
			{
				solidrectangle(0, 430, 1450, 720);
			}
			break;
		case WM_LBUTTONDOWN://鼠标在对应位置按下左键，开启对应模式，
			//并关闭音乐
			if (m.x >= 200 && m.x <= 350 && m.y >= 350 && m.y <= 420)
			{
				choose = 1; mciSendString(L"close BGM1", 0, 0, 0);
			}
			if (m.x >= 500 && m.x <= 650 && m.y >= 350 && m.y <= 420)
			{
				choose = 2; mciSendString(L"close BGM1", 0, 0, 0);
			}
			if (m.x >= 800 && m.x <= 950 && m.y >= 350 && m.y <= 420)
			{
				choose = 3; mciSendString(L"close BGM1", 0, 0, 0);
			}
		}
	}
}
int main()
{

	begin();
	if (choose == 1) { closegraph(),main1(); }
	else if (choose == 2) { closegraph(), main2(); }
	else main3();
}
