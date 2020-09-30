//#include <iostream>
#include "cmd_argument_analyzer.h"
#include "tcp_server.h"
#include "client.h"
using namespace std;


int main(int argc, char** argv)
{
    cmdOptions cmdOpt;
    cmdOpt = getCmdOptions(argc, argv);

    if (cmdOpt.isListeningMode == true) serverActivate(cmdOpt.port, cmdOpt.addr, cmdOpt.protocol);
    else if (cmdOpt.isListeningMode == false) clientActivate(cmdOpt.port, cmdOpt.addr, cmdOpt.protocol);
    else cout<<"Wrong ListeningMode entered\n";
    return 0;
}
