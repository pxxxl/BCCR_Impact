#pragma once

#include "layer.h"
#include "macros.h"
#include "base.h"
#include <malloc.h>

struct Status;
typedef struct Status Status;
struct Status{
    int hp;

    int froze;
    int burning;
    int defending;
    int weak;
};


struct Config;
typedef struct Config Config;
struct Config{
    int max_hp;
    int speed;
    int damage;
    int range;
    int interval;
    int type;
    int side;
};


struct Anime;
typedef struct Anime Anime;
struct Anime{
    int anime_clock;
};


struct Object;
typedef struct Object Object;
struct Object{
    Status status;
    Config config;
    Anime anime;

    Block* block;
    Layer* host;

    void (*init)(void *self, void *api);
    void (*birth)(void *self, void *api);
    void (*move)(void *self, void *api);
    void (*attack)(void *self, void *api);
    void (*affect)(void *self, void *api);
    void (*death)(void *self, void *api);

    void (*hurt)(void *self, int damage);
    void (*heal)(void *self, int heal);
    void (*freeze)(void *self, int degree);
    void (*burn)(void *self, int degree);
    void (*defend)(void *self, int degree);
    void (*weak)(void *self, int degree);
};


#define IMPLEMENTS_OBJECT(NAME) \
    Object object;