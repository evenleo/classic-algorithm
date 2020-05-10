#include <iostream>
#include <cassert>
#include "consistent_hash.h"

using namespace std;

int main(int argc, char **argv)
{
  consistent_hash conhash;
  conhash.add_node("192.168.0.1:8080", 2);
  conhash.add_node("192.168.0.2:8081", 3);
  conhash.add_node("10.0.1.56:8082", 2);
  conhash.add_node("10.0.1.57:8083", 2);

  std::cout << "insert done!" << std::endl;

  conhash.visit_vnode();
}
