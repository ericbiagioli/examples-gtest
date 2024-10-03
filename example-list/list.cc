#include "list.h"

List::List() : head(nullptr)
{
}

int List::len()
{
  int ret = 0;
  Node *t = head;
  while (t != nullptr) { ++ret; t = t->next; }
  return ret;
}

void List::push_front(int v) {
  Node *n = new Node();
  n->value = v;
  n->next = head;
  head = n;
}

