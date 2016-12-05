#include<iostream>
#include<cstring>
#include<unistd.h>
#include"customstream.h"
using namespace std;

int main(int argc, char* argv[])
{
  char* sea = argv[1];
  string search = argv[1];
  char* rep = argv[2];
  string replace = argv[2];
  char* filename = argv[3];

  CustomStream cs(filename, sea, rep);
  char ch;
  unsigned int match_count = 0;
  int looper = 50;

  while(!cs.get(ch).eof() && looper)
  {
    if(ch == sea[match_count])
    {
      ++match_count;
      if(match_count < search.length())
        continue;
    }

    if(match_count == search.length())
    {
      cs.matched_search_string();
      match_count = 0;
      continue;
    }
    else if(match_count > 0)
    {
      cs.found_partial_match(match_count, ch); //replace from search string then push front character on deque
    }
    else
    {
      cs.put(ch);
    }
    match_count = 0;
    looper--;
  }
  truncate(filename, cs.get_put_p());
  return 0;
}
