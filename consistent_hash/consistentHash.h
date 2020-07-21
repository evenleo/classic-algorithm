#ifndef CONSISTENT_HASH_H
#define CONSISTENT_HASH_H

#include "md5hash.h"
#include "rb_tree.h"
#include "rb_tree_helper.h"
#include <iostream>
#include <cassert>

class consistentHash {
public:
  typedef int64_t uint;
  struct VNode {
    std::string name;
    int size;
    VNode(const std::string& n, int s) : name(n), size(s) {}
    VNode() {}
  };

private:
  rb_tree<uint, VNode> vnode_tree;
  md5hash hash;

public:
  consistentHash() {}
  ~consistentHash() {}

  void addNode(const std::string& node_name, int size)
  {
    VNode node(node_name, size);
    uint key = hash.get_key(node_name);
    vnode_tree.insert(key, node);
    for (int i = 0; i < size; ++i)
    {
      std::string key_str = node_name + "#" + std::to_string(i);
      key = hash.get_key(key_str);
      vnode_tree.insert(key, node);
    }
  }
  void delNode(const std::string& node_name)
  {
    uint key = hash.get_key(node_name);
    auto ptr = vnode_tree.find(key);
    if (ptr)
    {
      for (int i = 0; i < ptr->value.size; ++i)
      {
        std::string key_str = node_name + "#" + std::to_string(i);
        uint k = hash.get_key(key_str);
        vnode_tree.erase(k);
      }
    }
    vnode_tree.erase(key);
  }
  std::string get_server_name(const std::string& name)
  {
    uint key = hash.get_key(name);
    auto it = vnode_tree.lookup(key);
    return it->value.name;
  }
  void visit()
  {
    visit(vnode_tree.root());
  }
  void helper()
  {
    rb_tree_helper<rb_tree<uint, VNode>::Node> pt(vnode_tree.root());
    pt.watch();
    assert(pt.is_rb_tree());
  }

private:
  void visit(rb_tree<uint, VNode>::Node* node)
  {
    if (node == nullptr)
      return;
    visit(node->left);
    std::cout << "key: " << node->key << ", vnode_name: " << node->value.name
              << std::endl;
    visit(node->right);
  }
};

#endif