#ifndef VIOLENCE_H
#define VIOLENCE_H

#include <string>

using namespace std;
/*
* 有一个文本串 S 和一个模式串 P，现在要查找 P 在 S 中的位置。如果用暴力匹配的思路，
* 并假设现在文本串 S 匹配到 i 位置，模式串 P 匹配到 j 位置，则有：
*
* 如果当前字符匹配成功（即 S[i] == P[j]），则 i++，j ++，继续匹配下一个字符。
* 如果失配（即 S[i] != P[j]），重置 i = i - (j - 1)，j = 0。相当于每次匹配失败时，
* i 回退，j 被置为 0。
*/
int violenceSearch(std::string& str, std::string& match)
{
  int strLen = str.size(); 
  int matchLen = match.size();
  if (strLen < matchLen)
    return -1;
  int i = 0;
  int j = 0;
  while (i < strLen && j < matchLen)
  {
    if (str[i] == match[j])
    {
      i++;
      j++;
    }
    else
    {
      i = i - j + 1;
      j = 0;
    }
  }
  if (j == matchLen)
    return i - j;
  return -1;
}


#endif