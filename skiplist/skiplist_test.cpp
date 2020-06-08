#include "skiplist.h"
#include "skiplist_helper.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  Skiplist<int> skiplist({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  skiplist_helper<Skiplist<int>::Node> sk_hp(skiplist.head, skiplist.max_level);
  sk_hp.printAll(-1);
}
