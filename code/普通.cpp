#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define side 25//������Ϸ��ͼ�߳�
#define max 20//�����ߵ���󳤶�
#define Speed1 70//�����ٶȣ�����ԽС���˶�Խ�죩
//#define player player1
int i1, j1, k1, judge1 = 1, speed1 = 0;//judge����������Ϸ�Ƿ����
void gotoxy(int x, int y);
void HideCursor();
struct snake1//�����ߵĽṹ��
{
    int x[max], y[max];//x[0]��y[0]����ͷ���꣬����Ϊ����������
    int food_x, food_y;//ʳ������
    int lenth;//�ߵĳ���
    int obstacle_x[max / 2], obstacle_y[max / 2];
    int special_x = -1, special_y = 1;
}player1;
enum direction1//ö�����п��ܵķ���
{
    up1, down1, left1, right1
}dir1;
void initgame1()//��ʼ����Ϸ
{
    dir1 = up1;//�ߵĳ�ʼ��������
    player1.lenth = 3;//�ߵĳ�ʼ����Ϊ3
    srand((unsigned)time(NULL));
    player1.x[0] = side / 2;//��ʼ����ͷ������
    player1.y[0] = side / 2;
    for (i1 = 1; i1 < player1.lenth; i1++)//��ʼ������������
    {
        player1.x[i1] = player1.x[i1 - 1];
        player1.y[i1] = player1.y[i1 - 1] + 1;

    }
    player1.food_x = rand() % (side - 1) + 1;//��ʼ��ʳ������
    player1.food_y = rand() % (side - 1) + 1;
}
void move1()//�ɼ��������Ӧ�������ı��ߵķ��򣨲���ת��90�ȣ��緽��Ϊ��
           //����ֱ�Ӹı�Ϊ���ϣ�
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
    if (t1 < Speed1 - speed1) t1++;/*�����ж���ͷ�Ƿ��Ѿ��ж���������������ͼ��������
                             ���һ��*/
    else
    {
        t1 = 0;
        gotoxy(player1.x[player1.lenth - 1], player1.y[player1.lenth - 1]);
        printf(" ");
        if (judge1 != 0)//��Ϸ�����򽫵�i�ڵ����긳����i-1�ڣ��ﵽ�˶���Ŀ��
        {
            for (i1 = player1.lenth - 1; i1 > 0; i1--)
            {
                player1.x[i1] = player1.x[i1 - 1];
                player1.y[i1] = player1.y[i1 - 1];
                while (player1.food_x == player1.x[i1] && player1.food_y == player1.y[i1])
                {//���ʳ�������������������ص�����ˢ��ʳ������
                    player1.food_x = rand() % (side - 1) + 1;
                    player1.food_y = rand() % (side - 1) + 1;
                }
            }
        }
        switch (player1.lenth)//���ݳ��ȸı��ߵ��ٶ�
        {
        case 5: speed1 = 15; break;
        case 10:speed1 = 25; break;
        case 15:speed1 = 35; break;
        case 20:judge1 = 0;  break;

        }
    }
    //���ݵ�ǰ���������Լ�ǰ��
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
    printf("��ǰ����Ϊ%d", player1.lenth);//�����ǰ����
}

void show1()
{
    for (k1 = 0; k1 <= side; k1++)//���դ��
    {
        gotoxy(k1, 0); printf("#");
        gotoxy(k1, side); printf("#");
    }
    for (k1 = 1; k1 <= side - 1; k1++)
    {
        gotoxy(0, k1); printf("#");
        gotoxy(side, k1); printf("#");
    }
    gotoxy(player1.x[0], player1.y[0]);//�����ͷ
    printf("X");
    for (k1 = 1; k1 < player1.lenth; k1++)//�������
    {
        gotoxy(player1.x[k1], player1.y[k1]);
        printf("O");
    }
    gotoxy(player1.food_x, player1.food_y);//���ʳ��
    printf("?");

}

void move()//�ɼ��������Ӧ�������ı��ߵķ��򣨲���ת��90�ȣ��緽��Ϊ��
           //����ֱ�Ӹı�Ϊ���ϣ�
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
void food1()//����ͷ�Ե�ʳ��ʱ��ˢ��ʳ������
{
    if (player1.x[0] == player1.food_x && player1.y[0] == player1.food_y)
    {
        player1.lenth++;
        player1.food_x = rand() % (side - 1) + 1;
        player1.food_y = rand() % (side - 1) + 1;
    }
}

void decide1()//�ж���Ϸ�Ƿ����
{
    if (player1.x[0] == 0 || player1.x[0] == side) judge1 = 0;//��ͷ��դ������������
    if (player1.y[0] == 0 || player1.y[0] == side) judge1 = 0;//��ͷ��դ������������
    for (k1 = 1; k1 < player1.lenth; k1++)//�ж���ͷ�Ƿ�����������
    {

        if (player1.x[0] == player1.x[k1] && player1.y[0] == player1.y[k1])
            judge1 = 0;//��ͷ��������������Ϸ����
    }
    switch (player1.lenth)//���ݳ��ȸı��ߵ��ٶ�
    {
    case 5: speed1 = 15; break;
    case 10:speed1 = 25; break;
    case 15:speed1 = 35; break;
    case 20:judge1 = 0;  break;

    }

}

void help1()//��Ϸ����ʾ
{
    
    printf("                          ������ͨģʽ\n     ");
    printf("                 ������դ��������������ʱ����Ϸ����\n");
    printf("                       �Ե�?���������ߵĳ���\n  ");
    printf("               �����ȷֱ�ﵽ5��10��15ʱ���ߵ��ٶȻ���\n");
    printf("                      �����ȴﵽ%dʱ����Ϸͨ�أ�\n", max);
    system("pause");
    system("cls");
}
void main1()//��ʼ��Ϸ
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
    if (player1.lenth >= 20) printf("��ϲ�����Ѿ�ͨ�أ�");
    else printf("���ź�����ʧ���ˣ�");
    gotoxy(0, side + 1);
    Sleep(800);
}
