#ifndef BASE_TEST_DRAW_H
#define BASE_TEST_DRAW_H

typedef struct Player{
    // only 1 & 2
    int player_name;

    // 0~100 convert to percentage
    int hp;

    // skills[n][0]: the serial number of skill
    // skills[n][1]: the number of skill the player owns
    int skills[][2];
} Player;

typedef struct Info_Move{
    int name;

    // provide the start and destination information
    int x_start, y_start;
    int x_dest, y_dest;
}Info_Move;

typedef struct Info_Attack{
    int name;

    //the effect area
    int x, y;
}Info_Attack;

void renew_backgrounds(int arr[][3], int length);
void renew_status(Player players[2]);

void move_object(Info_Move info);
void attack_object(Info_Attack info);

#endif //BASE_TEST_DRAW_H
