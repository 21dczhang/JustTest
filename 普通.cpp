#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define side 25//定义游戏地图边长
#define max 20//定义蛇的最大长度
#define Speed1 70//定义速度（数字越小蛇运动越快）
//#define player player1
int i1, j1, k1, judge1 = 1, speed1 = 0;//judge用来决定游戏是否结束
void gotoxy(int x, int y);
void HideCursor();
struct snake1//定义蛇的结构体
{
    int x[max], y[max];//x[0]和y[0]是蛇头坐标，其余为蛇身体坐标
    int food_x, food_y;//食物坐标
    int lenth;//蛇的长度
    int obstacle_x[max / 2], obstacle_y[max / 2];
    int special_x = -1, special_y = 1;
}player1;
enum direction1//枚举所有可能的方向
{
    up1, down1, left1, right1
}dir1;
void initgame1()//初始化游戏
{
    dir1 = up1;//蛇的初始方向向上
    player1.lenth = 3;//蛇的初始长度为3
    srand((unsigned)time(NULL));
    player1.x[0] = side / 2;//初始化蛇头的坐标
    player1.y[0] = side / 2;
    for (i1 = 1; i1 < player1.lenth; i1++)//初始化蛇身体坐标
    {
        player1.x[i1] = player1.x[i1 - 1];
        player1.y[i1] = player1.y[i1 - 1] + 1;

    }
    player1.food_x = rand() % (side - 1) + 1;//初始化食物坐标
    player1.food_y = rand() % (side - 1) + 1;
}
void move1()//由键盘输入对应按键，改变蛇的方向（不能转向90度，如方向为下
           //不能直接改变为向上）
{
    char c;
    if (_kbhit())
    {
        c = _getch();
        switch (c)
        {
        case'W':case'w': {if (dir1 != down1) dir1 = up1; break; }
        case'S':case's': {if (dir1 != up1) dir1 = down1; break; }
        case'A':case'a': {if (dir1 != right1) dir1 = left1; break; }
        case'D':case'd': {if (dir1 != left1) dir1 = right1; break; }
        }

    }
}
void automatic1()
{
    srand((unsigned)time(NULL));
    static int s1 = 0;
    static int t1 = 0;
    if (t1 < Speed1 - speed1) t1++;/*用来判断蛇头是否已经行动，如果是则清除地图中蛇身体
                             最后一节*/
    else
    {
        t1 = 0;
        gotoxy(player1.x[player1.lenth - 1], player1.y[player1.lenth - 1]);
        printf(" ");
        if (judge1 != 0)//游戏继续则将第i节的坐标赋给第i-1节，达到运动的目的
        {
            for (i1 = player1.lenth - 1; i1 > 0; i1--)
            {
                player1.x[i1] = player1.x[i1 - 1];
                player1.y[i1] = player1.y[i1 - 1];
                while (player1.food_x == player1.x[i1] && player1.food_y == player1.y[i1])
                {//如果食物坐标与蛇身体坐标重叠，则刷新食物坐标
                    player1.food_x = rand() % (side - 1) + 1;
                    player1.food_y = rand() % (side - 1) + 1;
                }
            }
        }
        switch (player1.lenth)//根据长度改变蛇的速度
        {
        case 5: speed1 = 15; break;
        case 10:speed1 = 25; break;
        case 15:speed1 = 35; break;
        case 20:judge1 = 0;  break;

        }
    }
    //根据当前方向，让蛇自己前进
    if (dir1 == up1)
    {
        if (s1 < Speed1 - speed1) s1++;
        else { s1 = 0; player1.y[0] = player1.y[0] - 1; }
    }
    else if (dir1 == down1)
    {
        if (s1 < Speed1 - speed1) s1++;
        else { s1 = 0; player1.y[0] = player1.y[0] + 1; }
    }
    else if (dir1 == left1)
    {
        if (s1 < Speed1 - speed1) s1++;
        else { s1 = 0; player1.x[0] = player1.x[0] - 1; }
    }
    else if (dir1 == right1)
    {
        if (s1 < Speed1 - speed1) s1++;
        else { s1 = 0; player1.x[0] = player1.x[0] + 1; }
    }
    gotoxy(2 * side, side / 2 + 1);
    printf("当前长度为%d", player1.lenth);//输出当前长度
}

void show1()
{
    for (k1 = 0; k1 <= side; k1++)//输出栅栏
    {
        gotoxy(k1, 0); printf("#");
        gotoxy(k1, side); printf("#");
    }
    for (k1 = 1; k1 <= side - 1; k1++)
    {
        gotoxy(0, k1); printf("#");
        gotoxy(side, k1); printf("#");
    }
    gotoxy(player1.x[0], player1.y[0]);//输出蛇头
    printf("X");
    for (k1 = 1; k1 < player1.lenth; k1++)//输出身体
    {
        gotoxy(player1.x[k1], player1.y[k1]);
        printf("O");
    }
    gotoxy(player1.food_x, player1.food_y);//输出食物
    printf("?");

}

void move()//由键盘输入对应按键，改变蛇的方向（不能转向90度，如方向为下
           //不能直接改变为向上）
{
    char c;
    if (_kbhit())
    {
        c = _getch();
        switch (c)
        {
        case'W':case'w': {if (dir1 != down1) dir1 = up1; break; }
        case'S':case's': {if (dir1 != up1) dir1 = down1; break; }
        case'A':case'a': {if (dir1 != right1) dir1 = left1; break; }
        case'D':case'd': {if (dir1 != left1) dir1 = right1; break; }
        }

    }
}
void food1()//当蛇头吃掉食物时，刷新食物坐标
{
    if (player1.x[0] == player1.food_x && player1.y[0] == player1.food_y)
    {
        player1.lenth++;
        player1.food_x = rand() % (side - 1) + 1;
        player1.food_y = rand() % (side - 1) + 1;
    }
}

void decide1()//判读游戏是否结束
{
    if (player1.x[0] == 0 || player1.x[0] == side) judge1 = 0;//蛇头与栅栏相碰，结束
    if (player1.y[0] == 0 || player1.y[0] == side) judge1 = 0;//蛇头与栅栏相碰，结束
    for (k1 = 1; k1 < player1.lenth; k1++)//判断蛇头是否与身体相碰
    {

        if (player1.x[0] == player1.x[k1] && player1.y[0] == player1.y[k1])
            judge1 = 0;//蛇头与身体相碰，游戏结束
    }
    switch (player1.lenth)//根据长度改变蛇的速度
    {
    case 5: speed1 = 15; break;
    case 10:speed1 = 25; break;
    case 15:speed1 = 35; break;
    case 20:judge1 = 0;  break;

    }

}

void help1()//游戏的提示
{
    
    printf("                          这是普通模式\n     ");
    printf("                 当蛇与栅栏或者身体相碰时，游戏结束\n");
    printf("                       吃到?可以增加蛇的长度\n  ");
    printf("               当长度分别达到5、10、15时，蛇的速度会变快\n");
    printf("                      当长度达到%d时，游戏通关！\n", max);
    system("pause");
    system("cls");
}
void main1()//开始游戏
{

    HideCursor();
    initgame1();
    help1();
    while (judge1)
    {
        show1();
        move1();
        food1();
        decide1();
        automatic1();
    }
    gotoxy(player1.x[player1.lenth - 1], player1.y[player1.lenth - 1]);
    printf("O");
    gotoxy(2 * side, side / 2);
    if (player1.lenth >= 20) printf("恭喜！您已经通关！");
    else printf("很遗憾，您失败了！");
    gotoxy(0, side + 1);
    Sleep(800);
}
