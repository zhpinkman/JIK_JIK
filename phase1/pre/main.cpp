#include <iostream>
#include <sstream>
#include <vector>
#include "jeeker.hpp"
#include "data_base.hpp"
#include "func.hpp"

using namespace std;

int main()
{

  Data_base data_base;
  string line;
  while(getline(cin,line))
  {
    data_base.get_command(line);
  }
  return 0;
}
