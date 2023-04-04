#pragma once
#include "layer.h"
#include "base.h"

/*
struct ProcessorApi{
    void (*request_move)(Processor *host, int direction, int step);
    void (*request_teleport)(Processor *host, int des_x, int des_y, Object* object);
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
*/

// init the processor
Processor* init_processor(int length, int height){
    Processor* self = (Processor*)malloc(sizeof(Processor));

    self->anime_cache = (ProcessorAnimeData*)malloc(sizeof(ProcessorAnimeData));
    self->anime_cache->info_move = (InfoMove*)malloc(ANIME_INFO_MOVE_MAX_LENGTH*sizeof(InfoMove));
    self->anime_cache->info_move_length = 0;
    self->anime_cache->info_effect = (InfoEffect*)malloc(ANIME_INFO_EFFECT_MAX_LENGTH*sizeof(InfoEffect));
    self->anime_cache->info_effect_length = 0;

    self->base = create_base(length, height);

    self->api = (ProcessorApi*)malloc(sizeof(ProcessorApi));
    self->api->request_move = request_move;
    self->api->request_teleport = request_teleport;
    self->api->request_freeze = request_freeze;
    self->api->request_burn = request_burn;
    self->api->request_defend = request_defend;
    self->api->request_weak = request_weak;
    self->api->request_heal = request_heal;
    self->api->request_hurt = request_hurt;
    self->api->detect_exist_object = detect_exist_object;
    self->api->get_object = get_object;
    self->api->find_closest_object_in_direction = find_closest_object_in_direction;
    self->api->find_closest_object = find_closest_object;

    return self;
}

// destroy the processor
void destroy_processor(Processor *self){
    destroy_base(self->base);
    free(self->anime_cache);
    free(self->api);
    free(self);
}


// place an object at this place
// return ptr to the object if success, return NULL if failed 
// notice that the object's Block and Processor need not to be set by extern user
Object* place_object(Processor *self, Object* object, int x, int y, int length, int height){
    Block* block = self->base->create_block(self->base, x, y, length, height);
    if(block == NULL){
        return NULL;
    }
    block->any_type = object->config.type;
    block->any = (void*)object;
    object->block = block;
    object->host = self;
    return object;
}


// step the processor
void step(Processor *self);


// export the anime data
ProcessorAnimeData export_anime_data(Processor *self){
    return *(self->anime_cache);
}


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
