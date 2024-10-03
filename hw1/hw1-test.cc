#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "hw1.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


TEST(AVLTreeTests, test1)
{
    AVLTree<int> tree;
    std::vector<int> t = tree.inorderTraversal();
    ASSERT_TRUE(t.size() == 0);
}

TEST(AVLTreeTests, test2)
{
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    std::vector<int> t = tree.inorderTraversal();
    ASSERT_TRUE(t == std::vector<int>({10, 20, 25, 30, 40, 50}));
}

template<typename T>
bool operator==(std::vector<T> const& a, std::vector<T> const& b)
{
  if (a.size() != b.size()) return false;
  for (int i = 0; i < a.size(); ++i)
    if (a[i] != b[i])
      return false;
  return true;
}

TEST(AVLTreeTests, test3)
{
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    std::vector<int> t = tree.inorderTraversal();
    ASSERT_TRUE(t == std::vector<int>({10, 20, 25, 30, 40, 50}));
    for (int i = 0; i < t.size(); ++i)
       std::cout << " " << t[i];
    std::cout << "\n";
    tree.deleteNode(10);
    for (int i = 0; i < t.size(); ++i)
       std::cout << " " << t[i];
    std::cout << "\n";
    std::vector<int> t2 = tree.inorderTraversal();
    ASSERT_TRUE(t == std::vector<int>({20, 25, 30, 40, 50}));
}

TEST(AVLTreeTests, test4)
{
    AVLTree<int> tree;
    tree.insert(10);
    ASSERT_TRUE(tree.height() == 0);
    tree.insert(20);
    ASSERT_TRUE(tree.height() == 1);
    tree.insert(30);
    ASSERT_TRUE(tree.height() == 2);
    tree.insert(40);
    ASSERT_TRUE(tree.height() == 3);
    tree.insert(50);
    ASSERT_TRUE(tree.height() == 4);
    tree.insert(25);
    ASSERT_TRUE(tree.height() == 4);
    std::vector<int> t = tree.inorderTraversal();
    ASSERT_TRUE(t == std::vector<int>({10, 20, 25, 30, 40, 50}));
    ASSERT_TRUE(tree.search(10)  == true);
    tree.deleteNode(10);
    ASSERT_TRUE(tree.height() == 3);
    ASSERT_TRUE(tree.search(10)  == false);
    std::vector<int> t2 = tree.inorderTraversal();
    ASSERT_TRUE(t == std::vector<int>({20, 25, 30, 40, 50}));
    ASSERT_TRUE(tree.search(20)  == true);
    ASSERT_TRUE(tree.search(30)  == true);
    ASSERT_TRUE(tree.search(40)  == true);
    ASSERT_TRUE(tree.search(50)  == true);
    ASSERT_TRUE(tree.search(25)  == true);
    ASSERT_TRUE(tree.search(15)  == false);
}
