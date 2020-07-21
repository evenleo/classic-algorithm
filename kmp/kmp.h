#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

/*
* 部分匹配值就是前缀和后缀的最长共有元素的长度。假设一个字符串 "hello"，它的前缀有 h、he、hel、hell，
* 它的后缀有 ello、llo、lo、o。
* 
* 假设模式字符串为 ABCAB ：
* 
* A 没有前缀和后缀，公有元素长度为 0
* AB 的前缀有 A，后缀有 B，公有元素长度为 0
* ABC 的前缀有 A、AB，后缀有 BC、C，公有元素长度为 0
* ABCA 的前缀有 A、AB、ABC，后缀有 BCA、CA、A，公有元素长度为 1
* ABCAB 的前缀有 A、AB、ABC、ABCA，后缀有 BCAB、CAB、AB、B，公有元素长度为 2
* ABCABD 的前缀有 A、AB、ABC、ABCA、ABCAB，后缀有 BCABD、CABD、ABD、BD、D，公有元素长度为 0
* 所以 ABCABD 中每个字符对于的匹配值分别为 0、0、0、1、2、0。
*/

std::vector<int> getNext(const std::string& match)
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

int kmp(const std::string& str, const std::string& match)
{
  std::vector<int> next = getNext(match);
  int k = 0;
  for (int i = 0; i < str.size(); ++i)
  {
    if (k > 0 && match[k] != str[i])
      k = next[k];
    if (match[k] == str[i])
      k++;
    if (k == match.size())
      return i - k + 1;
  }
  return -1;
}

#endif