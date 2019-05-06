#ifndef TEXT
#define TEXT TEXT

#include <vector>
#include <string>
using namespace std;

class User;

class Text
{
public:
  void add_id(string id);
  void add_text(string text);
  void add_name(string given_name);
  string get_id() { return text_id; }
  string get_text() { return  text; }
protected:
  string name;
  string text_id;
  string text;
  vector<User*> users_liked;
};

#endif
