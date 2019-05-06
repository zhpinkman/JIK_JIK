#include "interface.hpp"
#include "func.hpp"
#include "user.hpp"
#include <string>
#include "exception.hpp"
#include "notification.hpp"

Interface::Interface()
{
  jeeker = new Jeeker;
  status = COMMAND;
}
bool Interface::is_liked_by_user(string jeek_id)
{
  return jeeker->check_jeek_status(jeek_id, logedin_user);
}
void Interface::make_new_jeek()
{
  status = ON_JEEK;
  new_jeek = new Jeek();
  has_mention = 0;
}
void Interface::comment(string info)
{
  logedin_user->add_comment(jeeker, info);
}
void Interface::like(string info)
{
  logedin_user->handle_like(jeeker, info, 1);
}
void Interface::dislike(string info)
{
  logedin_user->handle_like(jeeker, info, 0);
}
void Interface::reply(string info)
{
  logedin_user->reply_to_comment(jeeker, info);
}
void Interface::rejeek(string info)
{
  logedin_user->rejeek(jeeker, info);
}
void Interface::follow(string info)
{
  logedin_user->make_relation(jeeker, info, 1);
}
void Interface::unfollow(string info)
{
  logedin_user->make_relation(jeeker, info, 0);
}
string Interface::notifications()
{
  return logedin_user->show_notifications();
}
void Interface::log_out(string info)
{
  if(!is_empty_part(info))
    throw (new Bad_use_of_command);
  status = COMMAND;
  logedin_user = NULL;
}
void Interface::handle_login(pair<string, string> info)
{
  if(info.first == "logout")
  {
    log_out(info.second);
  }
  else if(info.first == "jeek")
  {
    if(!is_empty_part(info.second))
      throw (new Bad_use_of_command);
    status = ON_JEEK;
    new_jeek = new Jeek();
    has_mention = 0;
  }
  else if(info.first == "comment")
  {
    if(is_empty_part(info.second))
      throw (new Bad_use_of_command);
    comment(info.second);
  }
  else if(info.first == "showJeek")
  {
    if(is_empty_part(info.second))
      throw (new Bad_use_of_command);
    show_jeek(info.second);
  }
  else if(info.first == "like")
  {
    if(is_empty_part(info.second))
      throw (new Bad_use_of_command);
    like(info.second);
  }
  else if(info.first == "dislike")
  {
    if(is_empty_part(info.second))
      throw (new Bad_use_of_command);
    dislike(info.second);
  }
  else if(info.first == "reply")
  {
    if(is_empty_part(info.second))
      throw (new Bad_use_of_command);
    reply(info.second);
  }
  else if(info.first == "showComment" || info.first == "showReply")
  {
    if(is_empty_part(info.second))
      throw (new Bad_use_of_command);
    show_comment(info.second);
  }
  else if(info.first == "rejeek")
  {
    if(is_empty_part(info.second))
      throw (new Bad_use_of_command);
    rejeek(info.second);
  }
  else if(info.first == "follow")
  {
    if(is_empty_part(info.second))
      throw (new Bad_use_of_command);
    follow(info.second);
  }
  else if(info.first == "unfollow")
  {
    if(is_empty_part(info.second))
      throw (new Bad_use_of_command);
    unfollow(info.second);
  }
  else if(info.first == "notifications")
  {
    if(!is_empty_part(info.second))
      throw (new Bad_use_of_command);
    notifications();
  }
  else
  {
    throw (new Invalid_command);
  }
}
void Interface::add_text(string info)
{
  if(is_empty_part(info))
    throw (new Bad_use_of_command);
  if((info).size() > MAX_TEXT_SIZE)
    throw (new Text_size_overflow);
  new_jeek->add_text(info);
}
void Interface::add_tag(string info)
{
  if(is_empty_part(info))
    throw (new Bad_use_of_command);
  string jeek_tag;
  string extra_part;
  stringstream tag_line(info);
  tag_line >> jeek_tag;
  getline(tag_line, extra_part);
  if(!is_empty_part(extra_part))
    throw (new Bad_use_of_command);
  new_jeek->add_tag(jeek_tag);
}

void Interface::add_mention(string info)
{
  User* mentioned_user;
  if(is_empty_part(info))
    throw (new Bad_use_of_command);
  string jeek_mention;
  string extra_part;
  stringstream mention_line(info);
  mention_line >> jeek_mention;
  getline(mention_line, extra_part);
  if(!is_empty_part(extra_part))
    throw (new Bad_use_of_command);
  mentioned_user = jeeker->find_user(jeek_mention, 1);
  if(mentioned_user != NULL && mentioned_user->get_username() == logedin_user->get_username())
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
void Interface::publish_jeek(string info)
{
  if(!is_empty_part(info))
    throw (new Bad_use_of_command);
  status = LOGEDIN;
  new_jeek->add_name(logedin_user->get_name());
  string new_id = jeeker->make_jeek_id();
  new_jeek->add_id(new_id);
  (logedin_user->my_jeeks).push_back(new_jeek);
  jeeker->add_jeek(new_jeek);
  (logedin_user->notifications)->make_jeek_notification(logedin_user, new_id);
  if(has_mention)
    (logedin_user->notifications)->make_mention_notification(logedin_user, new_jeek, new_id);
}
void Interface::abort_jeek(string info)
{
  if(!is_empty_part(info))
    throw (new Bad_use_of_command);
  status = LOGEDIN;
}
void Interface::handle_jeek(pair<string, string> info)
{
    if(info.first == "text")
    {
      add_text(info.second);
    }
    else if(info.first == "tag")
    {
      add_tag(info.second);
    }
    else if(info.first == "mention")
    {
      add_mention(info.second);
    }
    else if(info.first == "publish")
    {
      publish_jeek(info.second);
    }
    else if(info.first == "abort")
    {
      abort_jeek(info.second);
    }
    else
    {
      throw (new Invalid_command);
    }
}

vector<string> Interface::search(string info)
{
  return jeeker->search(info);
}
void Interface::show_comment(string info)
{
  jeeker->show_comment_by_id(info);
}
string Interface::show_jeek(string info)
{
   return jeeker->show_jeek_by_id(info);
}
void Interface::jeekjeek(string line)
{
  try
  {
    pair<string, string> info (parse_commands(line));
    if(status == COMMAND)
    {
      if(info.first == "signup")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        sign_up(info.second);
      }
      else if(info.first == "login")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        log_in(info.second);
      }
      else if(info.first == "search")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        search(info.second);
      }
      else if(info.first == "showComment")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        show_comment(info.second);
      }
      else if(info.first == "showJeek")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        show_jeek(info.second);
      }
      else
      {
        throw (new Invalid_command);
      }
    }
    else if(status == LOGEDIN)
    {
      handle_login(info);
    }
    else if(status == ON_JEEK)
    {
      handle_jeek(info);
    }
  }


  catch (Exception* exception)
  {
    exception->what();
  }
}

void Interface::sign_up(string info)
{
  jeeker->handle_signup(info);
}


void Interface::log_in(string info)
{
  jeeker->handle_login(this, info);
}
