#include <cfloat>
#include <iostream>
extern "C"{
    #include "../base/base.h"
}
#include "gtest/gtest.h"

TEST(BASE_TEST, init){
    Base* base = create_base(5, 5);
    ASSERT_TRUE(base != NULL);
    destroy_base(base);
}

TEST(BASE_TEST, create_block){
    Base* base = create_base(5, 5);
    Block* block = create_block(base, 0, 0, 1, 2);
    Block* block2 = create_block(base, 3, 3, 2, 2);
    Block* block3 = create_block(base, 0, 4, 1, 1);
    ASSERT_TRUE(block != NULL);
    ASSERT_TRUE(block->x == 0);
    ASSERT_TRUE(block->y == 0);
    ASSERT_TRUE(block->length == 1);
    ASSERT_TRUE(block->height == 2);
    Block* true_matrix[5][5] = {
        {block, 0, 0, 0, 0},
        {block, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, block2, block2},
        {block3, 0, 0, block2, block2}
    };
    int i, j;
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            ASSERT_TRUE(base->base[i][j] == true_matrix[i][j]);
        }
    }
    delete_block(base, block);
    Block* true_matrix2[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, block2, block2},
        {block3, 0, 0, block2, block2}
    };
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            ASSERT_TRUE(base->base[i][j] == true_matrix2[i][j]);
        }
    }
    destroy_base(base);
}

TEST(BASE_TEST, teleport_block){
    Base* base = create_base(5, 5);
    Block* block = create_block(base, 0, 0, 1, 2);
    Block* block2 = create_block(base, 3, 3, 2, 2);
    Block* block3 = create_block(base, 0, 4, 1, 1);
    BOOL a = teleport_block(base, 1, 0, block);
    Block* true_matrix[5][5] = {
        {0, block, 0, 0, 0},
        {0, block, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, block2, block2},
        {block3, 0, 0, block2, block2}
    };
    int i, j;
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            ASSERT_TRUE(base->base[i][j] == true_matrix[i][j]);
        }
    }
    BOOL b  = teleport_block(base, 0, 3, block);
    ASSERT_TRUE(!b);
    destroy_base(base);
}

TEST(BASE_TEST, move_block){
    Base* base = create_base(5, 5);
    Block* block = create_block(base, 0, 0, 1, 2);
    Block* block2 = create_block(base, 3, 3, 2, 2);
    Block* block3 = create_block(base, 0, 2, 1, 1);
    Block* true_matrix[5][5] = {
        {block, 0, 0, 0, 0},
        {block, 0, 0, 0, 0},
        {block3, 0, 0, 0, 0},
        {0, 0, 0, block2, block2},
        {0, 0, 0, block2, block2}
    };
    BOOL A = base->move_block(base, block, DOWN, 3);
    ASSERT_FALSE(A);
    BOOL B = base->move_block(base, block, RIGHT, 1);
    ASSERT_TRUE(B);
    int i, j;
    Block* true_matrix2[5][5] = {
        {0, block, 0, 0, 0},
        {0, block, 0, 0, 0},
        {block3, 0, 0, 0, 0},
        {0, 0, 0, block2, block2},
        {0, 0, 0, block2, block2}
    };
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            ASSERT_TRUE(base->base[i][j] == true_matrix2[i][j]);
        }
    }
    BOOL C = base->move_block(base, block2, UP, 1);
    ASSERT_TRUE(C);
    Block* true_matrix3[5][5] = {
        {0, block, 0, 0, 0},
        {0, block, 0, 0, 0},
        {block3, 0, 0, block2, block2},
        {0, 0, 0, block2, block2},
        {0, 0, 0, 0, 0}
    };
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            ASSERT_TRUE(base->base[i][j] == true_matrix3[i][j]);
        }
    }
    BOOL D = base->move_block(base, block, LEFT, 1);
    ASSERT_TRUE(D);
    Block* true_matrix4[5][5] = {
        {block, 0, 0, 0, 0},
        {block, 0, 0, 0, 0},
        {block3, 0, 0, block2, block2},
        {0, 0, 0, block2, block2},
        {0, 0, 0, 0, 0}
    };
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            ASSERT_TRUE(base->base[i][j] == true_matrix4[i][j]);
        }
    }
}

TEST(BASE_TEST, detect_exist_block){
    Base* base = create_base(5, 5);
    Block* block = create_block(base, 0, 0, 1, 2);
    Block* block2 = create_block(base, 3, 3, 2, 2);
    Block* block3 = create_block(base, 0, 2, 1, 1);
    Block* true_matrix[5][5] = {
        {block, 0, 0, 0, 0},
        {block, 0, 0, 0, 0},
        {block3, 0, 0, 0, 0},
        {0, 0, 0, block2, block2},
        {0, 0, 0, block2, block2}
    };
    Block* A = base->detect_exist_block(base, 0, 0, 1, 1);
    ASSERT_TRUE(A == block);
    Block* B = base->detect_exist_block(base, 0, 0, 2, 2);
    ASSERT_TRUE(B == block);
    Block* C = base->detect_exist_block(base, 1, 0, 2, 2);
    ASSERT_TRUE(C == NULL);
    Block* D = base->detect_exist_block(base, 3, 3, 4, 4);
    ASSERT_TRUE(D == block2);
    Block* E = base->detect_exist_block(base, 0, 3, 2, 4);
    ASSERT_TRUE(E == NULL);
    Block* F = base->detect_exist_block(base, 0, 2, 1, 3);
    ASSERT_TRUE(F == block3);
}

TEST(BASE_TEST, find_closest_block_in_direction){
    Base* base = create_base(5, 5);
    Block* block = create_block(base, 0, 0, 1, 2);
    Block* block2 = create_block(base, 3, 3, 2, 2);
    Block* block3 = create_block(base, 0, 4, 1, 1);
    Block* block4 = create_block(base, 2, 2, 1, 1);
    Block* true_matrix[5][5] = {
        {block, 0, 0, 0, 0},
        {block, 0, 0, 0, 0},
        {0, 0, block4, 0, 0},
        {0, 0, 0, block2, block2},
        {block3, 0, 0, block2, block2}
    };
    Block* R = base->find_closest_block_in_direction(base, block, RIGHT);
    Block* L = base->find_closest_block_in_direction(base, block, LEFT);
    Block* U = base->find_closest_block_in_direction(base, block, UP);
    Block* D = base->find_closest_block_in_direction(base, block, DOWN);
    ASSERT_TRUE(R == NULL);
    ASSERT_TRUE(L == NULL);
    ASSERT_TRUE(U == NULL);
    ASSERT_TRUE(D == block3);

    Block* R2 = base->find_closest_block_in_direction(base, block3, RIGHT);
    Block* L2 = base->find_closest_block_in_direction(base, block3, LEFT);
    Block* U2 = base->find_closest_block_in_direction(base, block3, UP);
    Block* D2 = base->find_closest_block_in_direction(base, block3, DOWN);
    ASSERT_TRUE(R2 == block2);
    ASSERT_TRUE(L2 == NULL);
    ASSERT_TRUE(U2 == block);
    ASSERT_TRUE(D2 == NULL);

    Block* R3 = base->find_closest_block_in_direction(base, block4, RIGHT);
    Block* L3 = base->find_closest_block_in_direction(base, block4, LEFT);
    Block* U3 = base->find_closest_block_in_direction(base, block4, UP);
    Block* D3 = base->find_closest_block_in_direction(base, block4, DOWN);
    ASSERT_TRUE(R3 == NULL);
    ASSERT_TRUE(L3 == NULL);
    ASSERT_TRUE(U3 == NULL);
    ASSERT_TRUE(D3 == NULL);

    Block* R4 = base->find_closest_block_in_direction(base, block2, RIGHT);
    Block* L4 = base->find_closest_block_in_direction(base, block2, LEFT);
    Block* U4 = base->find_closest_block_in_direction(base, block2, UP);
    Block* D4 = base->find_closest_block_in_direction(base, block2, DOWN);
    ASSERT_TRUE(R4 == NULL);
    ASSERT_TRUE(L4 == block3);
    ASSERT_TRUE(U4 == NULL);
    ASSERT_TRUE(D4 == NULL);
}

TEST(BASE_TEST, find_closest_block){
    Base* base = create_base(5, 5);
    Block* block = create_block(base, 0, 0, 1, 2);
    Block* block2 = create_block(base, 3, 3, 2, 2);
    Block* block3 = create_block(base, 0, 4, 1, 1);
    Block* block4 = create_block(base, 2, 2, 1, 1);
    Block* true_matrix[5][5] = {
        {block , 0, 0     , 0     , 0},
        {block , 0, 0     , 0     , 0},
        {0     , 0, block4, 0     , 0},
        {0     , 0, 0     , block2, block2},
        {block3, 0, 0     , block2, block2}
    };
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            ASSERT_TRUE(base->base[i][j] == true_matrix[i][j]);
        }
    }
    Block* A = base->find_closest_block(base, block);
    ASSERT_TRUE(A == block4);
    Block* B = base->find_closest_block(base, block2);
    ASSERT_TRUE(B == block4);
    Block* C = base->find_closest_block(base, block3);
    ASSERT_TRUE(C == block4);
    Block* D = base->find_closest_block(base, block4);
    ASSERT_TRUE(D == block2);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}