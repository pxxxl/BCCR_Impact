#include <cfloat>
#include <iostream>
extern "C"{
    #include "../base/base.h"
}
#include "gtest/gtest.h"

TEST(BASE_TEST, init){
    Layer* layer = create_layer();
    ASSERT_TRUE(layer != NULL);
    destroy_layer(layer);
}

TEST(BASE_TEST, create_object){
    Layer* layer = create_layer();
    Block* block = create_object(layer, 0, 0, 3, 3);
    ASSERT_TRUE(block != NULL);
    ASSERT_TRUE(block->x == 0);
    ASSERT_TRUE(block->y == 0);
    ASSERT_TRUE(block->length == 3);
    ASSERT_TRUE(block->height == 3);
    int i, j;
    for(i = 0; i < BASE_MAX_Y; i++){
        for(j = 0; j < BASE_MAX_X; j++){
            if(i < 3 && j < 3 && i >= 0 && j >= 0){
                ASSERT_TRUE(layer->layer[i][j] == block);
            }else{
                ASSERT_TRUE(layer->layer[i][j] == NULL);
            }
        }
    }
    delete_object(layer, block);
    Block* block2 = create_object(layer, 100, 150, 5, 7);
    ASSERT_TRUE(block2 != NULL);
    ASSERT_TRUE(block2->x == 100);
    ASSERT_TRUE(block2->y == 150);
    ASSERT_TRUE(block2->length == 5);
    ASSERT_TRUE(block2->height == 7);
    for(i = 0; i < BASE_MAX_Y; i++){
        for(j = 0; j < BASE_MAX_X; j++){
            if(i < 157 && j < 105 && i >= 150 && j >= 100){
                ASSERT_TRUE(layer->layer[i][j] == block2);
            }else{
                ASSERT_TRUE(layer->layer[i][j] == NULL);
            }
        } 
    }
    Block *block3 = create_object(layer, 99, 105, 2, 2);
    ASSERT_TRUE(block3 == NULL);
    destroy_layer(layer);
}

TEST(BASE_TEST, teleport_object){
    Layer* layer = create_layer();
    Block* block = create_object(layer, 0, 0, 3, 3);
    Block* block3 = create_object(layer, 9, 9, 3, 3);
    ASSERT_TRUE(block != NULL);
    ASSERT_TRUE(block->x == 0);
    ASSERT_TRUE(block->y == 0);
    ASSERT_TRUE(block->length == 3);
    ASSERT_TRUE(block->height == 3);
    BOOL a = teleport_object(layer, 180, 180, block);
    ASSERT_TRUE(a);
    ASSERT_TRUE(block->x == 180);
    ASSERT_TRUE(block->y == 180);
    ASSERT_TRUE(block->length == 3);
    ASSERT_TRUE(block->height == 3);
    BOOL b  = teleport_object(layer, 9, 9, block);
    ASSERT_TRUE(!b);
    destroy_layer(layer);
}

TEST(BASE_TEST, move_object){
    Layer* layer = create_layer();
    Block* block = create_object(layer, 100, 100, 3, 3);
    ASSERT_TRUE(block != NULL);
    ASSERT_TRUE(block->x == 100);
    ASSERT_TRUE(block->y == 100);
    ASSERT_TRUE(block->length == 3);
    ASSERT_TRUE(block->height == 3);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}