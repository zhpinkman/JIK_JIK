#include "data_base.hpp"
#include "func.hpp"
#include "user.hpp"
#include <string>
#include "exception.hpp"

Data_base::Data_base()
{
  jeeker = new Jeeker;
}
void Data_base::get_command(string line)
{
  try
  {
    pair<string, string> info (parse_commands(line));
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
      jeeker->search(info.second);
    }
    else if(info.first == "showComment")
    {
      if(is_empty_part(info.second))
        throw (new Bad_use_of_command);
      jeeker->show_comment_by_id(info.second);
    }
    else if(info.first == "showJeek")
    {
      if(is_empty_part(info.second))
        throw (new Bad_use_of_command);
      jeeker->show_jeek_by_id(info.second);
    }
    else
    {
      throw (new Invalid_command);
    }
  }
  catch (Exception* exception)
  {
    exception->what();
  }
}

void Data_base::sign_up(string info)
{
  jeeker->handle_signup(info);
}


void Data_base::log_in(string info)
{
  jeeker->handle_login(this, info);
}

void Data_base::handle_user(User* loged_user)
{
  string line;
  while(getline(cin, line))
  {
    try
    {
      pair<string, string> info (parse_commands(line));
      if(info.first == "logout")
      {
        if(!is_empty_part(info.second))
          throw (new Bad_use_of_command);
        break;
      }
      else if(info.first == "jeek")
      {
        if(!is_empty_part(info.second))
          throw (new Bad_use_of_command);
        loged_user->jeek_jeek(jeeker);
      }
      else if(info.first == "search")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        jeeker->search(info.second);
      }
      else if(info.first == "comment")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        loged_user->add_comment(jeeker, info.second);
      }
      else if(info.first == "showJeek")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        jeeker->show_jeek_by_id(info.second);
      }
      else if(info.first == "like")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        loged_user->handle_like(jeeker, info.second, 1);
      }
      else if(info.first == "dislike")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        loged_user->handle_like(jeeker, info.second, 0);
      }
      else if(info.first == "reply")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        loged_user->reply_to_comment(jeeker, info.second);
      }
      else if(info.first == "showComment" || info.first == "showReply")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        jeeker->show_comment_by_id(info.second);
      }
      else if(info.first == "rejeek")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        loged_user->rejeek(jeeker, info.second);
      }
      else if(info.first == "follow")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        loged_user->make_relation(jeeker, info.second, 1);
      }
      else if(info.first == "unfollow")
      {
        if(is_empty_part(info.second))
          throw (new Bad_use_of_command);
        loged_user->make_relation(jeeker, info.second, 0);
      }
      else if(info.first == "notifications")
      {
        if(!is_empty_part(info.second))
          throw (new Bad_use_of_command);
        loged_user->show_notifications();
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
