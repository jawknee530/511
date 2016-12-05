#include"customstream.h"
#include<unistd.h>
using namespace std;

CustomStream::CustomStream(string filename, char* search, char* replace): fs(filename, std::ios::in | std::ios::out), search(search), replace(replace)
{
  get_pos = 0;
  put_pos = 0;
  internally_hit_eof = false;
  sz_difference = 0;
  partial_match = 0;
  cout << search << replace << endl;
}

CustomStream& CustomStream::get(char& ch)
{
  if(partial_match)
  {
    ch = deck.front();
    deck.pop_front();
    cout << "getting from deck: " << ch << endl;
    partial_match--;
    return *this;
  }
  if(deck.size() > 0)
  {
    ch = deck.front();
    deck.pop_front();
    cout << "getting from deck: " << ch << endl;

    char ch2;
    fs.seekg(get_pos);
    fs.get(ch2);
    get_pos = fs.tellg();

    if(fs.eof())
    {

      cout << "set eof" << endl;
      internally_hit_eof = true;
      fs.clear();

      if(deck.size() == 0) //still have one ch to put
      {
        fs.seekp(put_pos);
        fs.put(ch);
        cout << "---PUTTING LAST character on deck: " << ch << endl;
        put_pos = fs.tellp();
        cout << "put_pos: " << put_pos << endl;
      }
      return *this;
    }
    deck.push_back(ch2);
    cout << "placing on deck: " << ch2 << endl;
    sz_difference--;
    
  }
  else
  {
    fs.seekg(get_pos);
    fs.get(ch);
    cout << "getting from file: " << ch << endl;
    get_pos = fs.tellg();
    cout << "get_pos: " << get_pos << endl;

    //cout << "put_pos " << put_pos << endl;
    //cout << "get_pos " << get_pos << endl;

    if(fs.eof())
    {
      cout << "set eof" << endl;
      internally_hit_eof = true;
      fs.clear();
    }
  }
  return *this;
}

void CustomStream::put(char& ch)
{
  fs.seekp(put_pos);
  fs.put(ch);
  cout << "-------PUTTING from main: " << ch << endl;
  put_pos = fs.tellp();
  cout << "put_pos: " << put_pos << endl;
}

bool CustomStream::eof() 
{
  if(deck.size() > 0)
  {
    return false;
  }
  else
  {
    return internally_hit_eof;
  }
}

void CustomStream::matched_search_string()
{
  string rep = replace;
  string sea = search;
  int rep_sz = rep.length();
  int sea_sz = sea.length();
  int diff;
  if(rep_sz > sea_sz)
  {
    diff = rep_sz - sea_sz;
    cout << diff << endl;
    sz_difference = diff;
    for(int i = 0; i < diff; i++)
    {
      char ch2;
      fs.seekg(get_pos);
      fs.get(ch2);
      get_pos = fs.tellg();
      cout << "getting from file: " << ch2 << endl;
      if(fs.eof())
      {
        internally_hit_eof = true;
        fs.clear();
        break;
      }
      cout << "Placing on deck: " << ch2 << endl;
      deck.push_back(ch2);
    }
  }


  for(unsigned int i = 0; i < rep.length(); i++)
  {
    fs.seekp(put_pos);
    cout << "----PUTTING from replace: " << replace[i] << endl;
    fs.put(replace[i]);
    put_pos = fs.tellp();
    cout << "put_pos: " << put_pos << endl;
  }
}

streampos CustomStream::get_put_p()
{
  return put_pos;
}

void CustomStream::found_partial_match(int count, char& ch) 
{
  bool recursive = false;
  string sea = search;
  for(int i = 0; i < count; i++)
  {
    if((i != 0) && (search[i] == search[0]) && (!recursive))
    {
      recursive = true;
      partial_match = count - i - 1;
    }
    if(!recursive)
    {
      fs.seekp(put_pos);
      fs.put(search[i]);
      cout << "-----PUTTING from search: " << search[i] << endl;
      put_pos = fs.tellp();
      cout << "put_pos: " << put_pos << endl;
    }
    else
    {
      cout << "Placing on deck: " << search[i] << endl;
      deck.push_back(search[i]);
    }
  }
  cout << "Placing on deck: " << ch << endl;
  deck.push_back(ch);
}





