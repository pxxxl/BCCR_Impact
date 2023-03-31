#include "base.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


// create a layer
Layer* create_layer(){
    Layer *self = (Layer*)malloc(sizeof(Layer));
    int i, j;
    for(i = 0; i < BASE_MAX_Y; i++){
        for(j = 0; j < BASE_MAX_X; j++){
            self->layer[i][j] = NULL;
        }
    }
    self->detect_exist_object = detect_exist_object;
    self->get_object = get_object;
    self->create_object = create_object;
    self->teleport_object = teleport_object;
    self->move_object = move_object;
    self->delete_object = delete_object;
    self->assign_pointer = assign_pointer;
    self->find_closest_object_in_direction = find_closest_object_in_direction;
    self->find_closest_object = find_closest_object;
    return self;
}

// delete a layer
void destroy_layer(Layer *self){
    if(self == NULL){
        printf("ERROR: NULL layer in destroy_layer");
        exit(1);
    }
    int i, j;
    for(i = 0; i < BASE_MAX_Y; i++){
        for(j = 0; j < BASE_MAX_X; j++){
            Block *object = self->layer[i][j];
            if(object != NULL){
                delete_object(self, object);
            }
        }
    }
    free(self);
}

// verify if the address is valid
BOOL is_valid_address(Layer *self, int x, int y){
    if(x < 0 || x >= BASE_MAX_X || y < 0 || y >= BASE_MAX_Y){
        return FALSE;
    }
    return TRUE;
}


// detect if there is an object in the area, return NULL if not, return the first object if there is
Block* detect_exist_object(Layer *self, int x1, int y1, int x2, int y2){
    if(is_valid_address(self, x1, y1) &&    // up left corner
       is_valid_address(self, x2, y2) &&    // down right corner
       x1 <= x2 && y1 <= y2){               // x1 <= x2 and y1 <= y2
        printf("ERROR: invalid address in detect_exist_object");
        exit(1);
    }
    int i, j;
    for(i = y1; i <= y2; i++){
        for(j = x1; j <= x2; j++){
            if(self->layer[i][j] != NULL){
                return self->layer[i][j];
            }
        }
    }
    return NULL;
}


// get the object at this place
Block* get_object(Layer *self, int x, int y){
    if(is_valid_address(self, x, y)){
        printf("ERROR: invalid address in get_object");
        exit(1);
    }
    return self->layer[y][x];
}

// create an object at this place, the place is up left corner
Block* create_object(Layer *self, int x, int y, int length, int height){
    if(is_valid_address(self, x, y) &&    // up left corner
       is_valid_address(self, x+length-1, y+height-1)){    // down right corner
        printf("ERROR: invalid address in create_object");
        exit(1);
    }
    if(detect_exist_object(self, x, y, x+length-1, y+height-1) != NULL){
        return NULL;
    }
    Block *object = (Block*)malloc(sizeof(Block));
    object->x = x;
    object->y = y;
    object->length = length;
    object->height = height;
    int i, j;
    for(i = y; i < y+height; i++){
        for(j = x; j < x+length; j++){
            self->layer[i][j] = object;
        }
    }
    return object;
}

// teleport the object, the place is up left corner
// the path do not need to be empty
// if success, return the object, else return NULL
Block* teleport_object(Layer *self, int des_x, int des_y, Block *object){
    if(is_valid_address(self, des_x, des_y) &&    // up left corner
       is_valid_address(self, des_x+object->length-1, des_y+object->height-1)){    // down right corner
        printf("ERROR: invalid address in teleport_object");
        exit(1);
    }
    if(detect_exist_object(self, des_x, des_y, des_x+object->length-1, des_y+object->height-1) != NULL){
        return NULL;
    }
    if(object == NULL){
        printf("ERROR: NULL object in teleport_object");
        exit(1);
    }
    int i, j;
    for(i = object->y; i < object->y+object->height; i++){
        for(j = object->x; j < object->x+object->length; j++){
            self->layer[i][j] = NULL;
        }
    }
    object->x = des_x;
    object->y = des_y;
    for(i = object->y; i < object->y+object->height; i++){
        for(j = object->x; j < object->x+object->length; j++){
            self->layer[i][j] = object;
        }
    }
    return object;
}

// move the object, the anchor point is up left corner
// the path need to be empty
// if success, return the object, else return NULL
Block* move_object(Layer *self, Block *object, int direction, int step){
    if(object == NULL){
        printf("ERROR: NULL object in move_object");
        exit(1);
    }
    if(is_valid_address(self, object->x, object->y) &&
       is_valid_address(self, object->x+object->length-1, object->y+object->height-1)){
        printf("ERROR: invalid address in move_object");
        exit(1);
    }
    if(step == 0){
        return object;
    }
    int des_x = object->x;
    int des_y = object->y;
    int empty_zone_x1, empty_zone_y1, empty_zone_x2, empty_zone_y2;
    switch(direction){
        case UP:
            des_y -= step;
            empty_zone_x1 = des_x;
            empty_zone_y1 = des_y;
            empty_zone_x2 = object->x;
            empty_zone_y2 = object->y;
            break;
        case DOWN:
            des_y += step;
            empty_zone_x1 = object->x;
            empty_zone_y1 = object->y + object->height;
            empty_zone_x2 = des_x;
            empty_zone_y2 = des_y + object->height;
            break;
        case LEFT:
            des_x -= step;
            empty_zone_x1 = des_x;
            empty_zone_y1 = des_y;
            empty_zone_x2 = object->x;
            empty_zone_y2 = object->y;
            break;
        case RIGHT:
            des_x += step;
            empty_zone_x1 = object->x + object->length;
            empty_zone_y1 = object->y;
            empty_zone_x2 = des_x + object->length;
            empty_zone_y2 = des_y;
            break;
        default:
            printf("ERROR: invalid direction in move_object");
            exit(1);
    }
    if(detect_exist_object(self, empty_zone_x1, empty_zone_y1, empty_zone_x2, empty_zone_y2) != NULL){
        return NULL;
    }
    if(is_valid_address(self, des_x, des_y) &&    // up left corner
       is_valid_address(self, des_x+object->length-1, des_y+object->height-1)){    // down right corner
        printf("ERROR: invalid address in move_object");
        exit(1);
    }
    int i, j;
    for(i = object->y; i < object->y+object->height; i++){
        for(j = object->x; j < object->x+object->length; j++){
            self->layer[i][j] = NULL;
        }
    }
    object->x = des_x;
    object->y = des_y;
    for(i = object->y; i < object->y+object->height; i++){
        for(j = object->x; j < object->x+object->length; j++){
            self->layer[i][j] = object;
        }
    }
    return object;
}

// delete the object
void delete_object(Layer* self, Block* object){
    if(object == NULL){
        printf("ERROR: NULL object in delete_object");
        exit(1);
    }
    int i, j;
    for(i = object->y; i < object->y+object->height; i++){
        for(j = object->x; j < object->x+object->length; j++){
            self->layer[i][j] = NULL;
        }
    }
    free(object);
}

// x1 == x2 or y1 == y2, not allowed x1 == x2 && y1 == y2
// assume x1 == x2, then detect from y1 to y2, range [y1, y2)
// if detected object, return yn, else return -1
static int path_detect(Layer* self, int x1, int y1, int x2, int y2){
    if(!is_valid_address(self, x1, y1) || !is_valid_address(self, x2, y2)){
        printf("ERROR: invalid address in (inline) path_detect");
        exit(1);
    }
    if(x1 == x2 && y1 != y2){
        int i;
        if(y1 < y2){
            for(i = y1; i < y2; i++){
                if(self->layer[i][x1] != NULL){
                    return i;
                }
            }
        }else{
            for(i = y1; i > y2; i--){
                if(self->layer[i][x1] != NULL){
                    return i;
                }
            }
        }
        return -1;
    }else if(x1 != x2 && y1 == y2){
        int i;
        if(x1 < x2){
            for(i = x1; i < x2; i++){
                if(self->layer[y1][i] != NULL){
                    return i;
                }
            }
        }else{
            for(i = x1; i > x2; i--){
                if(self->layer[y1][i] != NULL){
                    return i;
                }
            }
        }
        return -1;
    }
    printf("ERROR: invalid address in (inline) path_detect");
    exit(1);
}

// find the closest object in the direction
// if success, return the object, else return NULL
Block* find_closest_object_in_direction(Layer *self, Block *object, int direction){
    if(object == NULL){
        printf("ERROR: NULL object in find_closest_object_in_direction");
        exit(1);
    }
    if(is_valid_address(self, object->x, object->y) &&
       is_valid_address(self, object->x+object->length-1, object->y+object->height-1)){
        printf("ERROR: invalid address in find_closest_object_in_direction");
        exit(1);
    }
    int i, j;
    int* touch_position;
    int des_x;
    int des_y;
    int pos;
    int expect;
    int expect_pos;
    switch(direction){
        case UP:
            touch_position = (int*)malloc(sizeof(int)*object->length);
            for(i = object->x; i < object->x + object->length; i++){
                pos = path_detect(self, i, object->y + 1, i, -1);
                touch_position[i] = pos;
            }
            expect = -1;
            expect_pos = -1;
            for(i = object->x; i < object->x + object->length; i++){
                if(touch_position[i] != -1 && touch_position[i] > expect){
                    expect = touch_position[i];
                    expect_pos = i;
                }
            }
            if(expect_pos == -1){
                return NULL;
            }
            des_x = expect_pos;
            des_y = expect;
            break;
        case DOWN:
            touch_position = (int*)malloc(sizeof(int)*object->length);
            for(i = object->x; i < object->x + object->length; i++){
                pos = path_detect(self, i, object->y+object->height, i, BASE_MAX_Y);
                touch_position[i] = pos;
            }
            expect = BASE_MAX_Y;
            expect_pos = -1;
            for(i = object->x; i < object->x + object->length; i++){
                if(touch_position[i] != -1 && touch_position[i] < expect){
                    expect = touch_position[i];
                    expect_pos = i;
                }
            }
            if(expect_pos == -1){
                return NULL;
            }
            des_x = expect_pos;
            des_y = expect;
            break;
        case LEFT:
            touch_position = (int*)malloc(sizeof(int)*object->height);
            for(i = object->y; i < object->y + object->height; i++){
                pos = path_detect(self, object->x - 1, i, -1, i);
                touch_position[i] = pos;
            }
            expect = -1;
            expect_pos = -1;
            for(i = object->y; i < object->y + object->height; i++){
                if(touch_position[i] != -1 && touch_position[i] > expect){
                    expect = touch_position[i];
                    expect_pos = i;
                }
            }
            if(expect_pos == -1){
                return NULL;
            }
            des_x = expect;
            des_y = expect_pos;
            break;
        case RIGHT:
            touch_position = (int*)malloc(sizeof(int)*object->height);
            for(i = object->y; i < object->y + object->height; i++){
                int pos;
                pos = path_detect(self, object->x+object->length, i, BASE_MAX_X, i);
                touch_position[i] = pos;
            }
            expect = BASE_MAX_X;
            expect_pos = -1;
            for(i = object->y; i < object->y + object->height; i++){
                if(touch_position[i] != -1 && touch_position[i] < expect){
                    expect = touch_position[i];
                    expect_pos = i;
                }
            }
            if(expect_pos == -1){
                return NULL;
            }
            des_x = expect;
            des_y = expect_pos;
            break;
    }
    if(is_valid_address(self, des_x, des_y)){
        return self->layer[des_y][des_x];
    }
    return NULL;
}

// assign the any pointer
void assign_pointer(Layer* self, Block* object, void* any){
    if(object == NULL){
        printf("ERROR: NULL object in assign_pointer");
        exit(1);
    }
    object->any = any;
}


// scan the around of the object
// if success, return the object, else return NULL
static Block* find_closest_object_around(Layer *self, Block *object, int radius){
    if(object == NULL){
        printf("ERROR: NULL object in find_closest_object_around");
        exit(1);
    }
    if(is_valid_address(self, object->x, object->y) &&
       is_valid_address(self, object->x+object->length-1, object->y+object->height-1)){
        printf("ERROR: invalid address in find_closest_object_around");
        exit(1);
    }
    int i, j;
    int x1, x2, y1, y2;
    x1 = object->x - radius;
    x2 = object->x + object->length + radius + 1;
    y1 = object->y - radius;
    y2 = object->y + object->height + radius + 1;
    for(i = y1; i < y2; i++){
        if(is_valid_address(self, x1, i)) continue;
        if(is_valid_address(self, x2, i)) continue;
        if(self->layer[x1][i] != NULL){
            return self->layer[x1][i];
        }
        if(self->layer[x2][i] != NULL){
            return self->layer[x2][i];
        }
    }
    for(i = x1; i < x2; i++){
        if(is_valid_address(self, i, y1)) continue;
        if(is_valid_address(self, i, y2)) continue;
        if(self->layer[i][y1] != NULL){
            return self->layer[i][y1];
        }
        if(self->layer[i][y2] != NULL){
            return self->layer[i][y2];
        }
    }
    return NULL;
}

// find the closest object
// if success, return the object, else return NULL
Block* find_closest_object(Layer *self, Block *object){
    if(object == NULL){
        printf("ERROR: NULL object in find_closest_object");
        exit(1);
    }
    if(is_valid_address(self, object->x, object->y) &&
       is_valid_address(self, object->x+object->length-1, object->y+object->height-1)){
        printf("ERROR: invalid address in find_closest_object");
        exit(1);
    }
    int i;
    for(i = 1; i < LOOKUP_MAX_RADIUS; i++){
        Block *result = find_closest_object_around(self, object, i);
        if(result != NULL){
            return result;
        }
    }
    return NULL;
}
