#ifndef CMD_ARGUMENT_ANALYZER_H
# define CMD_ARGUMENT_ANALYZER_H

# include <string>
# include <getopt.h>
# include <iostream>
# include "file_func.h"
  using namespace std;

  enum fileUseMode {noFile, readFromFile, writeToFile};
  enum transportProtocol {tcp, udp};


  //! A cmdOptions struct.
  /*! Consist of flags and variables entered via cmd. */
  typedef struct {
    enum transportProtocol protocol;
    std::string addr;
    int port;
    std::string filename;
    bool isListeningMode;
    enum fileUseMode fileUseMode;
  } cmdOptions;

  //! Using getopt_long() it set flags and return cmdOptions structure to
  /*! indicate which connection need to be establish
  /*!
    \param argc an integer argument.
    \param argv a double character pointer.
    \return cmdOptions structure
  */
  cmdOptions getCmdOptions(int argc,char** argv);

  //! It set required struct fields at default values
  /*!
    \return cmdOptions structure
  */
  cmdOptions createDefaultCmdOptionsStructure();


#endif
