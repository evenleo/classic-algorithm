#include "kmp.h"
#include "violence.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  // string str = "CBC DCABCABABCABD BBCCA";
  // string match = "ABCABD";
  // int index = violenceSearch(str, match);
  // cout << index << endl;

  std::string match = "abcabd";
  std::vector<int> next = getNext(match);
  for (auto& i : next)
  {
    cout << i << " ";
  }

  cout << endl;

}

