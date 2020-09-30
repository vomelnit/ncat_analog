//#include <iostream>
#include "cmd_argument_analyzer.h"
#include "server.h"
#include "client.h"
using namespace std;


int main(int argc, char** argv)
{
    cmdOptions cmdOpt;
    cmdOpt = getCmdOptions(argc, argv);

    // std::cout << "cmdOptions structure" << '\n';
    // std::cout <<"Port: " <<cmdOpt.port << '\n';
    // std::cout <<"isListeningMode: " << cmdOpt.isListeningMode << '\n';
    // std::cout <<"protocol: " << cmdOpt.protocol << '\n';
    // std::cout <<"addr: " << cmdOpt.addr << '\n';
    // std::cout <<"fileUseMode: " << cmdOpt.fileUseMode << '\n';
    // std::cout <<"filename: " << cmdOpt.filename << '\n';
    if (cmdOpt.isListeningMode == true) serverActivate(cmdOpt.port, cmdOpt.addr, cmdOpt.protocol);
    else if (cmdOpt.isListeningMode == false) clientActivate(cmdOpt.port, cmdOpt.addr, cmdOpt.protocol);
    else cout<<"Wrong ListeningMode\n";
    return 0;
}
