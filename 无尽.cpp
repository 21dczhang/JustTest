#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define side 25//������Ϸ��ͼ�߳�
#define Max 100//�����޾�ģʽ�ߵ���󳤶�
#define Speed2 70//�����ٶȣ�����ԽС���˶�Խ�죩
#define player player2
int i2, j2, k2, judge2 = 1, speed2 = 0, creat = 1;//judge����������Ϸ�Ƿ����
extern void gotoxy(int x, int y);
extern void HideCursor();
struct snake2//�����ߵĽṹ��
{
    int x[Max], y[Max];//x[0]��y[0]����ͷ���꣬����Ϊ����������
    int food_x, food_y;//ʳ������
    int lenth;//�ߵĳ���
    int obstacle_x[Max], obstacle_y[Max];//�ϰ�������
    int special_x = -1, special_y = 1;
}player2;
enum direction2//ö�����п��ܵķ���
{
    up2, down2, left2, right2
}dir2;
void initgame2()//��ʼ����Ϸ
{
    dir2 = up2;//�ߵĳ�ʼ��������
    player.lenth = 3;//�ߵĳ�ʼ����Ϊ3
    srand((unsigned)time(NULL));
    player.x[0] = side / 2;//��ʼ����ͷ������
    player.y[0] = side / 2;
    player.obstacle_x[0] = rand() % (side - 1) + 1;//��ʼ���ϰ�
    player.obstacle_y[0] = rand() % (side - 1) + 1;
    for (i2 = 1; i2 < player.lenth; i2++)//��ʼ������������
    {
        player.x[i2] = player.x[i2 - 1];
        player.y[i2] = player.y[i2 - 1] + 1;
    }
    //for (int i = 1; i < Max ; i++)//�����ϰ���ʱ����������Ļ
    //{
    //    player.obstacle_x[i] = -1;
    //    player.obstacle_y[i] = -1;
    //}
    player.food_x = rand() % (side - 1) + 1;//��ʼ��ʳ������
    player.food_y = rand() % (side - 1) + 1;
    player.special_x = -150;//����ʳ����ʱ������
    player.special_y = -150;
}
void automatic2()
{
    srand((unsigned)time(NULL));
    static int s2 = 0;
    static int t2 = 0;
    if (t2 < Speed2 - speed2) t2++;/*�����ж���ͷ�Ƿ��Ѿ��ж���������������ͼ��������
                             ���һ��*/
    else
    {
        t2 = 0;
        gotoxy(player.x[player.lenth - 1], player.y[player.lenth - 1]);
        printf(" ");
        if (judge2 != 0)//��Ϸ�����򽫵�i�ڵ����긳����i-1�ڣ��ﵽ�˶���Ŀ��
        {
            for (i2 = player.lenth - 1; i2 > 0; i2--)
            {
                player.x[i2] = player.x[i2 - 1];
                player.y[i2] = player.y[i2 - 1];
                while (player.food_x == player.x[i2] && player.food_y == player.y[i2] ||
                    player.food_x == player.obstacle_x[i2] && player.food_y == player.obstacle_y[i2] ||
                    player.food_x == player.special_x && player.food_y == player.special_y)
                {//���ʳ����������������������ϰ������������ʳ�������ص�����ˢ��ʳ������
                    player.food_x = rand() % (side - 1) + 1;
                    player.food_y = rand() % (side - 1) + 1;
                }
                while (player.special_x == player.x[i2] && player.special_y == player.y[i2] ||
                    player.special_x == player.obstacle_x[i2] && player.special_y == player.obstacle_y[i2])
                {//��automatic1��������������ʳ����ж�
                    player.special_x = rand() % (side - 1) + 1;
                    player.special_y = rand() % (side - 1) + 1;
                }

            }
            switch (player.lenth)//���ݳ��ȸı��ߵ��ٶ�
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
    //���ݵ�ǰ���������Լ�ǰ��
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
    printf("��ǰ����Ϊ%d", player.lenth);//�����ǰ����
}
void show2()
{
    for (k2 = 0; k2 <= side; k2++)//���դ��
    {
        gotoxy(k2, 0); printf("#");
        gotoxy(k2, side); printf("#");
    }
    for (k2 = 1; k2 <= side - 1; k2++)
    {
        gotoxy(0, k2); printf("#");
        gotoxy(side, k2); printf("#");
    }
    gotoxy(player.x[0], player.y[0]);//�����ͷ
    printf("X");
    for (k2 = 1; k2 < player.lenth; k2++)//�������
    {
        gotoxy(player.x[k2], player.y[k2]);
        printf("O");
    }
    gotoxy(player.food_x, player.food_y);//���ʳ��
    printf("?");
    for (k2 = 0; k2 < Max; k2++)//����ϰ���
    {
        if (k2 % 2 != 0)
        {
            gotoxy(player.obstacle_x[k2], player.obstacle_y[k2]);
            printf("|");
        }
        if (k2 % 2 == 0)
        {
            gotoxy(player.obstacle_x[k2], player.obstacle_y[k2]);
            printf("��");
        }
    }
    gotoxy(player.special_x, player.special_y);//�������ʳ��
    printf("��");
}
void move2()//�ɼ��������Ӧ�������ı��ߵķ��򣨲���ת��90�ȣ��緽��Ϊ��
           //����ֱ�Ӹı�Ϊ���ϣ�
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
    if (player.x[0] == player.food_x && player.y[0] == player.food_y)//����ͷ�Ե�ʳ��ʱ��ˢ��ʳ������
    {
        player.lenth++;
        player.food_x = rand() % (side - 1) + 1;
        player.food_y = rand() % (side - 1) + 1;
    }
    if (player.x[0] == player.special_x && player.y[0] == player.special_y)
    {//��ͷ������ʳ������ʱ���߳��ȼ�һ���ı���Ļ��ɫ��������ʳ����ʱ����Ļ��ʧ
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
        player.obstacle_x[r] = rand() % (side - 1) + 1;//�������ϰ�
        player.obstacle_y[r] = rand() % (side - 1) + 1;
        player.special_x = rand() % (side - 1) + 1;//�߳��ȴﵽÿ��5���������󣬳�������ʳ��
        player.special_y = rand() % (side - 1) + 1;
        r++;
        creat = 0;
    }

}
void decide2()//�ж���Ϸ�Ƿ����
{
    for (k2 = 1; k2 < player.lenth; k2++)//�ж���ͷ�Ƿ�����������
    {

        if (player.x[0] == player.x[k2] && player.y[0] == player.y[k2])
            judge2 = 0;//��ͷ��������������Ϸ����
    }
    for (k2 = 0; k2 < Max; k2++)
    {
        if (player.x[0] == player.obstacle_x[k2] && player.y[0] == player.obstacle_y[k2]) judge2 = 0;
    }


}
void help2()
{
    printf("                          �����޾�ģʽ\n     ");
    printf("                 ������դ������ʱ,���դ����һ�˳���\n");
    printf("                       �Ե�?���������ߵĳ���\n  ");
    printf(" ÿ�����ȴﵽ5��������ʱ�������һ������ϰ���(|���ߡ�),���ߵ��ٶȻ���\n     ");
    printf("                 �Ե���������ӳ��Ⱥ͸ı���Ļ��ɫ\n");
    printf("                  �Ե���󣬡���ڸ������²�Ӱ����Ӱ���������ã�ֻ������\n");
    printf("                 ���ߵĳ��ȴﵽ%dʱ���޾�ģʽͨ��\n",Max);
    printf("              ����ͷ����������ϰ�������ʱ����Ϸ����\n");
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
    if (player.lenth >= 20) printf("��ϲ�����ĳɼ�Ϊ%d��", player.lenth);
    else printf("���ź������ĳɼ�Ϊ%d��", player.lenth);
    gotoxy(0, side + 1);
    Sleep(1000);
}