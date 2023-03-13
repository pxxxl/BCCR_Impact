//
// Created by Cozard on 2023/3/13.
//

/* The characters(units) in this game should use function in this header to manage.
 * Notes:
 * 1. Always hold unit_p_t as an unit. Use macros to decide its type and use SPECIFY to cast its right type
 * 2. After SPECIFY, you can use macros to get its info, and you can also use -> to get its info.
 * 3. NEVER USE Delete_Unit to delete a unit after you place it on a board.
 *
 *
 *
 *
 * */

#ifndef BCCR_IMPACT_UNIT_H
#define BCCR_IMPACT_UNIT_H

#include <assert.h>

typedef void* unit_p_t;
typedef void* func_t;

typedef int err_t;

typedef long long unit_id_t;
typedef char unit_side_t;
typedef char unit_type_t;

#define BLUE_SIDE 1
#define RED_SIDE 2

#define ARMY_TYPE 1
#define CONSTRUCTION_TYPE 2
#define MAGIC_TYPE 3


typedef struct {
    const unit_id_t id;
    const unit_side_t side;
    const unit_type_t type;
    const int speed;
    const int dps;
    const int range;
    const int interval;

    func_t attack_func;
    func_t move_func;
    func_t affect_func;
} unit_info_t, *unit_info_p_t;

typedef struct {
    unit_info_t info;
    int offset;
} abc_unit_t, *abc_unit_p_t;

typedef struct {
    unit_info_t info;
    int hp;
} army_t, *army_p_t;

typedef struct {
    unit_info_t info;
    int trigger_time_left;
} magic_t, *magic_p_t;

typedef struct {
    unit_info_t info;
    int hp;
} construction_t, *construction_p_t;

unit_p_t init_army(unit_side_t side, int hp, int speed, int dps, int range, int interval, func_t attack_func, func_t move_func);
unit_p_t init_magic(unit_side_t side, int dps, int range, int interval, func_t affect_func);
unit_p_t init_construction(unit_side_t side, int hp, int dps, int range, int interval, func_t attack_func);

err_t delete_unit(unit_p_t unit);

#define UNIT_TO_ABC(unit) ((abc_unit_p_t)unit)

#define UNIT_SIDE(unit) (UNIT_TO_ABC(unit)->info.side)
#define UNIT_TYPE(unit) (UNIT_TO_ABC(unit)->info.type)
#define UNIT_DPS(unit) (UNIT_TO_ABC(unit)->info.dps)
#define UNIT_RANGE(unit) (UNIT_TO_ABC(unit)->info.range)
#define UNIT_INTERVAL(unit) (UNIT_TO_ABC(unit)->info.interval)
#define UNIT_ID(unit) (UNIT_TO_ABC(unit)->info.id)
#define UNIT_SPEED(unit) (UNIT_TO_ABC(unit)->info.speed)
#define UNIT_ATTACK_FUNC(unit) (UNIT_TO_ABC(unit)->info.attack_func)
#define UNIT_MOVE_FUNC(unit) (UNIT_TO_ABC(unit)->info.move_func)
#define UNIT_AFFECT_FUNC(unit) (UNIT_TO_ABC(unit)->info.affect_func)

#define UNIT_IS_ARMY(unit) (UNIT_TYPE(unit) == ARMY_TYPE)
#define UNIT_IS_CONSTRUCTION(unit) (UNIT_TYPE(unit) == CONSTRUCTION_TYPE)
#define UNIT_IS_MAGIC(unit) (UNIT_TYPE(unit) == MAGIC_TYPE)
#define SPECIFY(unit, type) ((type##_p_t)unit)

#define UNIT_HP(unit) (UNIT_IS_MAGIC(unit) ? -1 : (SPECIFY(unit)->hp))
#define UNIT_TRIGGER_TIME_LEFT(unit) (UNIT_IS_MAGIC(unit) ? (SPECIFY(unit)->trigger_time_left) : -1)



#endif //BCCR_IMPACT_UNIT_H
