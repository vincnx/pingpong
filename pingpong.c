#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

typedef struct Base
{
    int x;
    int y;
    int len;
    int y_mov;
    int num;
    int point;
    char k_up;
    char k_dwn;
} Base;

typedef struct Ball
{
    int x;
    int y;
    int x_mov;
    int y_mov;
} Ball;

void _2p();
void _1p();

int menu();
void panah();
void setup();
void draw_map();
void draw_base();
Base move_base();
void draw_ball();
Ball move_ball();
Ball hit_map();
Ball hit_base();
Base not_hit();
void draw_point();

void delay();
void gotoxy();

int play = 0;
int ball_p = 0;
int hit_x = 0;

int main()
{
    system("COLOR 6F");
    setup();
}

void _1p()
{
    int i, j, key;
    Base player[2];
    Ball ball;
    player[0].x = 6;
    player[0].y = 11;
    player[0].len = 5;
    player[0].y_mov = 0;
    player[0].num = 0;
    player[0].k_up = 'w';
    player[0].k_dwn = 's';
    player[0].point = 0;
    player[1].x = 70;
    player[1].y = 11;
    player[1].len = 5;
    player[1].y_mov = 0;
    player[1].num = 1;
    player[1].k_up = 'i';
    player[1].k_dwn = 'k';
    player[1].point = 0;
    ball.x = 7;
    ball.y = 13;

    while (player[0].point + player[1].point != 5)
    {
    a:
        system("cls");
        draw_map(25, 75);
        draw_ball(ball);
        if (kbhit())
        {
            key = getch();
        }
        for (i = 0; i < 2; i++)
        {
            draw_base(player[i]);
            draw_point(player[i]);
            player[i] = not_hit(player[i], ball);
            if (hit_x)
            {
                key = 'z';
                ball.x_mov = 0;
                ball.y_mov = 0;
                if (ball.x == 2)
                {
                    ball.x = 7;
                    ball.y = 13;
                    hit_x = 0;
                }
                else
                {
                    ball.x = 69;
                    ball.y = 13;
                    hit_x = 0;
                }
                for (j = 0; j < 2; j++)
                {
                    player[j].y = 11;
                    player[j].y_mov = 0;
                }
                goto a;
            }
            ball = hit_base(ball, player[i], play);
        }
        player[0] = move_base(player[0], key, 0);
        player[1] = move_base(player[1], key, 1);
        ball = hit_map(ball, play);
        ball = move_ball(ball, player[ball_p], key, play);
        if (key == 32)
        {
            play = 1;
        }
        delay();
    }
}

int menu()
{
    int posisi = 1;
    int keyPressed = 0;
    while (keyPressed != 27)
    {
        system("cls");

        gotoxy(60, 5);
        printf("========================");
        gotoxy(60, 6);
        printf("      Ping Pong Game");
        gotoxy(60, 7);
        printf("========================");

        gotoxy(60, 8);
        panah(1, posisi);
        printf("1. Single Player");
        gotoxy(60, 9);
        panah(2, posisi);
        printf("2. Multi Player");
        gotoxy(60, 10);
        panah(3, posisi);
        printf("3. Exit\n");
        gotoxy(60, 11);
        printf("========================");

        keyPressed = getch();

        if (keyPressed == 72)
        {
            posisi--;
        }
        else if (keyPressed == 80)
        {
            posisi++;
        }
        else if (keyPressed == 13)
        {
            return posisi;
        }
        if (posisi < 1)
        {
            posisi = 3;
        }
        else if (posisi > 3)
        {
            posisi = 1;
        }
        keyPressed = 'a';
        delay();
    }
}

void panah(int posisiMenu, int posisiPanah)
{
    if (posisiPanah == posisiMenu)
    {
        printf("==> ");
    }
    else
    {
        printf("    ");
    }
}

void setup()
{
    int pil_menu_utama;
    int pil_cetak;

    pil_menu_utama = menu();
    switch (pil_menu_utama)
    {
    case 1:
        _1p();
        system("pause");
        setup();
        break;
    case 2:
        _2p();
        system("pause");
        setup();
        break;
    case 3:
        metu();
        system("pause");
        break;
    }
}

void hati(int n, int x_idx, int y_idx)
{
    int i, j;
    int k;

    for (i = n / 2; i <= n; i += 2)
    {
        gotoxy(x_idx, y_idx + k);
        for (j = 1; j < n - i; j += 2)
        {
            printf(" ");
        }
        for (j = 1; j <= i; j++)
        {
            printf("%c", 3);
        }
        for (j = 1; j <= n - i; j++)
        {
            printf(" ");
        }
        for (j = 1; j <= i; j++)
        {
            printf("%c", 3);
        }
        k++;
    }

    for (i = n; i >= 1; i--)
    {
        gotoxy(x_idx, y_idx + k);
        for (j = i; j < n; j++)
        {
            printf(" ");
        }
        for (j = 1; j <= (i * 2) - 1; j++)
        {
            printf("%c", 3);
        }
        k++;
    }
    gotoxy(x_idx, y_idx + k);
}

void metu()
{
    system("cls");
    gotoxy(60, 4);
    printf("Vincent Exelcio Susanto (672022070)\n");
    gotoxy(60, 5);
    printf("Hosea Raka Narwastudjati (672022160)\n");
    gotoxy(60, 6);
    printf("Fryan Gerardi Parantak (672022116)\n");
    hati(7, 70, 8);
    gotoxy(66, 20);
    printf("tidak perlu mencatat");
    Sleep(7000);
    exit(0);
}

void _2p()
{
    int i, j, key;
    Base player[2];
    Ball ball;
    player[0].x = 6;
    player[0].y = 11;
    player[0].len = 5;
    player[0].y_mov = 0;
    player[0].num = 0;
    player[0].k_up = 'w';
    player[0].k_dwn = 's';
    player[0].point = 0;
    player[1].x = 70;
    player[1].y = 11;
    player[1].len = 5;
    player[1].y_mov = 0;
    player[1].num = 1;
    player[1].k_up = 'i';
    player[1].k_dwn = 'k';
    player[1].point = 0;
    ball.x = 7;
    ball.y = 13;

    while (player[0].point + player[1].point != 5)
    {
    a:
        system("cls");
        draw_map(25, 75);
        draw_ball(ball);
        if (kbhit())
        {
            key = getch();
        }
        for (i = 0; i < 2; i++)
        {
            draw_base(player[i]);
            draw_point(player[i]);
            player[i] = not_hit(player[i], ball);
            if (hit_x)
            {
                key = 'z';
                ball.x_mov = 0;
                ball.y_mov = 0;
                if (ball.x == 2)
                {
                    ball.x = 7;
                    ball.y = 13;
                    hit_x = 0;
                }
                else
                {
                    ball.x = 69;
                    ball.y = 13;
                    hit_x = 0;
                }
                for (j = 0; j < 2; j++)
                {
                    player[j].y = 11;
                    player[j].y_mov = 0;
                }
                goto a;
            }
            ball = hit_base(ball, player[i], play);
            player[i] = move_base(player[i], key, 0);
        }
        ball = hit_map(ball, play);
        ball = move_ball(ball, player[ball_p], key, play);
        if (key == 32)
        {
            play = 1;
        }
        delay();
    }
}

void draw_point(Base player)
{
    gotoxy(80, 12);
    printf("score :");
    gotoxy(80, 13 + player.num);
    printf("player %i : %i", player.num, player.point);
}

Base not_hit(Base player, Ball ball)
{
    Base temp;
    temp = player;
    if (ball.x == 2 && temp.num == 1)
    {
        temp.point++;
        play = 0;
        ball_p = 0;
        hit_x = 1;
    }
    else if (ball.x == 74 && temp.num == 0)
    {
        temp.point++;
        play = 0;
        ball_p = 1;
        hit_x = 1;
    }
    return temp;
}

Ball hit_base(Ball ball, Base player, int play)
{
    Ball temp;
    temp = ball;
    if (play)
    {
        if (abs(player.x - ball.x) == 1 && player.y <= ball.y && ball.y < player.y + player.len)
        {
            if (ball.y < player.y + player.len / 2)
            {
                temp.y_mov = -1;
                temp.x_mov *= -1;
            }
            else if (ball.y == player.y + player.len / 2)
            {
                temp.y_mov = 0;
                temp.x_mov *= -1;
            }
            else
            {
                temp.y_mov = 1;
                temp.x_mov *= -1;
            }
            return temp;
        }
    }
}

Ball hit_map(Ball ball, int play)
{
    Ball temp;
    int i;
    temp = ball;
    if (play)
    {
        if (temp.y == 2 || temp.y == 24)
        {
            temp.y_mov *= -1;
            temp.y = ball.y + temp.y_mov;
        }
    }
    return temp;
}

Ball move_ball(Ball ball, Base player, int key, int play)
{
    Ball temp;
    temp = ball;
    if (!play)
    {
        if (abs(player.x - temp.x) == 1)
        {
            if (key == 32)
            {
                temp.y_mov = player.y_mov;
                temp.x_mov = 1 - (2 * player.num);
            }
            else
            {
                temp.x_mov = 0;
                temp.y_mov = player.y_mov;
            }
        }
    }
    temp.x += temp.x_mov;
    temp.y += temp.y_mov;
    return temp;
}

void draw_ball(Ball ball)
{
    gotoxy(ball.x, ball.y);
    printf("*");
}

Base move_base(Base player, int key, int num_player)
{
    Base tmp;
    tmp = player;
    if (num_player == 1 && tmp.y_mov == 0)
    {
        tmp.y_mov = -1;
    }
    else if (num_player == 0)
    {
        if (key == tmp.k_up)
        {
            tmp.y_mov = -1;
        }
        else if (key == tmp.k_dwn)
        {
            tmp.y_mov = 1;
        }
    }
    if (tmp.y == 2 && tmp.y_mov == -1)
    {
        tmp.y_mov = 0;
        if (num_player == 1)
        {
            tmp.y_mov = 1;
        }
    }
    else if (tmp.y == 25 - tmp.len && tmp.y_mov == 1)
    {
        tmp.y_mov = 0;
        if (num_player == 1)
        {
            tmp.y_mov = -1;
        }
    }
    tmp.y += tmp.y_mov;
    return tmp;
}

void draw_base(Base player)
{
    int i;
    for (i = 0; i < player.len; i++)
    {
        gotoxy(player.x, player.y + i);
        printf("|");
    }
}

void draw_map(int map_h, int map_w)
{
    int i, j;
    for (i = 1; i <= map_h; i++)
    {
        for (j = 1; j <= map_w; j++)
        {
            if (i == 1 || i == map_h || j == 1 || j == map_w / 2 + 1 || j == map_w)
            {
                gotoxy(j, i);
                printf("#");
            }
        }
    }
}

void delay()
{
    int i, j;
    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 7000; j++)
            ;
    }
}

void gotoxy(int x, int y)
{
    COORD coor;
    coor.X = x;
    coor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}
