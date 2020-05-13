#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <ctime>
#include <initializer_list>
#include <iostream>
#include <random>

#define private public  // 万恶的宏定义，主要用于测试访问私有成员

template <typename Key>
class skiplist {
private:
  enum { kMaxLevel = 12 };

public:
  struct Node
  {
    Node(Key k) : key(k) {}
    Key key;
    Node* next[1];  // C语言中的柔性数组技巧
  };

public:
  skiplist() : max_level(1)
  {
    head = newNode(0, kMaxLevel);
  };
  skiplist(std::initializer_list<Key> init) : skiplist()
  {
    for (const Key& k : init)
    {
      insert(k);
    }
  }
  ~skiplist()
  {
    Node* pNode = head;
    Node* del_node;
    while (nullptr != pNode)
    {
      del_node = pNode;
      pNode = pNode->next[0];
      delete del_node;
    }
  }
  skiplist(const skiplist&) = delete;
  skiplist& operator=(const skiplist&) = delete;
  skiplist& operator=(skiplist&&) = delete;

private:
  Node* newNode(const Key& key, int level)
  {
    void* node_memory = malloc(sizeof(Node) + sizeof(Node*) * (level - 1));
    return new (node_memory) Node(key);
  }
  int randomLevel()
  {
    int level = 1;
    while (rand() % 2 && level <= kMaxLevel)
      level++;
    return level;
  }
  int getRandom()
  {
    static int count = 1;
    std::default_random_engine generator(time(0) + count);
    std::uniform_int_distribution<int> distribution(1, 99999);
    count += 100;
    return distribution(generator);
  }

public:
  Node* find(const Key& key)
  {
    Node* pNode = head;
    for (int i = max_level - 1; i >= 0; --i)
    {
      while (nullptr != pNode->next[i] && pNode->next[i]->key < key)
      {
        pNode = pNode->next[i];
      }
    }
    if (nullptr != pNode->next[0] && pNode->next[0]->key == key)
      return pNode->next[0];
    return nullptr;
  }
  void insert(const Key& key)
  {
    int level = randomLevel();
    Node* new_node = newNode(key, level);
    Node* prev[kMaxLevel];
    Node* pNode = head;
    for (int i = level - 1; i >= 0; --i)
    {
      while ((nullptr != pNode->next[i]) && (pNode->next[i]->key < key))
      {
        pNode = pNode->next[i];
      }
      prev[i] = pNode;
    }
    for (int i = 0; i < level; ++i)
    {
      new_node->next[i] = prev[i]->next[i];
      prev[i]->next[i] = new_node;
    }

    if (max_level < level)
      max_level = level;
  }
  void erase(const Key& key)
  {
    Node* prev[max_level];
    Node* pNode = head;
    for (int i = max_level - 1; i >= 0; --i)
    {
      while (nullptr != pNode->next[i] && pNode->next[i]->key < key)
      {
        pNode = pNode->next[i];
      }
      prev[i] = pNode;
    }
    if (nullptr != pNode->next[0] && pNode->next[0]->key == key)
    {
      for (int i = max_level - 1; i >= 0; --i)
      {
        if (nullptr != prev[i]->next[i] && key == prev[i]->next[i]->key)
          prev[i]->next[i] = prev[i]->next[i]->next[i];
      }
      delete pNode->next[0];
    }
    while (max_level > 1 && head->next[max_level] == nullptr)
    {
      max_level--;
    }
  }

private:
  int max_level;
  Node* head;
};

#endif