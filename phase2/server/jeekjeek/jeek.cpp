#include "jeek.hpp"
#include "user.hpp"
#include <iostream>
#include "comment.hpp"
#include "jeeker.hpp"
#include "exception.hpp"
#include <fstream>

using  namespace std;


Jeek::Jeek(const Jeek& jeek)
{
  text = jeek.text;
  is_a_rejeek = 1;
  for(int i = 0;i < (jeek.tags).size(); i++)
  {
    tags.push_back((jeek.tags)[i]);
  }
  for(int i = 0;i < (jeek.users_mentioned).size(); i++)
  {
    users_mentioned.push_back((jeek.users_mentioned)[i]);
  }
}

bool Jeek::check_user_status(User* user)
{
  for(int i = 0;i < users_liked.size(); i++)
  {
    if(users_liked[i]->get_username() == user->get_username())
    return 1;
  }
  return 0;
}
void Jeek::add_tag(string my_tag)
{
  tags.push_back(my_tag);
}
void Jeek::add_mention(User* mentioned_user)
{
  users_mentioned.push_back(mentioned_user);
}
void Jeek::add_mention(string mentioned_user)
{
  invalid_mentions.push_back(mentioned_user);
}
string Jeek::show_jeeks_found()
{
  string result = "";
  result += text_id + " " + name + "  ";
  cout << text_id << " " << name <<endl;
  if(is_a_rejeek)
  {
    result += " rejeeked : ";
    cout << " rejeeked :  ";
  }
  result += "</br>";
  result += text;
  cout << text << endl;
  return result;
}

string Jeek::show_jeek()
{
  string result = "";
  result += name ;
  result += "</br>";
  if(is_a_rejeek)
  {
    result += " rejeeked : </br>";
  }
  result += text ;
  result += "</br>";
  for(int i = 0;i < tags.size(); i++)
  {
    result += " #" + tags[i] ;
    result += "</br>";
  }
  for(int i = 0;i < users_mentioned.size(); i++)
  {
    result += " @" + users_mentioned[i]->get_username() ;
    result += "</br>";
  }
  for(int i = 0;i < invalid_mentions.size(); i++)
  {
    result += " @" + invalid_mentions[i] ;
    result += "</br>";
  }
  result += " Likes " + to_string(users_liked.size()) + "</br>";
  result += " Rejeeks " + to_string(users_rejeeked.size()) + "</br>";
  result += " comments : </br>";
  for(int i = 0;i < comments.size(); i++)
  {
    result +=  comments[i]->get_text() + "</br>";
  }
  cout << result << endl;
  return result;
}

bool Jeek::has_tag(string tag)
{
  for(int i = 0;i < tags.size(); i++)
  {
    if(tags[i] == tag)
      return 1;
  }
  return 0;
}


void Jeek::add_comment(Jeeker* my_jeeker, string comment_text, string name)
{
  Comment* new_comment = new Comment;
  string comment_id = my_jeeker->make_comment_id();
  new_comment->add_text(comment_text);
  new_comment->add_id(comment_id);
  new_comment->add_name(name);
  comments.push_back(new_comment);
  my_jeeker->add_comment_to_data_base(new_comment);
}

void Jeek::like_or_dislike(User* user_likes, bool like)
{
  for(int i =0;i < users_liked.size(); i++)
  {
    if(users_liked[i]->get_username() == user_likes->get_username())
    {
      if(like)
      {
        throw (new Already_liked);
      }
      else
      {
        users_liked.erase(users_liked.begin() + i);
        return;
      }
    }
  }
  if(like)
  {
    users_liked.push_back(user_likes);
  }
  else
  {
    throw (new Disliked_already);
  }
}

void Jeek::get_rejeeked(Jeeker* my_jeeker, User* rejeeker)
{
  users_rejeeked.push_back(rejeeker);
  Jeek* rejeeked = new Jeek(*this);
  rejeeked->add_name(rejeeker->get_name());
  rejeeker->add_rejeeked_jeek(my_jeeker, rejeeked);
}

void Jeek::send_mention_notification(string notification)
{
  for(int i = 0;i < users_mentioned.size(); i++)
  {
    users_mentioned[i]->get_notification(notification);
  }
}
