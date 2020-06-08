#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>

class LRU_cache {
public:
  struct Node
  {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
  };
  typedef Node* node_ptr;

  LRU_cache(int cap) : capacity(cap), head(nullptr), tail(nullptr) {}
  ~LRU_cache()
  {
    while (head != nullptr)
    {
      node_ptr next = head->next;
      delete head;
      head = next;
    }
  }
  int get(int key)
  {
    auto it = hash_map.find(key);
    if (it == hash_map.end())
    {
      return -1;
    }
    else
    {
      node_ptr node = hash_map.at(key);
      int val = node->value;
      remove(node);
      append_head(node);
      return val;
    }
  }
  void put(int key, int value)
  {
    auto it = hash_map.find(key);
    if (it != hash_map.end())
    {
      node_ptr node = it->second;
      node->value = value;
      remove(node);
      append_head(node);
    }
    else
    {
      node_ptr node = new Node(key, value);
      if (hash_map.size() < capacity)
      {
        append_head(node);
        hash_map[key] = node;
      }
      else
      {
        hash_map.erase(tail->key);
        node_ptr del_node = tail;
        remove(del_node);
        delete del_node;
        append_head(node);
        hash_map[key] = node;
      }
    }
  }
  void append_head(node_ptr node)
  {
    if (head == nullptr)
      head = tail = node;
    else
    {
      node->next = head;
      head->prev = node;
      head = node;
    }
  }
  void remove(node_ptr node)
  {
    if (head == tail)
    {
      head = tail = nullptr;
    }
    else if (head == node)
    {
      head = node->next;
      head->prev = nullptr;
    }
    else if (tail == node)
    {
      tail = node->prev;
      tail->next = nullptr;
    }
    else
    {
      node->prev->next = node->next;
      node->next->prev = node->prev;
    }

    node->next = nullptr;
    node->prev = nullptr;
  }

private:
  int capacity;
  node_ptr head;
  node_ptr tail;
  std::unordered_map<int, node_ptr> hash_map;
};

#endif
