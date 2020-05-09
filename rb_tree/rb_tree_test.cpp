#include <iostream>
#include <cassert>
#include "rb_tree.h"
#include "rb_tree_helper.h"

using namespace std;

int main(int argc, char **argv)
{
  rb_tree<int, int> rbt;
  for (int i = 0; i < 20; ++i)
  {
    rbt.insert(i, i + 1);
  }

  rb_tree_helper<rb_tree<int, int>::Node> pt(rbt.root());
  pt.watch();
  assert(pt.is_rb_tree());

  rb_tree<int, int>::Node *ptr = rbt.find(18);
  if (ptr)
    cout << "key: " << ptr->key << "value: " << ptr->value << endl;
  else
    cout << "nullptr" << endl;

  rbt.erase(18);
  rb_tree_helper<rb_tree<int, int>::Node> pt2(rbt.root());
  pt2.watch();
  assert(pt2.is_rb_tree());

  ptr = rbt.find(18);
  if (ptr)
    cout << "key: " << ptr->key << "value: " << ptr->value << endl;
  else
    cout << "nullptr" << endl;
}
