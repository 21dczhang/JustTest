#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <graphics.h> 
#include <conio.h>   
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define X_Max 1280-120//定义蛇可活动地图x轴长度
#define Y_Max 720//定义蛇可活动地图y轴长度
#define Food_Max 200//定义地图中同时存在的食物数量
#define Lenth_Max 100//定义蛇的最大长度，达到即可通关
#define picture_r 25//素材图片的大小为25*25
#define Speed_Max 25*5//定义蛇的速度
#define Pervalue 20//定义分数每达到pervalue分数时长度加1
#define SFood_Max 10//定义特殊食物（水果）的数量
//int choose = 0;//选择程序执行哪种模式
int score, life = 1, cheat = 1;//life记录玩家是否死亡，cheat记录是否开启作弊
double r = picture_r / 2, player_x, player_y;
TCHAR a[30];
IMAGE logo, help, head1, Yhead1, head2, Yhead2, head3, Yhead3, head4, Yhead4;
IMAGE food1, food2, food3, food4, food5, trophy, body, Ybody, bk, bk2, Ybk2;
struct Snack//定义蛇的结构体
{
	int pos_x[Lenth_Max], pos_y[Lenth_Max];
	int speed = 25;//定义蛇的速度
	int size;
}snack;
enum direction//定义方向
{
	up, down, left, right
}dir;
struct Food//定义食物结构体
{
	int value;
	int r;
	DWORD color;
	int pos_x, pos_y;
}food[Food_Max];
struct SFood//定义特殊食物结构体
{
	int pos_x, pos_y;//定义贴图坐标
	int type;//定义特殊食物类型，根据类型显示不同图片和音效
	int value = 20;//定义特殊食物分数
	double centre_x, centre_y;//定义特殊食物中心，用来计算与蛇头距离
}SFood[SFood_Max];
void initfood(int i)//初始化食物
{

	food[i].value = rand() % 11;//初始化食物分数
	food[i].r = 5 + rand() % 5;//初始化食物半径
	food[i].pos_x = rand() % X_Max;//初始化食物坐标
	food[i].pos_y = rand() % Y_Max;
	food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	//初始化食物颜色
}
void initSfood(int i)
{
	SFood[i].pos_x = rand() % X_Max;//初始化贴图坐标
	SFood[i].pos_y = rand() % Y_Max;
	SFood[i].type = 1 + rand() % 5;//初始化类型
	SFood[i].centre_x = SFood[i].pos_x + r;//初始化图片中心
	SFood[i].centre_y = SFood[i].pos_y + r;
}
void initgame()
{
	mciSendString(L"open music//bk.mp3 alias BGM", 0, 0, 0);
	mciSendString(L"play BGM repeat", 0, 0, 0);
	snack.size = 3;//初始化长度
	initgraph(1280 + 120 + 50, 720, SHOWCONSOLE);
	loadimage(&Yhead1, L"picture//head2.jpg");
	loadimage(&head1, L"picture//head1.jpg");
	loadimage(&Yhead2, L"picture//head4.jpg");
	loadimage(&head2, L"picture//head3.jpg");
	loadimage(&Yhead3, L"picture//head6.jpg");
	loadimage(&head3, L"picture//head5.jpg");
	loadimage(&Yhead4, L"picture//head8.jpg");
	loadimage(&head4, L"picture//head7.jpg");
	loadimage(&Ybody, L"picture//body2.jpg");
	loadimage(&body, L"picture//body1.jpg");
	loadimage(&bk, L"picture//bk.jpg");
	loadimage(&Ybk2, L"picture//bk3jpg.");
	loadimage(&bk2, L"picture//bk2.jpg");
	loadimage(&food1, L"picture//food1.jpg");
	loadimage(&food2, L"picture//food2.jpg");
	loadimage(&food3, L"picture//food3.jpg");
	loadimage(&food4, L"picture//food4.jpg");
	loadimage(&food5, L"picture//food5.jpg");
	loadimage(&trophy, L"picture//trophy.jpg");
	snack.pos_x[0] = 640;//初始化蛇头位置
	snack.pos_y[0] = 360;
	dir = right;//初始化蛇头方向
	for (int i = 1; i < snack.size; i++)//初始化蛇身
	{
		snack.pos_x[i] = snack.pos_x[i - 1] - picture_r + 3;
		snack.pos_y[i] = snack.pos_y[i - 1];
	}
	for (int i = 0; i < Food_Max; i++)//初始化食物
	{
		initfood(i);
	}
	for (int i = 0; i < SFood_Max; i++)
	{
		initSfood(i);
	}
}
void show()
{
	cleardevice();//清屏
	BeginBatchDraw();//防止闪屏
	putimage(0, 0, &bk);//输出背景
	putimage(1160, 0, &Ybk2, SRCAND);
	putimage(1160, 0, &bk2, SRCPAINT);
	setbkmode(TRANSPARENT);
	if (cheat) outtextxy(1250, 400, L"作弊模式:开");//显示作弊模式开关
	else outtextxy(1250, 400, L"作弊模式:关");
	_stprintf_s(a, L"当前长度为%d,达到100即可通关!", snack.size);//显示蛇长度
	outtextxy(1200, 450, a);
	outtextxy(1230, 500, L"n/N   开启/关闭作弊模式");
	if (snack.size == 99) putimage(0, 0, &trophy);//当长度达到99，显示奖杯
	switch (dir)//根据方向让蛇自己前进
	{
	case up:putimage(snack.pos_x[0], snack.pos_y[0], &Yhead1, SRCAND);
		putimage(snack.pos_x[0], snack.pos_y[0], &head1, SRCPAINT); break;
	case down:putimage(snack.pos_x[0], snack.pos_y[0], &Yhead2, SRCAND);
		putimage(snack.pos_x[0], snack.pos_y[0], &head2, SRCPAINT); break;
	case left:putimage(snack.pos_x[0], snack.pos_y[0], &Yhead3, SRCAND);
		putimage(snack.pos_x[0], snack.pos_y[0], &head3, SRCPAINT); break;
	case right:putimage(snack.pos_x[0], snack.pos_y[0], &Yhead4, SRCAND);
		putimage(snack.pos_x[0], snack.pos_y[0], &head4, SRCPAINT); break;
	}
	for (int i = 1; i < snack.size; i++)
	{//输出身体
		putimage(snack.pos_x[i], snack.pos_y[i], &Ybody, SRCAND);
		putimage(snack.pos_x[i], snack.pos_y[i], &body, SRCPAINT);
	}
	for (int i = 0; i < Food_Max; i++) {
		setfillcolor(food[i].color);//输出食物
		solidcircle(food[i].pos_x, food[i].pos_y, food[i].r);
	}
	for (int i = 0; i < SFood_Max; i++)
	{//输出特殊食物
		switch (SFood[i].type)
		{
		case 1:putimage(SFood[i].pos_x, SFood[i].pos_y, &food1); break;
		case 2:putimage(SFood[i].pos_x, SFood[i].pos_y, &food2); break;
		case 3:putimage(SFood[i].pos_x, SFood[i].pos_y, &food3); break;
		case 4:putimage(SFood[i].pos_x, SFood[i].pos_y, &food4); break;
		case 5:putimage(SFood[i].pos_x, SFood[i].pos_y, &food5); break;
		}
	}
	EndBatchDraw();
	//setcliprgn();
	//clearcliprgn();
}
void Copy() {//复制身体

	for (int i = snack.size - 1; i; i--) {
		snack.pos_x[i] = snack.pos_x[i - 1];
		snack.pos_y[i] = snack.pos_y[i - 1];
	}
	switch (dir)
	{
	case up:snack.pos_y[0] -= picture_r - 3; break;
	case down:snack.pos_y[0] += picture_r - 3; break;
	case left:snack.pos_x[0] -= picture_r - 3; break;
	case right:snack.pos_x[0] += picture_r - 3; break;
	}
}
void without()
{//与用户无关的更新
	static int speed = Speed_Max;//设置速度
	if (speed) speed--;
	else {
		Copy();//复制身体
		speed = Speed_Max;//速度归原
		player_x = snack.pos_x[0] + r;//蛇头前进
		player_y = snack.pos_y[0] + r;
	}
	if (snack.size == 99)//长度达到99时
	{
		double distan;//蛇头与奖杯图片的距离
		distan = sqrt(pow(player_x - 25, 2) + pow(player_y - 22, 2));
		if (distan <= 2 * (double)picture_r)
		{
			life = 0;//结束游戏
		}
	}

}
void Foodupdata()
{
	double distance;
	for (int i = 0; i < Food_Max; i++)
	{//吃到食物
		distance = sqrt(pow(player_x - food[i].pos_x, 2) + pow(player_y - food[i].pos_y, 2));
		if (distance <= food[i].r + r)
		{//每吃到一个食物，分数叠加，并刷新一个食物
			score += food[i].value;
			initfood(i);
			
		}
	}
	for (int i = 0; i < SFood_Max; i++)
	{
		distance = sqrt(pow(player_x - SFood[i].centre_x, 2) + pow(player_y - SFood[i].centre_y, 2));
		if (distance <= 2 * r)
		{
			switch (1 + rand() % 5)
			{//根据类型播放对应音效
			case 1:mciSendString(L"closw  BGM1", 0, 0, 0);
				mciSendString(L"open music//m1.mp3 alias BGM1 ", 0, 0, 0);
				mciSendString(L"play BGM1", 0, 0, 0); break;
			case 2:mciSendString(L"close  BGM2", 0, 0, 0);
				mciSendString(L"open music//m2.mp3 alias BGM2 ", 0, 0, 0);
				mciSendString(L"play BGM2", 0, 0, 0); break;
			case 3:mciSendString(L"close  BGM3", 0, 0, 0);
				mciSendString(L"open music//m3.mp3 alias BGM3 ", 0, 0, 0);
				mciSendString(L"play BGM3", 0, 0, 0); break;
			case 4:mciSendString(L"close  BGM4", 0, 0, 0);
				mciSendString(L"open music//m4.mp3 alias BGM4 ", 0, 0, 0);
				mciSendString(L"play BGM4", 0, 0, 0); break;
			case 5:mciSendString(L"close  BGM5", 0, 0, 0);
				mciSendString(L"open music//m5.mp3 alias BGM5 ", 0, 0, 0);
				mciSendString(L"play BGM5", 0, 0, 0); break;
			}
			score += SFood[i].value;
			initSfood(i);
		}
	}
	if (snack.size == 99)
	{//长度达到99时，将所有食物移除屏幕
		for (int i = 0; i < Food_Max; i++)
		{
			food[i].pos_x = -50;
			food[i].pos_y = -50;
		}
		for (int i = 0; i < SFood_Max; i++)
		{
			SFood[i].pos_x = -50;
			SFood[i].pos_y = -50;
		}
	}
}
void BodySizeupdata()
{//根据分数增加蛇的长度
	if (score < Pervalue) return;
	else {
		if (snack.size < 99)//小于99时，增加，达到99后吃食物不再增加
		{
			snack.size += score / Pervalue; score = score % Pervalue;
			
		}
	}
	Copy();
}
void Key_Control() {
	// 72, 80, 75, 77  上下左右键值
	//判断是否有按键，没有返回假
	if (_kbhit() == false) return;
	switch (_getch()) {
	case 'W':
	case 'w':
	case 72:
		if (dir == down) break;
		dir = up;
		break;
	case 'S':
	case 's':
	case 80:
		if (dir == up) break;
		dir = down;
		break;
	case 'A':
	case 'a':
	case 75:
		if (dir == right) break;
		dir = left;
		break;
	case 'D':
	case 'd':
	case 77:
		if (dir == left) break;
		dir = right;
		break;

	case ' ': //游戏停止与继续
		while (1) {
			if (_getch() == ' ') return;
		}
		break;
	case 'N'://作弊是否开启
	case'n':
		if (cheat == 0) cheat = 1;
		else cheat = 0;
		break;
	}
}
void Gamerule()
{//根据作弊是否开启执行对应规则
	if (!cheat)
	{
		if (snack.pos_x[0]<0 || snack.pos_x[0]>X_Max || snack.pos_y[0]<0 || snack.pos_y[0]>Y_Max)
			life = 0;
		for (int i = 1; i < snack.size - 1; i++)
		{
			if (snack.pos_x[0] == snack.pos_x[i] && snack.pos_y[0] == snack.pos_y[i])
				life = 0;
		}
	}
	else {
		if (snack.pos_x[0] <= 0) snack.pos_x[0] = X_Max - 1.5 * picture_r;
		if (snack.pos_x[0] + picture_r >= X_Max) snack.pos_x[0] = 1.5 * picture_r;
		if (snack.pos_y[0] <= 0) snack.pos_y[0] = Y_Max - 1.5 * picture_r;
		if (snack.pos_y[0] + picture_r >= Y_Max) snack.pos_y[0] = 1.5 * picture_r;
	}
}
void Gameover()
{
	mciSendString(L"close BGM",0,0,0);
	IMAGE dead,victory;
	loadimage(&dead, L"picture//dead.jpg");
	loadimage(&victory, L"picture//victory.jpg");
	cleardevice();//清屏
	if (snack.size ==99)  putimage(360, 0, &victory);
	else  putimage(362, 0, &dead);
	mciSendString(L"open music//dead.mp3 alias dead", 0, 0, 0);
	mciSendString(L"play dead ", 0, 0, 0);
	Sleep(4500);
}
void main3()
{
	//begin();
	initgame();
	while (life)
	{
		show();
		Key_Control();
		without();
		Foodupdata();
		BodySizeupdata();
		Gamerule();
	}
	Gameover();
	return ;
}