#pragma once

struct ProcessorApi;
typedef struct ProcessorApi ProcessorApi;

struct Processor;
typedef struct Processor Processor;

struct ProcessorAnimeData;
typedef struct ProcessorAnimeData ProcessorAnimeData;

#include "base.h"
#include "object.h"
#include "macros.h"
#include "../draw/draw.h"



struct Processor{
    Base *base;
    ProcessorApi *api;
    ProcessorAnimeData *anime_cache;

    Object* (*place_object)(Processor *self, Object* object, int x, int y);
    void (*step)(Processor *self);
    ProcessorAnimeData (*export_anime_data)(Processor *self);
};


struct ProcessorApi{
    void (*request_move)(Processor *host, int direction, int step, Object* source);
    void (*request_teleport)(Processor *host, int des_x, int des_y, Object* source);
    void (*request_freeze)(Processor *host, Object* target, int degree, Object* source);
    void (*request_burn)(Processor *host, Object* target, int degree, Object* source);
    void (*request_defend)(Processor *host, Object* target, int degree, Object* source);
    void (*request_weak)(Processor *host, Object* target, int degree, Object* source);
    void (*request_heal)(Processor *host, Object* target, int heal, Object* source);
    void (*request_hurt)(Processor *host, Object* target, int damage, Object* source);

    Object* (*detect_exist_object)(Processor *host, int x1, int y1, int x2, int y2);
    Object* (*get_object)(Processor *host, int x, int y);
    Object* (*find_closest_object_in_direction)(Processor *host, int x, int y, int direction);
    Object* (*find_closest_object)(Processor *host, int x, int y);
};

struct ProcessorAnimeData{
    Player player1;
    Player player2;

    InfoMove* info_move;
    int info_move_length;

    InfoEffect* info_effect;
    int info_effect_length;
};

// init the processor
Processor* init_processor();

// destroy the processor
void destroy_processor(Processor *self);

// place an object at this place
// return ptr to the object if success, return NULL if failed 
Object* place_object(Processor *self, Object* object, int x, int y, int length, int height);

// step the processor
void step(Processor *self);

// export the anime data
ProcessorAnimeData export_anime_data(Processor *self);

// below are provided to the objects
// objects could only use these functions to interact with the processor or other objects

// request to move the object
void request_move(Processor *host, int direction, int step, Object* source);

// request to teleport the object
void request_teleport(Processor *host, int des_x, int des_y, Object* source);

// request to freeze the object
// freeze: the object will not "action"
// degree-- for each step
void request_freeze(Processor *host, Object* target, int degree, Object* source);

// request to burn the object
// burn: the object will lose hp, hp -= 1
// degree-- for each step
void request_burn(Processor *host, Object* target, int degree, Object* source);

// request to defend the object
// defend: hurt will be reduced by degree
void request_defend(Processor *host, Object* target, int degree, Object* source);

// request to weaken the object
// weaken: hurt will be increased by degree
void request_weak(Processor *host, Object* target, int degree, Object* source);

// request to heal the object
void request_heal(Processor *host, Object* target, int heal, Object* source);

// request to hurt the object
void request_hurt(Processor *host, Object* target, int damage, Object* source);

// detect if there is an object in the area
// return the object if there is, return NULL if not
// range [x1, x2), [y1, y2)
Object* detect_exist_object(Processor *host, int x1, int y1, int x2, int y2);

// get the object at this place
// return the object if there is, return NULL if not
Object* get_object(Processor *host, int x, int y);

// find the closest object in the direction
// return the closest if there is, return NULL if not
Object* find_closest_object_in_direction(Processor *host, int x, int y, int direction);

// find the closest object
// return the closest if there is, return NULL if not
Object* find_closest_object(Processor *host, int x, int y);
