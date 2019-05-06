#ifndef DATA_BASE
#define DATA_BASE DATA_BASE

#include <iostream>
#include <sstream>
#include <vector>
#include "jeeker.hpp"
class User;

using namespace std;


class Data_base
{
public:
  Data_base();
  void get_command(string line);
  void sign_up(string info);
  void log_in(string info);
  void handle_user(User* loged_user);
protected:
  Jeeker* jeeker;
};
#endif
