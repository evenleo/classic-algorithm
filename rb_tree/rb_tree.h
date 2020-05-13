#ifndef RB_TREE_H
#define RB_TREE_H

#define private \
public // 万恶的宏伎俩啊，因为测试用了私有的函数，这里需要破坏了封装

typedef bool color_type;
const color_type rb_tree_red = false;
const color_type rb_tree_black = true;

template <typename Key, typename Value>
class rb_tree
{
public:
  struct Node
  {
    Key key;
    Value value;
    color_type color;
    Node *parent;
    Node *left;
    Node *right;
    Node(Key k, Value v)
        : key(k), value(v), parent(nullptr), left(nullptr), right(nullptr)
    {
    }
    Node() {}
  };
  typedef Node *node_ptr;

private:
  node_ptr header;

public:
  rb_tree()
  {
    rb_tree_init();
  }
  ~rb_tree()
  {
    destroy(root());
    delete header;
  }
  node_ptr insert(Key k, Value v)
  {
    node_ptr y = header;
    node_ptr x = root();
    while (x != nullptr)
    {
      y = x;
      x = k < x->key ? x->left : x->right;
    }
    return insert(x, y, k, v);
  }
  void erase(Key k)
  {
    node_ptr n = find(k);
    if (n != nullptr)
    {
      node_ptr y = rb_tree_rebalance_for_erase(n, header->parent, header->left,
                                               header->right);
      delete y;
    }
  }
  node_ptr find(Key k)
  {
    node_ptr x = root();
    while (x != nullptr)
    {
      if (k < x->key)
        x = x->left;
      else if (k > x->key)
        x = x->right;
      else
        break;
    }
    return x;
  }
  node_ptr lookup(Key k)
  {
    node_ptr x = nullptr;
    node_ptr y = root();
    while (y != nullptr)
    {
      if (k <= y->key)
      {
        x = y;
        y = y->left;
      }
      else
        y = y->right;
    }
    return x ? x : minimum(root());
  }

private:
  node_ptr &root()
  {
    return header->parent;
  }
  node_ptr &leftmost()
  {
    return header->left;
  }
  node_ptr &rightmost()
  {
    return header->right;
  }
  static node_ptr minimum(node_ptr x)
  {
    while (x->left != nullptr)
      x = x->left;
    return x;
  }
  static node_ptr maximum(node_ptr x)
  {
    while (x->right != nullptr)
      x = x->right;
    return x;
  }
  void rb_tree_init()
  {
    header = new Node();
    header->parent = nullptr;
    header->left = header;
    header->right = header;
    header->color = rb_tree_red;
  }
  void destroy(node_ptr x)
  {
    if (x == nullptr)
      return;
    destroy(x->left);
    destroy(x->right);
    delete x;
  }
  node_ptr insert(node_ptr x, node_ptr y, Key k, Value v)
  {
    node_ptr z;
    if (y == header || x != nullptr || k < y->key)
    {
      z = new Node(k, v);
      y->left = z;
      if (y == header)
      {
        root() = z;
        rightmost() = z;
      }
      else if (y == leftmost())
        leftmost() = z;
    }
    else
    {
      z = new Node(k, v);
      y->right = z;
      if (y == rightmost())
        rightmost() = z;
    }
    z->parent = y;
    rb_tree_rebalance(z, header->parent);
    return z;
  }
  inline void rb_tree_rebalance(node_ptr x, node_ptr &root)
  {
    x->color = rb_tree_red;
    while (x != root && x->parent->color == rb_tree_red)
    {
      if (x->parent == x->parent->parent->left)
      {
        node_ptr y = x->parent->parent->right;
        if (y && y->color == rb_tree_red)
        {
          x->parent->color = rb_tree_black;
          y->color = rb_tree_black;
          x->parent->parent->color = rb_tree_red;
          x = x->parent->parent;
        }
        else
        {
          if (x == x->parent->right)
          {
            x = x->parent;
            rb_tree_rotate_left(x, root);
          }
          x->parent->color = rb_tree_black;
          x->parent->parent->color = rb_tree_red;
          rb_tree_rotate_right(x->parent->parent, root);
        }
      }
      else
      {
        node_ptr y = x->parent->parent->left;
        if (y && y->color == rb_tree_red)
        {
          x->parent->color = rb_tree_black;
          y->color = rb_tree_black;
          x->parent->parent->color = rb_tree_red;
          x = x->parent->parent;
        }
        else
        {
          if (x == x->parent->left)
          {
            x = x->parent;
            rb_tree_rotate_right(x, root);
          }
          x->parent->color = rb_tree_black;
          x->parent->parent->color = rb_tree_red;
          rb_tree_rotate_left(x->parent->parent, root);
        }
      }
    }
    root->color = rb_tree_black;
  }
  inline void rb_tree_rotate_left(node_ptr x, node_ptr &root)
  {
    node_ptr y = x->right;
    x->right = y->left;            /*      p                      p   */
    if (y->left != 0)              /*     / \                    / \  */
      y->left->parent = x;         /*    x   d  rotate left     y   d */
    y->parent = x->parent;         /*   / \     ===========>   / \    */
    if (x == root)                 /*  a   y                  x   c   */
      root = y;                    /*     / \                / \      */
    else if (x == x->parent->left) /*    b   c              a   b     */
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }
  inline void rb_tree_rotate_right(node_ptr x, node_ptr &root)
  {
    node_ptr y = x->left;
    x->left = y->right;            /*    p                     p       */
    if (y->right != nullptr)       /*   / \                   / \      */
      y->right->parent = x;        /*  a   x   rotate right  a   y     */
    y->parent = x->parent;         /*     / \  ============>    / \    */
    if (x == root)                 /*    y   d                 b   x   */
      root = y;                    /*   / \                       / \  */
    else if (x == x->parent->left) /*  b   c                     c   d */
      x->parent->left = y;
    else
      x->parent->right = y;
    y->right = x;
    x->parent = y;
  }
  inline node_ptr rb_tree_rebalance_for_erase(node_ptr z,
                                              node_ptr &root,
                                              node_ptr &leftmost,
                                              node_ptr &rightmost)
  {
    node_ptr y = z;
    node_ptr x = nullptr;
    node_ptr x_parent = nullptr;
    if (y->left == nullptr)       // z has at most one non-null child. y == z.
      x = y->right;               // x might be null.
    else if (y->right == nullptr) // z has exactly one non-null child.  y == z.
      x = y->left;                // x is not null.
    else
    {               // z has two non-null children.  Set y to
      y = y->right; //   z's successor.  x might be null.
      while (y->left != nullptr)
        y = y->left;
      x = y->right;
    }
    if (y != z)
    { // relink y in place of z.  y is z's successor
      z->left->parent = y;
      y->left = z->left;
      if (y != z->right)
      {
        x_parent = y->parent;
        if (x)
          x->parent = y->parent;
        y->parent->left = x; // y must be a left child
        y->right = z->right;
        z->right->parent = y;
      }
      else
        x_parent = y;
      if (root == z)
        root = y;
      else if (z->parent->left == z)
        z->parent->left = y;
      else
        z->parent->right = y;
      y->parent = z->parent;
      std::swap(y->color, z->color);
      y = z;
      // y now points to node to be actually deleted
    }
    else
    { // y == z
      x_parent = y->parent;
      if (x)
        x->parent = y->parent;
      if (root == z)
        root = x;
      else if (z->parent->left == z)
        z->parent->left = x;
      else
        z->parent->right = x;
      if (leftmost == z)
        if (z->right == nullptr) // z->left must be null also
          leftmost = z->parent;
        // makes leftmost == header if z == root
        else
          leftmost = minimum(x);
      if (rightmost == z)
        if (z->left == nullptr) // z->right must be null also
          rightmost = z->parent;
        // makes rightmost == header if z == root
        else // x == z->left
          rightmost = maximum(x);
    }
    if (y->color != rb_tree_red)
    {
      while (x != root && (x == nullptr || x->color == rb_tree_black))
      {
        if (x == x_parent->left)
        {
          node_ptr w = x_parent->right;
          if (w->color == rb_tree_red)
          {
            w->color = rb_tree_black;
            x_parent->color = rb_tree_red;
            rb_tree_rotate_left(x_parent, root);
            w = x_parent->right;
          }
          if ((w->left == nullptr || w->left->color == rb_tree_black) &&
              (w->right == nullptr || w->right->color == rb_tree_black))
          {
            w->color = rb_tree_red;
            x = x_parent;
            x_parent = x_parent->parent;
          }
          else
          {
            if (w->right == nullptr || w->right->color == rb_tree_black)
            {
              if (w->left)
                w->left->color = rb_tree_black;
              w->color = rb_tree_red;
              rb_tree_rotate_right(w, root);
              w = x_parent->right;
            }
            w->color = x_parent->color;
            x_parent->color = rb_tree_black;
            if (w->right)
              w->right->color = rb_tree_black;
            rb_tree_rotate_left(x_parent, root);
            break;
          }
        }
        else
        { // same as above, with right <-> left.
          node_ptr w = x_parent->left;
          if (w->color == rb_tree_red)
          {
            w->color = rb_tree_black;
            x_parent->color = rb_tree_red;
            rb_tree_rotate_right(x_parent, root);
            w = x_parent->left;
          }
          if ((w->right == nullptr || w->right->color == rb_tree_black) &&
              (w->left == nullptr || w->left->color == rb_tree_black))
          {
            w->color = rb_tree_red;
            x = x_parent;
            x_parent = x_parent->parent;
          }
          else
          {
            if (w->left == nullptr || w->left->color == rb_tree_black)
            {
              if (w->right)
                w->right->color = rb_tree_black;
              w->color = rb_tree_red;
              rb_tree_rotate_left(w, root);
              w = x_parent->left;
            }
            w->color = x_parent->color;
            x_parent->color = rb_tree_black;
            if (w->left)
              w->left->color = rb_tree_black;
            rb_tree_rotate_right(x_parent, root);
            break;
          }
        }
      }
      if (x)
        x->color = rb_tree_black;
    }
    return y;
  }
};

#endif
