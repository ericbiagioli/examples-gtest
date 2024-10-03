#pragma once

struct Node
{
  int value;
  Node *next;
};

struct List
{
  Node *head;
  List();
  int len();
  void push_front(int a);
};

