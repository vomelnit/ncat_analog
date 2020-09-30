#include "file_func.h"

void printFileByPath(std::string filepath) {
  std::cout << filepath << '\n';
   ifstream file(filepath); //taking file as inputstream
   std::string str;
   if(file) {
      ostringstream ss;
      ss << file.rdbuf(); // reading data
      str = ss.str();
   }
   cout<<str;
}

void printHelpCmd(){
  std::cout << "\nUsage: ncat_analog [options]\n\n\
  Options:\n\
  -u, --udp                        Use UDP instead of default TCP\n\
  -p, --port port                  Specify source port to use\n\
  -s, --source addr                Specify source address to use\n\
  -l, --listen                     Bind and listen for incoming connections\n\
  -r, --read-from-file <filename>  Transmit data from file\n\
  -w, --write-to-file  <filename>  Write received data into file\n\
  -h, --help                       Display this help screen\n" << '\n';
}
