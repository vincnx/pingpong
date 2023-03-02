#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// struct & global var
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

int play = 0;
int ball_p = 0;
int hit_x = 0;
// end struct & global var

void _2p();
void _1p();

int menu();
void move_player();
void move_ball();
void hit_base();
void res_val();
int add_score();
void draw_map();
void draw_ball();
void draw_player();

// tools
void delay();
void gotoxy();
void panah();
void hati();
// end tools
void metu();


int main(){
    system("COLOR 6F");
    int pil_menu_utama;
    pil_menu_utama = menu();
    switch (pil_menu_utama){
        case 1:
            _1p();
            system("pause");
            main();
            break;
        case 2:
            _2p();
            system("pause");
            main();
            break;
        case 3:
            metu();
            system("pause");
            break;
    }
}

int menu(){
    int posisi = 1;
    int keyPressed = 0;
    while (keyPressed != 27){
        system("cls");
        gotoxy(60, 5);
        printf("========================");
        gotoxy(60, 6);
        printf("     Ping Pong Game");
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
        if (keyPressed == 72){
            posisi--;
        }
        else if (keyPressed == 80){
            posisi++;
        }
        else if (keyPressed == 13){
            return posisi;
        }
        if (posisi < 1){
            posisi = 3;
        }
        else if (posisi > 3){
            posisi = 1;
        }
    }
}

void _1p(){
    int i, j, key;
    Base player[2];
    Ball ball;
    player[0].x = 6;
    player[0].y = 11;
    player[0].k_up = 'w';
    player[0].k_dwn = 's';
    player[1].x = 70;
    player[1].y = 11;
    for (i = 0; i < 2; i++){
        player[i].len = 5;
        player[i].y_mov = 0;
        player[i].num = i;
        player[i].point = 0;
    }
    ball.x = 7;
    ball.y = 13;
    while (player[0].point + player[1].point != 5){
    start:
        system("cls");
        draw_map(25, 75);
        draw_ball(ball);
        if (kbhit()){
            key = getch();
        }
        for (i = 0; i < 2; i++){
            draw_player(player[i]);
            if (add_score(&player[i], ball)){
                key = '\0';
                res_val(&ball);
                for (j = 0; j < 2; j++){
                    player[j].y = 11;
                    player[j].y_mov = 0;
                }
                goto start;
            }
            if (play){
                hit_base(&ball, player[i]);
            }
            move_player(&player[i], key, i);
        }
        move_ball(&ball, player[ball_p], key, play);
        if (key == 32){
            play = 1;
        }
        delay();
    }
}

void _2p(){
    int i, j, key;
    Base player[2];
    Ball ball;
    player[0].x = 6;
    player[0].y = 11;
    player[0].k_up = 'w';
    player[0].k_dwn = 's';
    player[1].x = 70;
    player[1].y = 11;
    player[1].k_up = 'i';
    player[1].k_dwn = 'k';
    for (i = 0; i < 2; i++){
        player[i].len = 5;
        player[i].y_mov = 0;
        player[i].num = i;
        player[i].point = 0;
    }
    ball.x = 7;
    ball.y = 13;

    while (player[0].point + player[1].point != 5){
    start:
        system("cls");
        draw_map(25, 75);
        draw_ball(ball);
        if (kbhit()){
            key = getch();
        }
        for (i = 0; i < 2; i++)
        {
            draw_player(player[i]);
            if (add_score(&player[i], ball)){
                key = '\0';
                res_val(&ball);
                for (j = 0; j < 2; j++){
                    player[j].y = 11;
                    player[j].y_mov = 0;
                }
                goto start;
            }
            if (play){
                hit_base(&ball, player[i]);
            }
            move_player(&player[i], key, 0);
        }
        move_ball(&ball, player[ball_p], key, play);
        if (key == 32){
            play = 1;
        }
        delay();
    }
}

void metu(){
    system("cls");
    gotoxy(60, 4);
    printf("Vincent Exelcio Susanto (672022070)");
    gotoxy(60, 5);
    printf("Hosea Raka Narwastudjati (672022160)");
    gotoxy(60, 6);
    printf("Fryan Gerardi Parantak (672022116)\n");
    hati(7, 70, 8);
    gotoxy(66, 20);
    printf("tidak perlu mencatat");
    Sleep(7000);
    exit(0);
}

int add_score(Base *player, Ball ball){
    if (ball.x == 2 && player->num == 1){
        player->point++;
        play = 0;
        hit_x = 1;
        ball_p = 0;
    }
    else if (ball.x == 74 && player->num == 0){
        player->point++;
        play = 0;
        hit_x = 1;
        ball_p = 1;
    }
    return hit_x;
}

void res_val(Ball *ball){
    ball->x_mov = 0;
    ball->y_mov = 0;
    if (ball->x == 2){
        ball->x = 7;
        ball->y = 13;
        hit_x = 0;
    }
    else{
        ball->x = 69;
        ball->y = 13;
        hit_x = 0;
    }
}

void hit_base(Ball *ball, Base player){
    if (abs(player.x - ball->x) == 1 && player.y <= ball->y && ball->y < player.y + player.len){
        if (ball->y < player.y + player.len / 2){
            ball->y_mov = -1;
            ball->x_mov *= -1;
        }
        else if (ball->y == player.y + player.len / 2){
            ball->y_mov = 0;
            ball->x_mov *= -1;
        }
        else{
            ball->y_mov = 1;
            ball->x_mov *= -1;
        }
    }
}

void move_ball(Ball *ball, Base player, int key, int play){
    if (play){
        if (ball->y == 2 || ball->y == 24){
            ball->y_mov *= -1;
            ball->y = ball->y + ball->y_mov;
        }
    }
    else{
        if (abs(player.x - ball->x) == 1){
            ball->y_mov = player.y_mov;
            if (key == 32){
                ball->x_mov = 1 - (2 * player.num);
            }
            else{
                ball->x_mov = 0;
            }
        }
    }
    ball->x += ball->x_mov;
    ball->y += ball->y_mov;
}

void move_player(Base *player, int key, int num_player){
    if (num_player == 1 && player->y_mov == 0){
        player->y_mov = -1;
    }
    else{
        if (key == player->k_up){
            player->y_mov = -1;
        }
        else if (key == player->k_dwn){
            player->y_mov = 1;
        }
    }
    if (player->y == 2 && player->y_mov == -1){
        player->y_mov = 0;
        if (num_player == 1){
            player->y_mov = 1;
        }
    }
    else if (player->y == 25 - player->len && player->y_mov == 1){
        player->y_mov = 0;
        if (num_player == 1){
            player->y_mov = -1;
        }
    }
    player->y += player->y_mov;
}

void draw_map(int map_h, int map_w){
    int i, j;
    for (i = 1; i <= map_h; i++){
        for (j = 1; j <= map_w; j++){
            if (i == 1 || i == map_h || j == 1 || j == map_w / 2 + 1 || j == map_w){
                gotoxy(j, i);
                printf("#");
            }
        }
    }
}

void draw_ball(Ball ball){
    gotoxy(ball.x, ball.y);
    printf("*");
}

void draw_player(Base player){
    int i;
    for (i = 0; i < player.len; i++){
        gotoxy(player.x, player.y + i);
        printf("|");
    }
    gotoxy(80, 12);
    printf("score :");
    gotoxy(80, 13 + player.num);
    printf("player %i : %i", player.num, player.point);
}

// tools
void delay(){
    int i, j;
    for (i = 0; i < 1000; i++){
        for (j = 0; j < 7000; j++);
    }
}

void gotoxy(int x, int y){
    COORD coor;
    coor.X = x;
    coor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}

void panah(int posisiMenu, int posisiPanah){
    if (posisiPanah == posisiMenu){
        printf("==> ");
    }
    else{
        printf("    ");
    }
}

void hati(int n, int x_idx, int y_idx){
    int i, j;
    int k;
    for (i = n / 2; i <= n; i += 2){
        gotoxy(x_idx, y_idx + k);
        for (j = 1; j < n - i; j += 2){
            printf(" ");
        }
        for (j = 1; j <= i; j++){
            printf("%c", 3);
        }
        for (j = 1; j <= n - i; j++){
            printf(" ");
        }
        for (j = 1; j <= i; j++){
            printf("%c", 3);
        }
        k++;
    }
    for (i = n; i >= 1; i--){
        gotoxy(x_idx, y_idx + k);
        for (j = i; j < n; j++){
            printf(" ");
        }
        for (j = 1; j <= (i * 2) - 1; j++){
            printf("%c", 3);
        }
        k++;
    }
    gotoxy(x_idx, y_idx + k);
}
// end tools