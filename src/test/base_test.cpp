#include <iostream>
extern "C"{
    #include "../base/base.h"
}
#include "gtest/gtest.h"

TEST(BASE_TEST, valid_address){
    Layer* layer = create_layer();
    ASSERT_TRUE(layer != NULL);
    destroy_layer(layer);
}

TEST(BASE_TEST, init){
    Layer* layer = create_layer();
    ASSERT_TRUE(layer != NULL);
    destroy_layer(layer);
}

TEST(BASE_TEST, create_object){
    Layer* layer = create_layer();
    Block* block = create_object(layer, 0, 0, 1, 1);
    ASSERT_TRUE(block != NULL);
    ASSERT_TRUE(block->x == 0);
    ASSERT_TRUE(block->y == 0);
    ASSERT_TRUE(block->length == 1);
    ASSERT_TRUE(block->height == 1);
    destroy_layer(layer);
}

TEST(BASE_TEST, teleport_object){
    Layer* layer = create_layer();
    Block* block = create_object(layer, 0, 0, 3, 3);
    ASSERT_TRUE(block != NULL);
    ASSERT_TRUE(block->x == 0);
    ASSERT_TRUE(block->y == 0);
    ASSERT_TRUE(block->length == 3);
    ASSERT_TRUE(block->height == 3);
    Block* block2 = teleport_object(layer, 200, 200, block);
    ASSERT_TRUE(block2 != NULL);
    ASSERT_TRUE(block2->x == 200);
    ASSERT_TRUE(block2->y == 200);
    ASSERT_TRUE(block2->length == 3);
    ASSERT_TRUE(block2->height == 3);
    destroy_layer(layer);
}

TEST(BASE_TEST, move_object){
    Layer* layer = create_layer();
    Block* block = create_object(layer, 100, 100, 3, 3);
    ASSERT_TRUE(block != NULL);
    ASSERT_TRUE(block->x == 0);
    ASSERT_TRUE(block->y == 0);
    ASSERT_TRUE(block->length == 3);
    ASSERT_TRUE(block->height == 3);

}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}