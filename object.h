//
// Created by cozard on 23-3-26.
//

#ifndef BCCR_IMPACT_OBJECT_H
#define BCCR_IMPACT_OBJECT_H

#include "lw_oopc.h"
#include "layer.h"
#define obj_type_t int

#define BLUE_SIDE 1
#define RED_SIDE 2
#define MIDDLE_SIDE 3
#define BLUE_ATTACK 4
#define RED_ATTACK 5

CLASS(Object)
{
    // Object Position
    int x;
    int y;

    // Specified during initialization
    const int speed;
    const int dps;
    const int range;
    const int interval;
    const obj_type_t type;

    // Object attribute
    int hp;
    int anime_clock;

    // Object Status
    char frozen;
    char burning;
    char defending;
    char weak;

    // Object action
    void (*decision)(Object *self, Layer *layer);
    void (*move)(Object *self, Layer *layer);
    void (*attack)(Object *self, Layer *layer);
    void (*affect)(Object *self, Layer *layer);
};

void object_decision(Object *self, Layer *layer);
void object_move(Object *self, Layer *layer);
void object_attack(Object *self, Layer *layer);
void object_affect(Object *self, Layer *layer);

#endif //BCCR_IMPACT_OBJECT_H
