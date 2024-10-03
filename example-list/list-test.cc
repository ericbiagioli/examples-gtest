#include <iostream>
#include "gtest/gtest.h"
#include "list.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(LenTest, LenOfEmptyListIsZero) {
  List l;
  ASSERT_TRUE(l.len() == 0);
}

TEST(LenTest, OnePushFrontIncreasesByOne) {
  List l;
  ASSERT_TRUE(l.len() == 0);
  l.push_front(1);
  ASSERT_TRUE(l.len() == 1);
  l.push_front(1);
  ASSERT_TRUE(l.len() == 2);
  l.push_front(1);
  ASSERT_TRUE(l.len() == 3);
}

