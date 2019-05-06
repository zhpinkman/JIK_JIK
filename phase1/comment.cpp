#include "comment.hpp"
#include <iostream>
#include "jeeker.hpp"
using namespace std;

void Comment::show_comment()
{
  cout << name << endl;
  cout << text << endl;
  cout << "Replies :" << endl;
  for(int i = 0;i < replies.size(); i++)
  {
    cout << "reply  "<< replies[i]->get_id() << endl;
  }
}

void Comment::reply_comment(Jeeker* my_jeeker, string text, string name)
{
  Comment* reply = new Comment;
  string reply_id = my_jeeker->make_reply_id();
  reply->add_text(text);
  reply->add_id(reply_id);
  reply->add_name(name);
  replies.push_back(reply);
  my_jeeker->add_reply_to_data_base(reply);
}
