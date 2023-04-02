#pragma once
#include "macros.h"


typedef struct Block{
    // Position : up left corner
    int x;
    int y;

    // length : x
    // height : y
    int length;
    int height;

    // this module did not release the "any" pointer
    void* any;
} Block;

struct Layer;
typedef struct Layer Layer;
struct Layer
{
    Block *layer[BASE_MAX_Y][BASE_MAX_X];

    Block* (*detect_exist_object)(Layer *self, int x1, int y1, int x2, int y2);
    Block* (*get_object)(Layer *self, int x, int y);
    Block* (*create_object)(Layer *self, int x, int y, int length, int height);
    BOOL (*teleport_object)(Layer *self, int des_x, int des_y, Block *object);
    BOOL (*move_object)(Layer *self, Block *object, int direction, int step);
    void (*delete_object)(Layer *self, Block *object);
    void (*assign_pointer)(Layer* self, Block *object, void *any);
    Block* (*find_closest_object_in_direction)(Layer *self, Block *object, int direction);
    Block* (*find_closest_object)(Layer *self, Block *object);

};

// create a layer
Layer* create_layer();

// delete a layer
void destroy_layer(Layer *self);

// NOTICE: varieble range: [x1, x2), [y1, y2)

// detect if there is an object in the area, return NULL if not, return the first object if there is
Block* detect_exist_object(Layer *self, int x1, int y1, int x2, int y2);

// get the object at this place
Block* get_object(Layer *self, int x, int y);

// create an object at this place, the place is up left corner
Block* create_object(Layer *self, int x, int y, int length, int height);

// teleport the object, the place is up left corner
// the path do not need to be empty
// if success, return TRUE
BOOL teleport_object(Layer *self, int des_x, int des_y, Block *object);

// move the object, the anchor point is up left corner
// the path need to be empty
// if success, return the object, else return NULL
BOOL move_object(Layer *self, Block *object, int direction, int step);

// delete the object
void delete_object(Layer* self, Block* object);

// assign the any pointer
void assign_pointer(Layer* self, Block* object, void* any);

// find the closest object in the direction
// if success, return the object, else return NULL
Block* find_closest_object_in_direction(Layer *self, Block *object, int direction);

// find the closest object
// if success, return the object, else return NULL
Block* find_closest_object(Layer *self, Block *object);