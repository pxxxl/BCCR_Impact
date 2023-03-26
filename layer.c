//
// Created by cozard on 23-3-26.
//

#include "lw_oopc.h"
#include "object.h"
#include "layer.h"

#define BOUND_TEST(x, y) \
    do {                 \
        if(x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) \
        return NULL;     \
        }while(0)

#define NULLPTR_TEST(self) \
    do {                 \
        if(self == NULL) \
        return NULL;     \
        }while(0)


Object* get_object(Layer *self, int x, int y){
    BOUND_TEST(x, y);
    return self->layer[y][x];
}

Object* set_object(Layer *self, int x, int y, Object *object){
    BOUND_TEST(x, y);
    if (self->layer[y][x] == NULL){
        self->layer[y][x] = object;
        object->x = x;
        object->y = y;
        return object;
    }else {
        return NULL;
    }
}

Object* del_object(Layer *self, Object* object){
    NULLPTR_TEST(object);
    BOUND_TEST(object->x, object->y);
    self->layer[object->y][object->x] = NULL;
    object->x = -1;
    object->y = -1;
    return object;
}

Object* up_step_object(Layer *self, Object* object){
    NULLPTR_TEST(object);
    BOUND_TEST(object->x, object->y);
    Object* target = get_object(self, object->x, object->y-1);
    if(target != NULL){
        return NULL;
    }else{
        set_object(self, object->x, object->y-1, object);
        del_object(self, object->x, object->y);
        object->y -= 1;
        return object;
    }
}

Object* left_step_object(Layer *self, Object* object){
    NULLPTR_TEST(object);
    BOUND_TEST(object->x, object->y);
    Object* target = get_object(self, object->x-1, object->y);
    if(target != NULL){
        return NULL;
    }else{
        set_object(self, object->x-1, object->y, object);
        del_object(self, object->x, object->y);
        object->x -= 1;
        return object;
    }
}

Object* right_step_object(Layer *self, Object* object){
    NULLPTR_TEST(object);
    BOUND_TEST(object->x, object->y);
    Object* target = get_object(self, object->x+1, object->y);
    if(target != NULL){
        return NULL;
    }else{
        set_object(self, object->x+1, object->y, object);
        del_object(self, object->x, object->y);
        object->x += 1;
        return object;
    }
}

Object* down_step_object(Layer *self, Object* object){
    NULLPTR_TEST(object);
    BOUND_TEST(object->x, object->y);
    Object* target = get_object(self, object->x, object->y+1);
    if(target != NULL){
        return NULL;
    }else{
        set_object(self, object->x, object->y+1, object);
        del_object(self, object->x, object->y);
        object->y += 1;
        return object;
    }
}

Object* teleport_object(Layer *self, int x, int y, Object *object){
    BOUND_TEST(x, y);
    Object* target = get_object(self, x, y);
    if(object == NULL || target != NULL){
        return NULL;
    }else{
        set_object(self, x, y, object);
        del_object(self, object->x, object->y);
        object->x = x;
        object->y = y;
        return object;
    }
}

Object* detect_direct_path(Layer *self, Object* object, int step, int direction){
    BOUND_TEST(x1, y1);
    BOUND_TEST(x2, y2);
    int cur_x = x1;
    int cur_y = y1;
    int dir_x = x2 - x1 > 0 ? 1 : -1;
    int dir_y = y2 - y1 > 0 ? 1 : -1;
}

Object* move_object(Layer* self, Object* object, int step, int direction){

}

Object* up_move_object(Layer *self, Object* object, int step){
    BOUND_TEST(object->x,object->y);
    if(step <= 0){
        return NULL;
    }
    int count = 0;
    Object* target = object;
    Object* signal = NULL;
    for(count = 0; count < step; count++){
        signal = up_step_object(self, target);
        if(signal == NULL){
            break;
        }
    }
    if(signal == NULL){
        for(; count >= 0; count--){
            down_step_object(self, target);
        }
    }
}

Object* left_move_object(Layer *self, int x, int y, int step);
Object* right_move_object(Layer *self, int x, int y, int step);
Object* down_move_object(Layer *self, int x, int y, int step);

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