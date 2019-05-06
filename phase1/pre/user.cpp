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

void User::jeek_jeek(Jeeker* my_jeeker)
{
  string line;
  bool has_mention = 0;
  bool finished = 0;
  Jeek* new_jeek = new Jeek();
  while(!finished && getline(cin, line))
  {
    try
    {
      pair<string, string> info (parse_commands(line));
      if(info.first == "text")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        if((info.second).size() > MAX_TEXT_SIZE)
          throw (new Text_size_overflow);
        new_jeek->add_text(info.second);
      }
      else if(info.first == "tag")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        string jeek_tag;
        string extra_part;
        stringstream tag_line(info.second);
        tag_line >> jeek_tag;
        getline(tag_line, extra_part);
        if(!is_empty_part(extra_part))
          throw (new Bad_use_of_command);
        new_jeek->add_tag(jeek_tag);
      }
      else if(info.first == "mention")
      {
        User* mentioned_user;
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        string jeek_mention;
        string extra_part;
        stringstream mention_line(info.second);
        mention_line >> jeek_mention;
        getline(mention_line, extra_part);
        if(!is_empty_part(extra_part))
          throw (new Bad_use_of_command);
        mentioned_user = my_jeeker->find_user(jeek_mention, 1);
        if(mentioned_user != NULL && mentioned_user->get_username() == username)
          throw (new Invalid_username);
        if(mentioned_user != NULL)
          has_mention = 1;
        if(mentioned_user != NULL)
        {
          new_jeek->add_mention(mentioned_user);
        }
        else
        {
          new_jeek->add_mention(jeek_mention);
        }
      }
      else if(info.first == "publish")
      {
        if(!is_empty_part(info.second))
          throw (new Bad_use_of_command);
        finished = 1;
        new_jeek->add_name(name);
        string new_id = my_jeeker->make_jeek_id();
        new_jeek->add_id(new_id);
        my_jeeks.push_back(new_jeek);
        my_jeeker->add_jeek(new_jeek);
        notifications->make_jeek_notification(this, new_id);
        if(has_mention)
          notifications->make_mention_notification(this, new_jeek, new_id);
      }
      else if(info.first == "abort")
      {
        if(!is_empty_part(info.second))
          throw (new Bad_use_of_command);
        finished = 1;
      }
      else
      {
        throw (new Invalid_command);
      }
    }
    catch(Exception* exception)
    {
      exception->what();
    }
  }
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
