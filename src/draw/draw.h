#pragma once

typedef struct Player{
    // only 1 & 2
    int player_name;

    // 0~100 convert to percentage
    int hp;

    // skills[n][0]: the serial number of skill
    // skills[n][1]: the number of skill the player owns
    int skill_num;
    int* skills;
} Player;

typedef struct InfoMove{
    int name;

    // provide the start and destination information
    int x_start, y_start;
    int x_dest, y_dest;
}InfoMove;

typedef struct InfoEffect{
    int name;

    //the effect area
    int x, y;
}InfoEffect;


void renew_backgrounds(int **arr, int length);
void renew_status(Player players[2]);

void import_info(InfoMove *info_move, int *size_move, InfoEffect *info_effect, int *size_effect);
void refresh();