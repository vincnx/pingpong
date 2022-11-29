#include <stdio.h>
#include <conio.h>
#include <windows.h>

typedef struct Base{
    int x;
    int y;
    int len;
    int y_mov;
    int num;
    int point;
    char k_up;
    char k_dwn;
} Base;
typedef struct Ball{
    int x;
    int y;
    int x_mov;
    int y_mov;
} Ball;

int setup();
void draw_map();
void draw_base();
void draw_ball();
void move_base();
void move_ball();
void gotoxy();

int main(){
    int cond;
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
    ball.x_mov = 0;
    ball.y_mov = 0;
    cond = setup(25, 75, 2, 0, &player, &ball);
    
}

int setup(int map_h, int map_w, int total_player, int play_ball, Base *players, Ball *ball){
    int i, key;
    int game_over = 0; int start = 0;
    while (!game_over){
        system("cls");
        draw_map(map_h, map_w);
        draw_ball(ball);
        if (kbhit()){
            key = getch();
        }
        if (key == 32){
            start = 1;
        }
        for (i = 0; i < total_player; i++){
            draw_base(&players[i]);
            move_base(&players[i], key);
            // ball hit base
            if (abs(ball->x - players[i].x) == 1){
                if (ball->y == players[i].y + players[i].len / 2){
                    ball->x_mov *= -1;
                    ball->y_mov = 0;
                }
                else if (ball->y >= players[i].y && ball->y < players[i].y + players[i].len /2){
                    ball->x_mov *= -1;
                    ball->y_mov = -1;
                }
                else if (ball->y < players[i].y + players[i].len){
                    ball->x_mov *= -1;
                    ball->y_mov = 1;
                }
            }
            // end of ball hit base
        }
        if (ball->x == 2){
            Sleep(1500);
            return 0;
        }
        else if (ball->x == 74){
            Sleep(1500);
            return 1;
        }

        // ball mov
        if (ball->y == 2 || ball->y == 24){
            ball->y_mov *= -1;
        }
        else if (start && ball->x_mov == 0){
            ball->x_mov = 1 + 2 * play_ball;
            ball->y_mov = players[play_ball].y_mov;
        }
        else if (!start){
            ball->y_mov = players[play_ball].y_mov;
        }
        ball->x += ball->x_mov;
        ball->y += ball->y_mov;
        // end of ball mov

        gotoxy(80, 12);
        printf("%i %i", ball->x, players[1].x);

    }
}

void move_base(Base *players, int key){
    if (players->y == 2 || players->y == 20)
    {
        players->y_mov = 0;
    }
    if (key == players->k_up && players->y != 2)
    {
        players->y_mov = -1;
    }
    else if (key == players->k_dwn && players->y != 20)
    {
        players->y_mov = 1;
    }
    players->y += players->y_mov;
}

void draw_ball(Ball *ball){
    gotoxy(ball->x, ball->y);
    printf("*");
}

void draw_base(Base *player){
    int i;
    for (i = 0; i < player->len; i++)
    {
        gotoxy(player->x, player->y + i);
        printf("|");
    }
}

void draw_map(int map_h, int map_w){
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

void gotoxy(int x, int y){
    COORD coor;
    coor.X = x;
    coor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}