#include "lrucache.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  LRUCache<int, int> lru(10);
  for (int i = 1; i <= 10; ++i)
  {
    lru.put(i, i + 100);
  }
  lru.put(11, 111);
  assert(lru.get(1) == nullptr);

  lru.put(2, 112);
  assert(*lru.get(2) == 112);

  lru.put(9, 113);

  lru.put(12, 114);
  assert(lru.get(3) == nullptr);
}
