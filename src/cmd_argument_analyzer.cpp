
#include "cmd_argument_analyzer.h"
#include "file_func.h"
#include <stdio.h>
#include <stdlib.h>


cmdOptions getCmdOptions(int argc,char** argv){
  cmdOptions cmdOpt;
  cmdOpt = createDefaultCmdOptionsStructure();
  //std::string helpFileResolPath ("../resources/help.txt");
  const char* short_options = "us:p:lr:w:h";

	const struct option long_options[] = {
		{"udp",no_argument, NULL,'u'},
    {"source",required_argument, NULL, 's'},
    {"port",required_argument, NULL, 'p'},
    {"listen",no_argument, NULL, 'l'},
		{"read-from-file", required_argument, NULL, 'r'},
    {"write-to-file", required_argument, NULL, 'w'},
    {"help", no_argument, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};

	int optResult;
	int option_index;
	while ((optResult=getopt_long(argc,argv,short_options,
		long_options,&option_index))!=-1){

		switch(optResult){
      case 'u': {
        std::cout << "--udp" << '\n';
				cmdOpt.protocol = udp;
				break;
			};

      case 'l': {
        std::cout << "--listen" << '\n';
				cmdOpt.isListeningMode = true;
				break;
			};

			case 'p': {
				if (optarg!=NULL)
					cmdOpt.port =  atoi(optarg);
				else
					printf("After --port option must be port number.\n");
				break;
			};

      case 's': {
				if (optarg!=NULL)
					cmdOpt.addr = optarg;
				else
					printf("After --source option must be address.\n");
				break;
			};

      case 'r': {
				if (optarg!=NULL){
					cmdOpt.fileUseMode = readFromFile;
          cmdOpt.filename = optarg;
        }
				else
					printf("After --read-from-file option must name of file.\n");
				break;
			};

      case 'w': {
				if (optarg!=NULL){
					cmdOpt.fileUseMode = writeToFile;
          cmdOpt.filename = optarg;
        }
				else
					printf("After --write-to-file option must name of file.\n");
				break;
			};

      case 'h': {
        std::cout << "--help" << '\n';
        printHelpCmd();
        //printFileByPath(helpFileResolPath);
        exit(EXIT_SUCCESS);
				break;
			};

			case '?': default:{
				printf("Unknown option was found.\n");
				break;
			};
		};

	};
  return cmdOpt;
}


cmdOptions createDefaultCmdOptionsStructure(){
  cmdOptions defaultCmdOpt;
  defaultCmdOpt.protocol = tcp;
  defaultCmdOpt.addr = "127.0.0.1";
  defaultCmdOpt.port = 0;
  defaultCmdOpt.filename = "";
  defaultCmdOpt.isListeningMode = true;
  defaultCmdOpt.fileUseMode = noFile;

  return defaultCmdOpt;
}
