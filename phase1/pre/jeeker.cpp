#include "jeeker.hpp"
#include "data_base.hpp"
#include "user.hpp"
#include "jeek.hpp"
#include <string>
#include <sstream>
#include "func.hpp"
#include "exception.hpp"

void Jeeker::handle_login(Data_base* data_base, string info)
{
  stringstream from_line(info);
  string command_part;
  vector<string> parts;
  for(int i = 0;i < 2; i ++)
  {
    command_part = "";
    from_line >> command_part;
    if(is_empty_part(command_part))
      throw (new Invalid_command);
    parts.push_back(command_part);
  }
  User* loged_user = this->get_user(parts[0], parts[1]);
  data_base->handle_user(loged_user);
}
void Jeeker::handle_signup(string info)
{
  stringstream from_line(info);
  string command_part = "";
  vector<string> parts;
  for(int i = 0;i < 3; i ++)
  {
    command_part = "";
    from_line >> command_part;
    if(is_empty_part(command_part))
      throw (new Invalid_command);
    parts.push_back(command_part);
  }
  User* new_user = new User(parts[0], parts[1], parts[2]);
  this->check_invalid_user(new_user);
  this->add_user(new_user);
}
void Jeeker::check_invalid_user(User* new_user)
{
  for(int i = 0;i < users.size(); i++)
  {
    users[i]->check_duplicate_username(new_user);
  }
}
void Jeeker::add_user(User* new_user)
{
  users.push_back(new_user);
}

User* Jeeker::get_user(string username, string password)
{
  for(int i = 0;i < users.size(); i++)
  {
    if(users[i]->get_username() == username)
    {
      users[i]->check_password(password);
      return users[i];
    }
  }
  throw (new Invalid_username);
}

User* Jeeker::find_user(string username, bool mention)
{
  for(int i = 0;i < users.size(); i++)
  {
    if(users[i]->get_username() == username)
    {
      return users[i];
    }
  }
  if(mention)
    return NULL;
  throw (new Invalid_username);
}

string Jeeker::make_jeek_id()
{
  string id;
  for(int i = id_data_base.size() - 1; i >= 0; i--)
  {
    if(id_data_base[i][0] == 'J')
    {
      string number_part = id_data_base[i].substr(1,id_data_base[i].size());
      int int_id = stoi(number_part);
      int_id++;
      id = "J" + to_string(int_id);
      id_data_base.push_back(id);
      return id;
    }
  }
  id = "J0";
  id_data_base.push_back(id);
  return id;
}
string Jeeker::make_reply_id()
{
  string id;
  for(int i = id_data_base.size() - 1; i >= 0; i--)
  {
    if(id_data_base[i][0] == 'R')
    {
      string number_part = id_data_base[i].substr(1,id_data_base[i].size());
      int int_id = stoi(number_part);
      int_id++;
      id = "R" + to_string(int_id);
      id_data_base.push_back(id);
      return id;
    }
  }
  id = "R0";
  id_data_base.push_back(id);
  return id;
}
string Jeeker::make_comment_id()
{
  string id;
  for(int i = id_data_base.size() - 1; i >= 0; i--)
  {
    if(id_data_base[i][0] == 'C')
    {
      string number_part = id_data_base[i].substr(1,id_data_base[i].size());
      int int_id = stoi(number_part);
      int_id++;
      id = "C" + to_string(int_id);
      id_data_base.push_back(id);
      return id;
    }
  }
  id = "C0";
  id_data_base.push_back(id);
  return id;
}

void Jeeker::add_jeek(Jeek* jeek)
{
  all_jeeks.push_back(jeek);
}


void Jeeker::show_hashtag(string hashtag)
{
  for(int i = 0;i < all_jeeks.size(); i++ )
  {
    if(all_jeeks[i]->has_tag(hashtag))
    {
      all_jeeks[i]->show_jeeks_found();
      return;
    }
  }
  throw (new Invalid_hashtag);
}

void Jeeker::add_comment_to_jeek(Jeeker* my_jeeker, string jeek_id, string comment_text, string name)
{
  for(int i = 0;i < all_jeeks.size(); i++)
  {
    if(all_jeeks[i]->get_id() == jeek_id)
    {
      all_jeeks[i]->add_comment(my_jeeker, comment_text, name);
      return;
    }
  }
  throw (new Invalid_jeek_id);
}
void Jeeker::add_reply_to_data_base(Comment* reply)
{
  all_comments.push_back(reply);
}
void Jeeker::add_comment_to_data_base(Comment* new_comment)
{
  all_comments.push_back(new_comment);
}



void Jeeker::show_comment_by_id(string info)
{
  string id = "";
  string extra_part = "";
  stringstream show_comment_line(info);
  show_comment_line >> id;
  getline(show_comment_line, extra_part);
  if(!is_empty_part(extra_part))
    throw (new Bad_use_of_command);
  for(int i = 0;i < all_comments.size(); i++)
  {
    if(all_comments[i]->get_id() == id)
    {
      all_comments[i]->show_comment();
      return;
    }
  }
  throw (new Invalid_comment_id);
}
void Jeeker::show_jeek_by_id(string info)
{
  string id;
  string extra_part;
  stringstream show_info(info);
  show_info >> id;
  getline(show_info, extra_part);
  if(!is_empty_part(extra_part))
    throw (new Bad_use_of_command);
  for(int i = 0 ;i < all_jeeks.size(); i++)
  {
    if(all_jeeks[i]->get_id() == id)
    {
      all_jeeks[i]->show_jeek();
      return;
    }
  }
  throw (new Invalid_jeek_id);
}

void Jeeker::like_jeek_by_id(string id, User* user_likes, bool like)
{
  for(int i = 0;i < all_jeeks.size(); i++)
  {
    if(all_jeeks[i]->get_id() == id)
    {
      all_jeeks[i]->like_or_dislike(user_likes, like);
      return;
    }
  }
  throw (new Invalid_jeek_id);
}


void Jeeker::reply_comment_by_id(string id, string text, string name)
{
  for(int i = 0;i < all_comments.size(); i++)
  {
    if(all_comments[i]->get_id() == id)
    {
      all_comments[i]->reply_comment(this, text, name);
      return;
    }
  }
  throw (new Invalid_comment_id);
}


void Jeeker::search(string info)
{
  string extra_part = "";
  stringstream search_line(info);
  string searched_info;
  search_line >> searched_info;
  getline(search_line, extra_part);
  if(!is_empty_part(extra_part))
    throw (new Bad_use_of_command);
  if(searched_info[0] == '@')
  {
    searched_info = searched_info.substr(1,searched_info.size());
    User* found_user = find_user(searched_info);
    found_user->show_user_jeeks();
  }
  else if(searched_info[0] == '#')
  {
    searched_info = searched_info.substr(1,searched_info.size());
    show_hashtag(searched_info);
  }
  else
  {
    throw (new Bad_use_of_command);
  }
}


void Jeeker::rejeek_by_id(User* rejeeker, string jeek_id)
{
  int num_of_jeeks = all_jeeks.size();
  for(int i = 0;i < num_of_jeeks; i++)
  {
    if(all_jeeks[i]->get_id() == jeek_id)
    {
      all_jeeks[i]->get_rejeeked(this, rejeeker);
      return;
    }
  }
  throw (new Invalid_jeek_id);
}
