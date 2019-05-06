#include "user.hpp"
#include "func.hpp"
#include "jeeker.hpp"
#include "exception.hpp"
#include "notification.hpp"
#include <sstream>

User::User(string _username, string _name, string _password)
{
  notifications = new Notification;
  username = _username;
  name = _name;
  password = _password;
}

void User::check_duplicate_username(User* x)
{
  if(username == x->username)
    throw (new Duplicate_username);
}
void User::check_password(string given_password)
{
  if(password != given_password)
    throw (new Invalid_password);
}
void User::show_user_jeeks()
{
  for(int i = 0;i < my_jeeks.size(); i++)
  {
    my_jeeks[i]->show_jeeks_found();
  }
}
void User::add_comment(Jeeker* my_jeeker, string info)
{
  string jeek_id;
  string comment_text;
  stringstream comment_line(info);
  comment_line >> jeek_id;
  getline(comment_line, comment_text);
  if(is_empty_part(comment_text))
    throw (new Bad_use_of_command);
  my_jeeker->add_comment_to_jeek(my_jeeker, jeek_id, comment_text, name);
  notifications->make_comment_notification(this, jeek_id);
}
void User::handle_like(Jeeker* my_jeeker, string info, bool like)
{
  string id = "";
  string extra_part = "";
  stringstream like_line(info);
  like_line >> id;
  getline(like_line, extra_part);
  if(!is_empty_part(extra_part))
    throw (new Bad_use_of_command);
  my_jeeker->like_jeek_by_id(id, this, like);
  notifications->make_like_notification(this, id, like);
}

void User::show_notifications()
{
  notifications->show();
}
void User::send_notification(string notification)
{
  for(int i = 0;i < followings.size() ; i++)
  {
    followings[i]->get_notification(notification);
  }
}
void User::get_notification(string notification)
{
  notifications->add_to_notifications(notification);
}
void User::reply_to_comment(Jeeker* my_jeeker, string info)
{
  string id = "";
  string text_part = "";
  stringstream reply_line(info);
  reply_line >> id;
  getline(reply_line, text_part);
  if(is_empty_part(text_part))
    throw (new Bad_use_of_command);
  my_jeeker->reply_comment_by_id(id, text_part, this->name);
  notifications->make_reply_notification(this, id);
}
void User::rejeek(Jeeker* my_jeeker, string info)
{
  string jeek_id = "";
  string extra_part = "";
  stringstream rejeek_line(info);
  rejeek_line >> jeek_id;
  getline(rejeek_line, extra_part);
  if(!is_empty_part(extra_part))
    throw (new Bad_use_of_command);
  my_jeeker->rejeek_by_id(this, jeek_id);
  notifications->make_rejeek_notification(this, jeek_id);
}

void User::add_rejeeked_jeek(Jeeker* my_jeeker, Jeek* rejeeked)
{
  string new_id = my_jeeker->make_jeek_id();
  rejeeked->add_id(new_id);
  my_jeeks.push_back(rejeeked);
  my_jeeker->add_jeek(rejeeked);
}


void User::make_relation(Jeeker* my_jeeker, string info, bool ok_relation)
{
  string username = "";
  string extra_part = "";
  stringstream relation_line(info);
  relation_line >> username;
  getline(relation_line, extra_part);
  if(!is_empty_part(extra_part))
    throw (new Bad_use_of_command);
  User* specified_user = my_jeeker->find_user(username);
  if(this->username == specified_user->username)
    throw (new Invalid_username);
  if(ok_relation)
    specified_user->add_user_to_followings(this);
  else
    specified_user->remove_user_from_followings(this);
}

void User::add_user_to_followings(User* not_a_follower)
{
  for(int i = 0;i < followings.size(); i++)
  {
    if(followings[i]->username == not_a_follower->username)
      throw (new Already_a_follower);
  }
  followings.push_back(not_a_follower);
}
void User::remove_user_from_followings(User* follower)
{
  for(int i = 0;i < followings.size(); i++)
  {
    if(followings[i]->username == follower->username)
    {
      followings.erase(followings.begin() + i);
      return;
    }
  }
  throw (new Not_a_follower);
}
