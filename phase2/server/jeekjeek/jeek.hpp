#ifndef JEEK
#define JEEK JEEK


#include "comment.hpp"
#include <vector>

using namespace std;

class User;
class Jeeker;

class Jeek : public Text
{
public:
  bool check_user_status(User* user);
  Jeek() { is_a_rejeek = 0; }
  Jeek(const Jeek& jeek);
  void get_rejeeked(Jeeker* my_jeeker, User* rejeeker);
  string show_jeek();
  void add_comment(Jeeker* my_jeeker, string comment_text, string name);
  bool has_tag(string tag);
  void add_mention(User* mentioned_user);
  void add_mention(string mentioned_user);
  void add_tag(string my_tag);
  string show_jeeks_found();
  void like_or_dislike(User* user_likes, bool like);
  void send_mention_notification(string notification);
protected:
  bool is_a_rejeek;
  vector<string> invalid_mentions;
  vector<User*> users_mentioned;
  vector<User*> users_rejeeked;
  vector<string> tags;
  vector<Comment*> comments;
};


#endif
