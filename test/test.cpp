#include <gtest/gtest.h>
#include "../src/generator.h"

TEST(test1,c1){
    EXPECT_EQ(1,1);
}

GTEST_API_ int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}