#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
/*
* LRU是Least Recently Used的简写，字面意思是最近最少使用，通常用于缓存淘汰策略
* 维护一个双向链表，并用无序关联式容器unordered_map存储链表的节点
*/
template <typename Key, typename Value>
class LRUCache {
private:
  struct Node
  {
    Key key;     
    Value value;
    Node* prev;
    Node* next;
    Node(Key k, Value v) 
      : key(k), value(v), 
        prev(nullptr), next(nullptr) {}
  };

  typedef Node* node_ptr;

public:
  LRUCache(size_t cap) 
    : capacity(cap), head(nullptr), tail(nullptr) {}
  ~LRUCache()
  {
    while (head != nullptr)
    {
      node_ptr next = head->next;
      delete head;
      head = next;
    }
  }
  
  /*
  * @brief 或者缓存值
  * 根据key获取value，不存在返回nullptr
  * 存在，则在双向链表中删除该节点，再将节点添加到表头
  */
  Value* get(Key key)
  {
    auto it = hashMap.find(key);
    if (it == hashMap.end())
    {
      return nullptr;
    }
    else
    {
      node_ptr node = hashMap[key];
      remove(node);
      appendHead(node);
      return &node->value;
    }
  }

  /*
  * @brief 将键值对放进缓存中
  * 缓存已存在，更新value，并在双向链表中删除该节点，再将节点添加到表头
  * 不存在，创建节点node，如果当前缓存大小小于缓存容量，直接将节点添加到
  * 表头即可，否则将双向链表的尾结点在关联式容器hashMap中删除，然后在双
  * 向链表中也删除尾节点，最后将新节点添加到表头和hashMap中
  */ 
  void put(Key key, Value value)
  {
    auto it = hashMap.find(key);
    if (it != hashMap.end())
    {
      node_ptr node = it->second;
      node->value = value;
      remove(node);
      appendHead(node);
    }
    else
    {
      node_ptr node = new Node(key, value);
      if (hashMap.size() < capacity)
      {
        appendHead(node);
        hashMap[key] = node;
      }
      else
      {
        hashMap.erase(tail->key);
        node_ptr delNode = tail;
        remove(delNode);
        delete delNode;
        appendHead(node);
        hashMap[key] = node;
      }
    }
  }

private:
  /*
  * 将节点添加到双向链表的头部
  */ 
  void appendHead(node_ptr node)
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
  
  /*
  * 在双向链表删除node节点，但不销毁节点，主要是为了其他方法可以通用
  */
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
  size_t capacity;  // 缓存容量
  node_ptr head;    // 双向链表的头结点
  node_ptr tail;    // 双向链表的尾结点
  std::unordered_map<int, node_ptr> hashMap;  // 无序关联式容器
};

#endif
