//
// Created by cozard on 23-3-26.
//

/*
 * Physical Layer
 * Abstract objects: Only contains position information
 * Constrains: Not allow overlap
 */

#ifndef BCCR_IMPACT_LAYER_H
#define BCCR_IMPACT_LAYER_H

#include "lw_oopc.h"
#include "object.h"

#define MAX_X 20
#define MAX_Y 40
#define DIRECTION_UP 1
#define DIRECTION_LEFT 2
#define DIRECTION_RIGHT 3
#define DIRECTION_DOWN 4

CLASS(Layer)
{
    Object *layer[MAX_Y][MAX_X];

    Object* (*get_object)(Layer *self, int x, int y);
    Object* (*set_object)(Layer *self, int x, int y, Object *object);
    Object* (*del_object)(Layer *self, int x, int y);
    Object* (*up_step_object)(Layer *self, int x, int y);
    Object* (*left_step_object)(Layer *self, int x, int y);
    Object* (*right_step_object)(Layer *self, int x, int y);
    Object* (*down_step_object)(Layer *self, int x, int y);
    Object* (*up_move_object)(Layer *self, int x, int y, int step);
    Object* (*left_move_object)(Layer *self, int x, int y, int step);
    Object* (*right_move_object)(Layer *self, int x, int y, int step);
    Object* (*down_move_object)(Layer *self, int x, int y, int step);
    Object* (*teleport_object)(Layer *self, int x, int y, Object *object);
    Object* (*find_closest_object)(Layer *self, int x, int y, obj_type_t type);
    Object* (*find_front_object)(Layer *self, int x, int y, obj_type_t type);
};

Object* get_object(Layer *self, int x, int y);
Object* set_object(Layer *self, int x, int y, Object *object);
Object* del_object(Layer *self, int x, int y);
Object* up_step_object(Layer *self, int x, int y);
Object* left_step_object(Layer *self, int x, int y);
Object* right_step_object(Layer *self, int x, int y);
Object* down_step_object(Layer *self, int x, int y);
Object* up_move_object(Layer *self, int x, int y, int step);
Object* left_move_object(Layer *self, int x, int y, int step);
Object* right_move_object(Layer *self, int x, int y, int step);
Object* down_move_object(Layer *self, int x, int y, int step);
Object* teleport_object(Layer *self, int x, int y, Object *object);
Object* find_closest_object(Layer *self, int x, int y, obj_type_t type);
Object* find_front_object(Layer *self, int x, int y, obj_type_t type);

Object* hurt_object(Object *self, int damage);
Object* heal_object(Object *self, int heal);
Object* freeze_object(Object *self);
Object* burn_object(Object *self);
Object* defend_object(Object *self);
Object* weaken_object(Object *self);
Object* de_freeze_object(Object *self);
Object* de_burn_object(Object *self);
Object* de_defend_object(Object *self);
Object* de_weaken_object(Object *self);
#endif //BCCR_IMPACT_LAYER_H
