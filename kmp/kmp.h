#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

std::vector<int> getNext(std::string& match)
{
  int k = 0;
  int len = match.size();
  std::vector<int> next(len, 0);
  for (int i = 1; i < len; ++i)
  {
    if (k > 0 && match[k] != match[i])
    {
      k = next[k - 1];
    }
    if (match[k] == match[i])  
      k++;
    next[i] = k;
  }
  return next;
}


int kmp(std::string& str, std::string& match)
{
}


#endif