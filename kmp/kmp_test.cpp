#include "kmp.h"
#include "violence.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  string str = "CBC DCABCABABCABD BBCCA";
  string match = "ABCABD";
  int index = violenceSearch(str, match);
  cout << index << endl;

  index = kmp(str, match);
  cout << index << endl;

  cout << endl;

}

