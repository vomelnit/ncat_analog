#ifndef CMD_ARGUMENT_ANALYZER_H
# define CMD_ARGUMENT_ANALYZER_H

# include <string>
# include <getopt.h>
# include <iostream>
# include "file_func.h"
  using namespace std;

  enum fileUseMode {noFile, readFromFile, writeToFile};
  enum transportProtocol {tcp, udp};



  typedef struct {
    enum transportProtocol protocol;
    std::string addr;
    int port;
    std::string filename;
    bool isListeningMode;
    enum fileUseMode fileUseMode;
  } cmdOptions;


  cmdOptions getCmdOptions(int argc,char** argv);

  cmdOptions createDefaultCmdOptionsStructure();


#endif
