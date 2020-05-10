#ifndef RB_TREE_HELPER_H
#define RB_TREE_HELPER_H

#include <stdio.h>
#include "rb_tree.h"

template <typename Node>
class rb_tree_helper {
public:
  rb_tree_helper(Node *n) : root(n), prev(nullptr) {}
  void watch() { rb_tree_for_watch(root); }
  bool is_rb_tree()
  {
    if (root->color == rb_tree_red)
      return false;
    int black_count = 0;
    return is_rb_tree(root, black_count);
  }

private:
  Node *root;
  Node *prev;

private:
  struct backlog {
    Node *node;
    int next_sub_idx;
  };
  enum
  {
    LeftIndex,
    RightIndex
  };
  enum
  {
    MaxLevel = 64
  };
  static inline void
  nbl_push(backlog *nbl, backlog **top, backlog **bottom)
  {
    if (*top - *bottom < MaxLevel)
      (*(*top)++) = *nbl;
  }
  static inline backlog *nbl_pop(backlog **top, backlog **bottom)
  {
    return *top > *bottom ? --*top : nullptr;
  }
  static inline int nbl_is_empty(backlog *top, backlog *bottom)
  {
    return top == bottom;
  }
  static inline bool is_leaf(Node *node)
  {
    return node->left == nullptr && node->right == nullptr;
  }
  static void node_print(Node *node)
  {
    if (node != nullptr)
    {
      if (node->color)
        printf("%ld\n", node->key);
      else
        printf("\033[1;31;40m%ld\n\033[0m", node->key); // 红色打印
    }
    else
      printf("\n");
  }
  static void rb_tree_for_watch(Node *root)
  {
    int level = 0;
    Node *node = root;
    int prev_sub_index;
    backlog nbl;
    backlog *p_nbl = nullptr;
    backlog *top, *bottom, nblStack[MaxLevel];
    top = bottom = nblStack;

    for (;;)
    {
      if (node != nullptr)
      {
        //以下两句非常巧妙实现，回到回溯点时不打印回溯点，打印左节点，该过程循环两遍，
        //第一遍不打印，第二遍节点存在，且p_nbl已为空，此时sub_index为RightIndex，会打印
        int sub_index = p_nbl != nullptr ? p_nbl->next_sub_idx : RightIndex;
        p_nbl = nullptr;

        //记录回溯点，先保存左再保存右，当前sub_index为RightIndex打印
        if (is_leaf(node) || sub_index == LeftIndex)
        {
          nbl.node = nullptr;
          nbl.next_sub_idx = RightIndex;
        }
        else
        {
          nbl.node = node;
          nbl.next_sub_idx = LeftIndex;
        }
        nbl_push(&nbl, &top, &bottom);
        level++;
        if (sub_index == RightIndex)
        {
          for (int i = 1; i < level; ++i)
          {
            if (i == level - 1)
            {
              if (prev_sub_index == LeftIndex)
                printf("%-8s", "l-------");
              else
                printf("%-8s", "r-------");
            }
            else
            {
              if (nblStack[i - 1].node != nullptr)
                printf("%-8s", "|");
              else
                printf("%-8s", " ");
            }
          }
          node_print(node);
        }
        node = sub_index == LeftIndex ? node->left : node->right;
        prev_sub_index = sub_index;
      }
      else
      {
        p_nbl = nbl_pop(&top, &bottom);
        if (p_nbl == nullptr)
          break;
        node = p_nbl->node;
        level--;
      }
    }
  }
  bool is_rb_tree(Node *node, int &black_count)
  {
    if (node == nullptr)
    {
      black_count++;
      return true;
    }
    if (node->color == rb_tree_red && node->parent->color == rb_tree_red)
      return false;

    if (node->color == rb_tree_black)
      black_count++;

    int left_black_count = 0;
    int right_black_count = 0;
    if (!is_rb_tree(node->left, left_black_count))
      return false;

    if (prev != nullptr && node->key < prev->key)
      return false;
    prev = node;

    if (!is_rb_tree(node->right, right_black_count))
      return false;

    if (left_black_count != right_black_count)
      return false;

    black_count += left_black_count;
    return true;
  }
};

#endif