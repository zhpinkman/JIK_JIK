#include "func.hpp"
pair<string, string> parse_commands(string line)
{
  string command_part;
  string other_part;
  stringstream from_line(line);
  from_line >> command_part;
  getline(from_line, other_part);
  pair<string, string> info (command_part, other_part);
  return info;
}

bool is_empty_part(string extra_part)
{
  string empty = "";
  stringstream ss(extra_part);
  ss >> empty;
  if(empty == "")
    return 1;
  else
    return 0;
}
