#include <iostream>
#include <sstream>
#include <vector>
#include "jeeker.hpp"
#include "interface.hpp"
#include "func.hpp"

using namespace std;

int main()
{

  Interface interface;
  string line;
  while(getline(cin,line))
  {
    interface.jeekjeek(line);
  }
  return 0;
}
