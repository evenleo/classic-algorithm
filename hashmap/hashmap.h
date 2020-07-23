#ifndef Hashmap_H
#define Hashmap_H

/*
* @brief 链地址法实现哈希表
* @param Key: 键值
* @param Value: 值
* @param HashFunc: 哈希函数
*/
template <typename Key, typename Value, typename HashFunc>
class Hashmap {
public:
    struct Node {
        Node(Key key, Value value) 
            : key(key), value(value), next(nullptr) {}

        Key key;
        Value value;
        Node *next;
    };

public:
    Hashmap(size_t size) : size(size), hash()
    {
        table = new Node*[size];
        for (size_t i = 0; i < size; i++)
            table[i] = nullptr;
    }
    ~Hashmap()
    {
        for (size_t i = 0; i < size; i++)
        {
            Node* node = table[i];
            while (node)
            {
                Node* delNode = node;
                node = node->next;
                delete delNode;
            }
        }
        delete[] table;
    }
    void insert(const Key& key, const Value& value)
    {
        int index = hash(key) % size;
        Node* node = new Node(key, value);
        node->next = table[index];
        table[index] = node;
    }
    bool remove(const Key& key)
    {
        unsigned index = hash(key) % size;
        Node* node = table[index];
        Node* prev = nullptr;
        while (node)
        {
            if (node->key == key)
            {
                if (prev == nullptr)
                    table[index] = node->next;
                else
                    prev->next = node->next;
                delete node;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }
    Value* find(const Key& key)
    {
        unsigned  index = hash(key) % size;
        if (table[index] != nullptr)
        {
            Node* node = table[index];
            while (node)
            {
                if (node->key == key)
                    return &node->value;
                node = node->next;
            }
        }
        return nullptr;
    }
    Value& operator[](const Key& key)
    {
        unsigned  index = hash(key) % size;
        if (table[index] != nullptr)
        {
            Node* node = table[index];
            while (node)
            {
                if (node->key == key)
                    return node->value;
                node = node->next;
            }
        }

        Node* node = new Node(key, Value());
        node->next = table[index];
        table[index] = node;
        return node->value;
    }
   
private:
    HashFunc hash;
    Node** table;
    size_t size;
};

#endif