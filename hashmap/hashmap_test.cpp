#include <cassert>
#include <iostream>
#include "hashmap.h"

template <class Key> 
struct Hash { };

inline size_t __stl_hash_string(const char* s)
{
    unsigned long h = 0; 
    for ( ; *s; ++s)
        h = 5*h + *s;
    
    return size_t(h);
}

// std::string偏特化，简单测试只写std::string的特化版本
template <>
struct Hash<std::string> {
    size_t operator()(const std::string& s)
    {
        return __stl_hash_string(s.c_str());
    }
};

int main(int argc, char** argv)
{
    Hashmap<std::string, std::string, Hash<std::string> > hashmap(10);
    hashmap.insert("even", "1225");
    hashmap.insert("leo", "1226");
    hashmap.insert("cary", "1227");
    hashmap.insert("lory", "1228");

    assert(*hashmap.find("leo") == "1226");
    assert(hashmap.find("lee") == nullptr);
    assert(hashmap["even"] == "1225");
}

