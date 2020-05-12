#include <cassert>
#include <iostream>
#include "skiplist.h"
#include "skiplist_helper.h"

using namespace std;

int main(int argc, char **argv)
{
  skiplist<int> skl({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
  skiplist_helper<skiplist<int>::Node> sk_hp(skl.head, skl.max_level);
  sk_hp.printAll(-1);
}
