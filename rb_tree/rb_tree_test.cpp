#include <iostream>
#include <cassert>
#include "rb_tree.h"
#include "rb_tree_helper.h"

using namespace std;

struct vnode {
  std::string name;
  int vnum;
  vnode(const std::string& n, int v) 
    : name(n), vnum(v) {}
  vnode() {}
};

void test()
{
  typedef unsigned int uint;
  rb_tree<uint, vnode> rbt;
  vnode node1("192.168.0.1:8080", 2);
  rbt.insert(56682548, node1);
  rbt.insert(83398644, node1);
  rbt.insert(1343565114, node1);

  vnode node2("192.168.0.2:8859", 3);
  rbt.insert(2944204626, node2);
  rbt.insert(699085590, node2);
  rbt.insert(3840088899, node2);
  rbt.insert(1509478695, node2);


  vnode node3("10.0.1.56:80", 2);
  rbt.insert(3832154031, node3);
  rbt.insert(1135309063, node3);
  rbt.insert(249816110, node3);


  vnode node4("10.0.1.57:80", 2);
  rbt.insert(2254896392, node4);
  rbt.insert(2820209232, node4);

  rb_tree_helper<rb_tree<uint, vnode>::Node> pt(rbt.root());
  pt.watch();
  assert(pt.is_rb_tree());

  rbt.insert(3036657673, node4);
}

int main()
{
  test();
}

int main1(int argc, char **argv)
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
    cout << "key: " << ptr->key << ", value: " << ptr->value << endl;
  else
    cout << "nullptr" << endl;

  rbt.erase(18);
  rb_tree_helper<rb_tree<int, int>::Node> pt2(rbt.root());
  pt2.watch();
  assert(pt2.is_rb_tree());

  ptr = rbt.find(18);
  if (ptr)
    cout << "key: " << ptr->key << ", value: " << ptr->value << endl;
  else
    cout << "nullptr" << endl;
}
