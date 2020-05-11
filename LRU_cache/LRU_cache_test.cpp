#include <cassert>
#include <iostream>
#include "LRU_cache.h"

using namespace std;

int main(int argc, char **argv)
{
  LRU_cache lru(10);
  for (int i = 1; i <= 10; ++i)
  {
    lru.put(i, i+100);
  } 
  lru.put(11, 111);
  assert(lru.get(1) == -1);

  lru.put(2, 112);
  assert(lru.get(2) == 112);

  lru.put(9, 113);

  lru.put(12, 114);
  assert(lru.get(3) == -1);
}
