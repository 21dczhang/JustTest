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
void gotoxy(int x, int y) //����������(x,y)��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor()  //���ع����ʾ
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void help()
{

	printf("                               ��w�����������ƶ�\n     ");
	printf("                          ��s�����������ƶ�\n     ");
	printf("                          ��a�����������ƶ�\n     ");
	printf("                          ��d�����������ƶ�\n     ");
	printf("                 ����1������ͨģʽ������2�����޾�ģʽ\n");
}
void begin()
{
	IMAGE logo, help;
	initgraph(1280 + 170, 720);
	MOUSEMSG m;
	loadimage(&help, L"picture//��ʾ.jpg");
	loadimage(&logo, L"picture//logo.jpg");
	putimage(415, 0, &logo);
	setlinecolor(WHITE);
	setfillcolor(BLACK);
	//�ڶ�Ӧλ�����������
	fillrectangle(200, 350, 350, 420);
	fillrectangle(500, 350, 650, 420);
	fillrectangle(800, 350, 950, 420);
	fillrectangle(1100, 350, 1250, 420);
	settextstyle(31.25, 0, L"����");
	//�ڳ����������������
	outtextxy(215, 368.75, L"��ͨģʽ");
	outtextxy(515, 368.75, L"�޾�ģʽ");
	outtextxy(815, 368.75, L"����ģʽ");
	outtextxy(1115, 368.75, L"������ʾ");
	/*mciSendString(L"open music//bk.mp3 alias BKBGM",0,0,0);
	mciSendString(L"play BKBGM repeat", 0, 0, 0);*/
	mciSendString(L"open music//3.mp3 alias BGM1", 0, 0, 0);//��������
	mciSendString(L"play BGM1 repeat", 0, 0, 0);
	while (!choose) {
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE://���ͣ�ڵ��ĸ��������ϣ���ʾ��Ϸ��ʾ
			if (m.x >= 1100 && m.x <= 1250 && m.y >= 350 && m.y <= 420)
			{
				putimage(115, 500, &help);
			}
			else
			{
				solidrectangle(0, 430, 1450, 720);
			}
			break;
		case WM_LBUTTONDOWN://����ڶ�Ӧλ�ð��������������Ӧģʽ��
			//���ر�����
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
