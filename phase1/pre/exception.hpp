#include <iostream>
using namespace std;

class Exception
{
public:
  virtual void what() = 0;
};

class Invalid_command : public Exception
{
public:
  void what() { cout << " invalid command. " << endl; }
};
class Bad_use_of_command : public Invalid_command
{
public:
  void what() { cout << " bad use of command. " << endl; }
};

class Text_size_overflow : public Exception
{
public:
  void what() { cout << " text size overflow. " << endl; }
};

class Invalid_jeek_id : public Exception
{
public:
  void what() { cout << " invalid jeek id. " << endl; }
};

class Invalid_username : public Exception
{
public:
  void what() { cout << " invalid username. " << endl; }
};

class Invalid_comment_id : public Exception
{
public:
  void what() { cout << " invalid comment id. " << endl; }
};

class Invalid_reply_id : public Exception
{
public:
  void what() { cout << " invalid reply. " << endl; }
};

class Invalid_search_keyword : public Exception
{
public:
  void what() { cout << " invalid search keyword. " << endl; }
};

class Invalid_password : public Exception
{
public:
  void what() { cout << " invalid password. " << endl; }
};

class Duplicate_username : public Exception
{
public:
  void what() { cout << " duplicate username. " << endl; }
};

class Invalid_hashtag : public Exception
{
public:
  void what() { cout << " invalid hashtag. " << endl; }
};

class Already_liked : public Exception
{
public:
  void what() { cout << " already liked. " << endl; }
};

class Not_a_follower : public Exception
{
public:
  void what() { cout << " user is not a follower. " << endl; }
};

class Already_a_follower : public Exception
{
public:
  void what() { cout << " user is already a follower. " << endl; }
};

class Disliked_already : public Exception
{
public:
  void what() { cout << " didn't even liked the post. " << endl; }
};

class No_notifications : public Exception
{
public:
  void what() { cout << " no new notifications. " << endl; }
};
