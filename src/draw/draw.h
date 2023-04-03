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

typedef struct Info_Move{
    int name;

    // provide the start and destination information
    int x_start, y_start;
    int x_dest, y_dest;
}Info_Move;

typedef struct Info_Effect{
    int name;

    //the effect area
    int x, y;
}Info_Effect;


void renew_backgrounds(int **arr, int length);
void renew_status(Player players[2]);

void import_info(Info_Move *info_move, int *size_move, Info_Effect *info_effect, int *size_effect);
void refresh();