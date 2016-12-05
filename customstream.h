#ifndef CUSTOMSTREAM_H
#define CUSTOMSTREAM_H
#include<fstream>
#include<string>
#include<cstring>
#include<iostream>
#include"trackingdeque.h"
using namespace std;

class CustomStream {
  public:
    CustomStream(string filename, char* search, char* replace);
    CustomStream& get(char& ch);
    void put(char& ch);
    void matched_search_string();
    void found_partial_match(int count, char& ch);
    bool eof();
    streampos get_put_p();
  private:
    fstream fs;
    char* search;
    char* replace;
    int rep_size;
    streampos get_pos;
    streampos put_pos;
    bool internally_hit_eof;
    deque<char> deck;
    int sz_difference;
    int partial_match;
};

#endif
