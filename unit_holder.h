//
// Created by LENOVO on 2023/3/13.
//

#ifndef BCCR_IMPACT_UNIT_HOLDER_H
#define BCCR_IMPACT_UNIT_HOLDER_H

#include <stdbool.h>
#include "unit.h"

#define STANDARD_BOARD_LENGTH 400
#define STANDARD_BOARD_WIDTH 400

typedef struct {
    int x;
    int y;
} pos_t;

typedef struct {
    unit_p_t** data;
    int length;
    int width;


} unit_holder_t, *unit_holder_p_t;

err_t init_board(unit_p_t** board, int length, int width);
err_t land_unit(unit_holder_p_t board, unit_p_t unit, pos_t pos);
unit_p_t get_unit(unit_holder_p_t board, pos_t pos);
err_t del_unit(unit_holder_p_t board, pos_t pos);


bool can_move_to(unit_holder_p_t board, pos_t target);
err_t move_unit(unit_holder_p_t board, pos_t pos, pos_t target);
err_t up_move_unit(unit_holder_p_t board, pos_t pos, int step);
err_t left_move_unit(unit_holder_p_t board, pos_t pos, int step);
err_t right_move_unit(unit_holder_p_t board, pos_t pos, int step);
err_t down_move_unit(unit_holder_p_t board, pos_t pos, int step);


err_t get_blue_side_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_red_side_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_army_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_construction_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_magic_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_blue_side_army_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_blue_side_construction_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_blue_side_magic_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_red_side_army_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_red_side_construction_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_red_side_magic_unit(unit_holder_p_t board, unit_p_t* units, int* length);
err_t get_closest_enemy_army_unit(unit_holder_p_t board, pos_t pos, unit_side_t self_side, unit_p_t* unit);
err_t get_closest_enemy_construction_unit(unit_holder_p_t board, pos_t pos, unit_side_t self_side, unit_p_t* unit);
err_t get_closest_enemy_magic_unit(unit_holder_p_t board, pos_t pos, unit_side_t self_side, unit_p_t* unit);

#endif //BCCR_IMPACT_UNIT_HOLDER_H
