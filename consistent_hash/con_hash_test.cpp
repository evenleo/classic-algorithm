#include "consistentHash.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  consistentHash conhash;
  conhash.addNode("192.168.0.1:8080", 2);
  conhash.addNode("192.168.0.2:8081", 3);
  conhash.addNode("10.0.1.56:8082", 2);
  conhash.addNode("10.0.1.57:8083", 3);

  conhash.helper();
  conhash.visit();

  std::string server_name = conhash.get_server_name("127.0.0.1");
  cout << "server_name: " << server_name << std::endl;
  server_name = conhash.get_server_name("128.0.0.1");
  cout << "server_name: " << server_name << std::endl;

  conhash.delNode("10.0.1.56:8082");
  server_name = conhash.get_server_name("128.0.0.1");
  cout << "server_name: " << server_name << std::endl;
}