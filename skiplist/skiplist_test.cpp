#include <cassert>
#include <iostream>
#include "skiplist.h"

using namespace std;

int main(int argc, char **argv)
{
  skiplist<int> skl({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
  skl.printAll(-1);
}
