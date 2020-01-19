#include <iostream>
#include "../src/generator.h"
#include "gtest/gtest.h"
#include "ctime"

int time_count(int method,int num){
    clock_t start, finish;
    int  duration;
//    /* 测量一个事件持续的时间*/
    start = clock();
    if(method==1){
        sudoku_generate(num);
    }
    else if(method ==2){
        ques_generate(num);
    }
    else{
//        strcpy(AbsolutePath,"ques.txt");
//        settle_ques();
    }
    finish = clock();
    return (int)(finish - start) / CLOCKS_PER_SEC;
}

TEST(SudokuGenerate,test1k ){
    ASSERT_GT(60,time_count(1,1000));
}
TEST(QuesGenerate,test1k ){
    ASSERT_GT(60,time_count(2,1000));
}
//TEST(SudokuSettle,test1k ){
//    ASSERT_GT(60,time_count(3,0));
//}


TEST(SudokuGenerate,test1w){
    ASSERT_GT(60,time_count(1,10000));
}
TEST(QuesGenerate,test1w){
    ASSERT_GT(60,time_count(2,10000));
}
//TEST(SudokuSettle,test1w){
//    ASSERT_GT(60,time_count(3,10000));
//}

TEST(SudokuGenerate,test10w){
    ASSERT_GT(60,time_count(1,100000));
}
TEST(QuesGenerate,test10w){
    ASSERT_GT(60,time_count(2,100000));
}
//TEST(SudokuSettle,test10w){
//    ASSERT_GT(60,time_count(3,0));
//}

TEST(SudokuGenerate,test50w){
    ASSERT_GT(60,time_count(1,500000));
}
TEST(QuesGenerate,test50w){
    ASSERT_GT(60,time_count(2,500000));
}
//TEST(SudokuSettle,test50w){
//    ASSERT_GT(60,time_count(3,0));
//}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
