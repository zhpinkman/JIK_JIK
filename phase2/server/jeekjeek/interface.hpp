#ifndef INTERFACE
#define INTERFACE INTERFACE


#define ON_JEEK 2
#define LOGEDIN 1
#define COMMAND 0


#include <iostream>
#include <sstream>
#include <vector>
#include "jeeker.hpp"
class User;

using namespace std;


class Interface
{
public:
  Interface();
  bool is_liked_by_user(string jeek_id);
  void log_out(string info);
  void make_new_jeek();
  void abort_jeek(string info);
  void publish_jeek(string info);
  void add_mention(string info);
  void add_tag(string info);
  void add_text(string info);
  void jeekjeek(string line);
  void sign_up(string info);
  void log_in(string info);
  vector<string> search(string info);
  void show_comment(string info);
  string show_jeek(string info);
  void comment(string info);
  void like(string info);
  void dislike(string info);
  void reply(string info);
  void rejeek(string info);
  void follow(string info);
  void unfollow(string info);
  string notifications();
  void handle_login(pair<string, string> info);
  void handle_jeek(pair<string, string> info);
  User* logedin_user;
  int status;
protected:
  Jeeker* jeeker;
  Jeek* new_jeek;
  bool has_mention;
};
#endif
