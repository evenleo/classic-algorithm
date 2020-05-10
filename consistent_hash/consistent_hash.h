#ifndef CONSISTENT_HASH_H
#define CONSISTENT_HASH_H

#include <iostream>
#include "rb_tree.h"
#include "md5hash.h"

class consistent_hash {
public:
  struct vnode {
    std::string name;
    int vnum;
    vnode(const std::string& n, int v) 
      : name(n), vnum(v) {}
    vnode() {}
  };

private:
  typedef unsigned int uint;
  
  rb_tree<uint, vnode> vnode_tree;
  md5hash hash;

public:
  consistent_hash() {}
  ~consistent_hash() {}

  bool add_node(const std::string& node_name, int vnum)
  {
    vnode node(node_name, vnum);
    uint key = hash.get_key(node_name);
    std::cout << "-------------------------------" << std::endl;
    std::cout << "node_name: " << node_name << ", key: " << key << std::endl;
    vnode_tree.insert(key, node);
    for (int i = 0; i < vnum; ++i)
    {
      std::string key_str = node_name + "#" + std::to_string(i);
      key = hash.get_key(key_str);
      std::cout << "node_name: " << key_str << ", key: " << key << std::endl;

      vnode_tree.insert(key, node);
    }
    std::cout << "done node_name: " << node_name << std::endl;
    return true;
  }
  bool del_vnode(const std::string& node_name)
  {
    uint key = hash.get_key(node_name);
    auto it = vnode_tree.find(key);
    if (it) {
      for (int i = 0; i < it->value.vnum; ++i)
      {
        std::string key_str = node_name + "#" + std::to_string(i);
        key = hash.get_key(key_str);
        vnode_tree.erase(key);
      }
    }
    vnode_tree.erase(key);
    return true;
  }

  bool visit_vnode() 
  {
    rb_tree<uint, vnode>::Node* root = vnode_tree.root();
    visit(root);
    return true;
  }
private:
  void visit(rb_tree<uint, vnode>::Node* node) 
  {
    if (node == nullptr) return;
    visit(node->left);
    std::cout << "key: " << node->key << ", vnode_name: " << node->value.name << std::endl;
    visit(node->right);
  }
};

#endif