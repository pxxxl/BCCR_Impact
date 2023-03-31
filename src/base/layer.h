#pragma once

#include "base.h"
#include "object.h"
#include "macros.h"

struct ProcessorApi;
typedef struct ProcessorApi ProcessorApi;


struct Processor;
typedef struct Processor Processor;
struct Processor{
    Processor *layer;
    ProcessorApi *api;

    Object* (*create_object_processor)(Processor *self, int x, int y);
    void (*step)(Processor *self);
    void (*export_anime_data)(Processor *self);
};


struct ProcessorApi{
    void (*request_move)(Processor *host, int direction, int step);
    void (*request_freeze)(Processor *host, Object* target);
    void (*request_burn)(Processor *host, Object* target);
    void (*request_defend)(Processor *host, Object* target, int degree);
    void (*request_weak)(Processor *host, Object* target, int degree);
    void (*request_heal)(Processor *host, Object* target, int heal);
    void (*request_hurt)(Processor *host, Object* target, int damage);

    Object* (*detect_exist_object)(Processor *host, int x1, int y1, int x2, int y2);
    Object* (*get_object)(Processor *host, int x, int y);
    Object* (*find_closest_object_in_direction)(Processor *host, int x, int y, int direction);
    Object* (*find_closest_object)(Processor *host, int x, int y);
};

Processor* init_processor();
void destroy_processor(Processor *self);

Object* create_object_processor(Processor *self, int x, int y);
void step(Processor *self);
void export_anime_data(Processor *self);

void request_move(Processor *host, int direction, int step);
void request_freeze(Processor *host, Object* target);
void request_burn(Processor *host, Object* target);
void request_defend(Processor *host, Object* target, int degree);
void request_weak(Processor *host, Object* target, int degree);
void request_heal(Processor *host, Object* target, int heal);
void request_hurt(Processor *host, Object* target, int damage);

Object* processor_detect_exist_object(Processor *host, int x1, int y1, int x2, int y2);
Object* processor_get_object(Processor *host, int x, int y);
Object* processor_find_closest_object_in_direction(Processor *host, int x, int y, int direction);
Object* processor_find_closest_object(Processor *host, int x, int y);

