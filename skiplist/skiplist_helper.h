#ifndef SKIPLIST_HELPER_H
#define SKIPLIST_HELPER_H

#include "skiplist.h"

template <typename Node>
class skiplist_helper {
private:
  Node* head;
  int max_level;

public:
  skiplist_helper(Node* h, int l) : head(h), max_level(l) {}

  void printAll()
  {
    Node* pNode = head;
    while (nullptr != pNode->next[0])
    {
      std::cout << pNode->next[0]->key << " ";
      pNode = pNode->next[0];
    }
  }
  void printAll(int level)
  {
    for (int i = max_level - 1; i >= 0; --i)
    {
      Node* pNode = head;
      std::cout << "level: " << i << std::endl;
      if (level < 0 || (level >= 0 && level == i))
      {
        while (nullptr != pNode->next[i])
        {
          std::cout << pNode->next[i]->key << " ";
          pNode = pNode->next[i];
        }
        std::cout << std::endl;
        if (level >= 0)
          break;
      }
    }
  }
};

#endif