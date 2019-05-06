#ifndef COMMENT
#define COMMENT COMMENT

#include "text.hpp"

class Jeeker;

class Comment : public Text
{
public:
  void show_comment();
  void reply_comment(Jeeker* my_jeeker, string text, string name);
protected:
  vector<Comment*> replies;
};


#endif
