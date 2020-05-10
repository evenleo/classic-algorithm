#ifndef CONSISTENT_HASH_H
#define CONSISTENT_HASH_H

#include <iostream>
#include "rb_tree.h"
#include "rb_tree_helper.h"
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
  typedef int64_t uint;
  
  rb_tree<uint, vnode> vnode_tree;
  md5hash hash;

public:
  consistent_hash() {}
  ~consistent_hash() {}

  bool add_node(const std::string& node_name, int vnum)
  {
    vnode node(node_name, vnum);
    uint key = hash.get_key(node_name);
    vnode_tree.insert(key, node);
    for (int i = 0; i < vnum; ++i)
    {
      std::string key_str = node_name + "#" + std::to_string(i);
      key = hash.get_key(key_str);
      vnode_tree.insert(key, node);
    }
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
        uint k = hash.get_key(key_str);
        vnode_tree.erase(k);
      }
    }
    vnode_tree.erase(key);
    return true;
  }
  std::string get_server_name(const std::string& name)
  {
    uint key = hash.get_key(name);
    auto it = vnode_tree.lookup(key);
    return it->value.name;
  }
  void visit_vnode() 
  {
    rb_tree<uint, vnode>::Node* root = vnode_tree.root();
    visit(root);
  }
  
  void helper()
  {
    rb_tree_helper<rb_tree<uint, vnode>::Node> pt(vnode_tree.root());
    pt.watch();
    assert(pt.is_rb_tree());
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