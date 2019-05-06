#ifndef USER
#define USER USER

#include <iostream>
#include <vector>
#include "jeek.hpp"
#include "notification.hpp"

#define MAX_TEXT_SIZE 140

class Jeeker;
using namespace std;


class User
{
public:
  User(string username, string name, string password);
  void add_comment(Jeeker* my_jeeker, string info);
  void add_rejeeked_jeek(Jeeker* my_jeeker, Jeek* rejeeked);
  void check_duplicate_username(User* x);
  string get_username() { return username; }
  string get_name() { return name; }
  void check_password(string given_password);
  vector<string> show_user_jeeks();
  void handle_like(Jeeker* my_jeeker, string info, bool like);
  void reply_to_comment(Jeeker* my_jeeker, string info);
  void rejeek(Jeeker* my_jeeker, string info);
  void make_relation(Jeeker* my_jeeker, string info, bool ok_relation);
  void remove_user_from_followings(User* follower);
  void add_user_to_followings(User* unfollower);
  void get_notification(string notification);
  void send_notification(string notification);
  string show_notifications();
  Notification* notifications;
  string username;
  string name;
  string password;
  vector<Jeek*> my_jeeks;
  vector<User*> followings;

};


#endif
