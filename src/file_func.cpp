#include "file_func.h"

void printFileByPath(std::string filepath) {
  std::cout << filepath << '\n';
   ifstream file(filepath); //taking file as inputstream
   std::string str;
   if(file) {
      std::cout << "Here" << '\n';
      ostringstream ss;
      ss << file.rdbuf(); // reading data
      str = ss.str();
   }
   cout<<str;
}
