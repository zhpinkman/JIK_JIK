#ifndef JEEKER
#define JEEKER JEEKER

#include <string>
#include <vector>
using namespace std;


class User;
class Jeek;
class Comment;
class Interface;

class Jeeker
{
public:
  bool check_jeek_status(string jeek_id, User* user);
  void handle_login(Interface* interface, string info);
  void handle_signup(string info);
  void rejeek_by_id(User* rejeeker, string jeek_id);
  vector<string> search(string info);
  string show_jeek_by_id(string info);
  void show_comment_by_id(string info);
  void add_comment_to_data_base(Comment* new_comment);
  void add_reply_to_data_base(Comment* reply);
  vector<string> show_hashtag(string hashtag);
  void sign_up(string username, string name, string password);
  void  check_invalid_user(User* new_user);
  void add_user(User* new_user);
  User* get_user(string username, string password);
  User* find_user(string username, bool mention = 0);
  string make_jeek_id();
  string make_comment_id();
  string make_reply_id();
  void add_comment_to_jeek(Jeeker* my_jeeker, string jeek_id, string comment_text, string name);
  void add_jeek(Jeek* jeek);
  void like_jeek_by_id(string id, User* user_likes, bool like);
  void reply_comment_by_id(string id, string text, string name);
protected:
  vector<Comment*> all_comments;
  vector<User*> users;
  vector<Jeek*> all_jeeks;
  vector<string> id_data_base;
  User* loged_user;
};


#endif
