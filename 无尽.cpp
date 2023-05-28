#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define side 25//定义游戏地图边长
#define Max 100//定义无尽模式蛇的最大长度
#define Speed2 70//定义速度（数字越小蛇运动越快）
#define player player2
int i2, j2, k2, judge2 = 1, speed2 = 0, creat = 1;//judge用来决定游戏是否结束
extern void gotoxy(int x, int y);
extern void HideCursor();
struct snake2//定义蛇的结构体
{
    int x[Max], y[Max];//x[0]和y[0]是蛇头坐标，其余为蛇身体坐标
    int food_x, food_y;//食物坐标
    int lenth;//蛇的长度
    int obstacle_x[Max], obstacle_y[Max];//障碍物坐标
    int special_x = -1, special_y = 1;
}player2;
enum direction2//枚举所有可能的方向
{
    up2, down2, left2, right2
}dir2;
void initgame2()//初始化游戏
{
    dir2 = up2;//蛇的初始方向向上
    player.lenth = 3;//蛇的初始长度为3
    srand((unsigned)time(NULL));
    player.x[0] = side / 2;//初始化蛇头的坐标
    player.y[0] = side / 2;
    player.obstacle_x[0] = rand() % (side - 1) + 1;//初始化障碍
    player.obstacle_y[0] = rand() % (side - 1) + 1;
    for (i2 = 1; i2 < player.lenth; i2++)//初始化蛇身体坐标
    {
        player.x[i2] = player.x[i2 - 1];
        player.y[i2] = player.y[i2 - 1] + 1;
    }
    //for (int i = 1; i < Max ; i++)//其他障碍暂时不出现在屏幕
    //{
    //    player.obstacle_x[i] = -1;
    //    player.obstacle_y[i] = -1;
    //}
    player.food_x = rand() % (side - 1) + 1;//初始化食物坐标
    player.food_y = rand() % (side - 1) + 1;
    player.special_x = -150;//特殊食物暂时不出现
    player.special_y = -150;
}
void automatic2()
{
    srand((unsigned)time(NULL));
    static int s2 = 0;
    static int t2 = 0;
    if (t2 < Speed2 - speed2) t2++;/*用来判断蛇头是否已经行动，如果是则清除地图中蛇身体
                             最后一节*/
    else
    {
        t2 = 0;
        gotoxy(player.x[player.lenth - 1], player.y[player.lenth - 1]);
        printf(" ");
        if (judge2 != 0)//游戏继续则将第i节的坐标赋给第i-1节，达到运动的目的
        {
            for (i2 = player.lenth - 1; i2 > 0; i2--)
            {
                player.x[i2] = player.x[i2 - 1];
                player.y[i2] = player.y[i2 - 1];
                while (player.food_x == player.x[i2] && player.food_y == player.y[i2] ||
                    player.food_x == player.obstacle_x[i2] && player.food_y == player.obstacle_y[i2] ||
                    player.food_x == player.special_x && player.food_y == player.special_y)
                {//如果食物坐标与蛇身体坐标或者障碍坐标或者特殊食物坐标重叠，则刷新食物坐标
                    player.food_x = rand() % (side - 1) + 1;
                    player.food_y = rand() % (side - 1) + 1;
                }
                while (player.special_x == player.x[i2] && player.special_y == player.y[i2] ||
                    player.special_x == player.obstacle_x[i2] && player.special_y == player.obstacle_y[i2])
                {//与automatic1的区别，增加特殊食物的判断
                    player.special_x = rand() % (side - 1) + 1;
                    player.special_y = rand() % (side - 1) + 1;
                }

            }
            switch (player.lenth)//根据长度改变蛇的速度
            {
            case 5 * 1: speed2 = 15; break;
            case 5 * 2: speed2 = 25; break;
            case 5 * 3: speed2 = 35; break;
            case 5 * 4: speed2 = 45; break;
            case 5 * 5: speed2 = 55; break;
            case 5 * 6: speed2 = 65; break;
                /* case 5 * 7: speed2 = 75; break;
                 case 5 * 8: speed2 = 55; break;
                 case 5 * 9: speed2 = 55; break;
                 case 5 * 10: judge2 = 0; break;*/
                 //case 5 * 10: speed = 75; break;
                // case 5 * 11: speed = 80; break;
            }


        }
    }
    //根据当前方向，让蛇自己前进
    if (dir2 == up2)
    {
        if (s2 < Speed2 - speed2) s2++;
        else
        {
            s2 = 0;
            if (player.y[0] == 0 || player.y[0] == 1) player.y[0] = side - 1;
            else  player.y[0] = player.y[0] - 1;
        }
    }
    else if (dir2 == down2)
    {
        if (s2 < Speed2 - speed2) s2++;
        else
        {
            s2 = 0;
            if (player.y[0] == side || player.y[0] == side - 1) player.y[0] = 1;
            else  player.y[0] = player.y[0] + 1;
        }
    }
    else if (dir2 == left2)
    {
        if (s2 < Speed2 - speed2) s2++;
        else
        {
            s2 = 0;
            if (player.x[0] == 0 || player.x[0] == 1) player.x[0] = side - 1;
            else  player.x[0] = player.x[0] - 1;
        }
    }
    else if (dir2 == right2)
    {
        if (s2 < Speed2 - speed2) s2++;
        else
        {
            s2 = 0;
            if (player.x[0] == side || player.x[0] == side - 1) player.x[0] = 1;
            else player.x[0] = player.x[0] + 1;
        }
    }
    gotoxy(2 * side, side / 2 + 1);
    printf("当前长度为%d", player.lenth);//输出当前长度
}
void show2()
{
    for (k2 = 0; k2 <= side; k2++)//输出栅栏
    {
        gotoxy(k2, 0); printf("#");
        gotoxy(k2, side); printf("#");
    }
    for (k2 = 1; k2 <= side - 1; k2++)
    {
        gotoxy(0, k2); printf("#");
        gotoxy(side, k2); printf("#");
    }
    gotoxy(player.x[0], player.y[0]);//输出蛇头
    printf("X");
    for (k2 = 1; k2 < player.lenth; k2++)//输出身体
    {
        gotoxy(player.x[k2], player.y[k2]);
        printf("O");
    }
    gotoxy(player.food_x, player.food_y);//输出食物
    printf("?");
    for (k2 = 0; k2 < Max; k2++)//输出障碍物
    {
        if (k2 % 2 != 0)
        {
            gotoxy(player.obstacle_x[k2], player.obstacle_y[k2]);
            printf("|");
        }
        if (k2 % 2 == 0)
        {
            gotoxy(player.obstacle_x[k2], player.obstacle_y[k2]);
            printf("—");
        }
    }
    gotoxy(player.special_x, player.special_y);//输出特殊食物
    printf("☆");
}
void move2()//由键盘输入对应按键，改变蛇的方向（不能转向90度，如方向为下
           //不能直接改变为向上）
{
    char c;
    if (_kbhit())
    {
        c = _getch();
        switch (c)
        {
        case'W':case'w': {if (dir2 != down2) dir2 = up2; break; }
        case'S':case's': {if (dir2 != up2) dir2 = down2; break; }
        case'A':case'a': {if (dir2 != right2) dir2 = left2; break; }
        case'D':case'd': {if (dir2 != left2) dir2 = right2; break; }
        }

    }
}
void food2()
{
    int color;
    static int r = 1;
    if (player.x[0] == player.food_x && player.y[0] == player.food_y)//当蛇头吃掉食物时，刷新食物坐标
    {
        player.lenth++;
        player.food_x = rand() % (side - 1) + 1;
        player.food_y = rand() % (side - 1) + 1;
    }
    if (player.x[0] == player.special_x && player.y[0] == player.special_y)
    {//蛇头与特殊食物相碰时，蛇长度加一，改变屏幕颜色和让特殊食物暂时在屏幕消失
        player.lenth++;
        creat = 0;
        player.special_x = -150;
        player.special_y = -150;
        color = rand() % 10;
        switch (color)
        {
        case 0:system("color 0"); break;
        case 1:system("color 1"); break;
        case 2:system("color 2"); break;
        case 3:system("color 3"); break;
        case 4:system("color 4"); break;
        case 5:system("color 5"); break;
        case 6:system("color 6"); break;
        case 7:system("color 7"); break;
        case 8:system("color 8"); break;
        case 9:system("color 9"); break;
        }
    }
    if (player.lenth % 5 != 0 && creat == 0) creat = 1;
    if (player.lenth % 5 == 0 && creat == 1)
    {
        player.obstacle_x[r] = rand() % (side - 1) + 1;//增加新障碍
        player.obstacle_y[r] = rand() % (side - 1) + 1;
        player.special_x = rand() % (side - 1) + 1;//蛇长度达到每次5的整数倍后，出现特殊食物
        player.special_y = rand() % (side - 1) + 1;
        r++;
        creat = 0;
    }

}
void decide2()//判读游戏是否结束
{
    for (k2 = 1; k2 < player.lenth; k2++)//判断蛇头是否与身体相碰
    {

        if (player.x[0] == player.x[k2] && player.y[0] == player.y[k2])
            judge2 = 0;//蛇头与身体相碰，游戏结束
    }
    for (k2 = 0; k2 < Max; k2++)
    {
        if (player.x[0] == player.obstacle_x[k2] && player.y[0] == player.obstacle_y[k2]) judge2 = 0;
    }


}
void help2()
{
    printf("                          这是无尽模式\n     ");
    printf("                 当蛇与栅栏相碰时,会从栅栏另一端出现\n");
    printf("                       吃到?可以增加蛇的长度\n  ");
    printf(" 每当长度达到5的整数倍时，会出现一个☆和障碍物(|或者—),且蛇的速度会变快\n     ");
    printf("                 吃到☆可以增加长度和改变屏幕颜色\n");
    printf("                  吃到☆后，☆会在附近留下残影，残影无任意作用，只供观赏\n");
    printf("                 当蛇的长度达到%d时，无尽模式通关\n",Max);
    printf("              当蛇头于身体或者障碍物相碰时，游戏结束\n");
    system("pause");
    system("cls");
    
}
void main2()
{
    HideCursor();
    initgame2();
    help2();
    while (judge2)
    {
        show2();
        move2();
        food2();
        decide2();
        automatic2();
    }
    gotoxy(player.x[player.lenth - 1], player.y[player.lenth - 1]);
    printf("O");
    gotoxy(2 * side, side / 2);
    if (player.lenth >= 20) printf("恭喜！您的成绩为%d分", player.lenth);
    else printf("很遗憾，您的成绩为%d！", player.lenth);
    gotoxy(0, side + 1);
    Sleep(1000);
}