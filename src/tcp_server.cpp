#include "tcp_server.h"

void serverActivate(int port, std::string addr, int protocol){
    server serverStruct;
    serverStruct = initServerStruct(port, addr, protocol);
    int valread, activity, new_socket, currentSocket;

    serverStruct.master_socket = initSocketOnListeningMode(serverStruct.ipVersion,
    serverStruct.protocolType, serverStruct.opt, serverStruct.sockLevel, serverStruct.optname, serverStruct.address);

    while(true){
        FD_ZERO(&serverStruct.readfds);
        FD_SET(0, &serverStruct.readfds);
        FD_SET(serverStruct.master_socket, &serverStruct.readfds);
        serverStruct.max_sd = serverStruct.master_socket;

        for (int i = 0 ; i < serverStruct.max_clients ; i++){
            currentSocket = serverStruct.client_socket[i];
            if(currentSocket > 0)
                FD_SET( currentSocket , &serverStruct.readfds);
            if(currentSocket > serverStruct.max_sd)
                serverStruct.max_sd = currentSocket;
        }

        activity = select( serverStruct.max_sd + 1 , &serverStruct.readfds , NULL , NULL , NULL);
        if ((activity < 0) && (errno!=EINTR)){
            printf("select error");
        }

        if (FD_ISSET(serverStruct.master_socket, &serverStruct.readfds)){
            if ((new_socket = accept(serverStruct.master_socket,
              (struct sockaddr *)&serverStruct.address, (socklen_t*)&serverStruct.addrlen))<0){
                perror("accept");
                exit(EXIT_FAILURE);
            }

            printConnectionMsgs(new_socket,serverStruct.address);

            for (int i = 0; i < serverStruct.max_clients; i++){
                if( serverStruct.client_socket[i] == 0 ){
                    serverStruct.client_socket[i] = new_socket;
                    break;
                }
            }
        }

        for (int i = 0; i < serverStruct.max_clients; i++){
            currentSocket = serverStruct.client_socket[i];
            if (FD_ISSET( currentSocket , &serverStruct.readfds)){
                if ((valread = read( currentSocket , serverStruct.buffer, BUFFER_SIZE_BYTES-1)) == 0){
                    getpeername(currentSocket , (struct sockaddr*)&serverStruct.address ,
                      (socklen_t*)&serverStruct.addrlen);
                    std::cout<<"Host disconnected , ip "<<inet_ntoa(serverStruct.address.sin_addr)<<
                      " , port "<<ntohs(serverStruct.address.sin_port)<<'\n';

                    close( currentSocket );
                    serverStruct.client_socket[i] = 0;
                }
                else{
                    serverStruct.buffer[valread] = '\0';
                    if (currentSocket == 0) {
                        sendBufferToAllClients(serverStruct.buffer,serverStruct.max_clients,serverStruct.client_socket);
                    }
                    else std::cout << serverStruct.buffer;

                }
            }
        }
      }


}

server initServerStruct(int port, std::string addressStr, int protocol){
    server serverInitStruct;
    serverInitStruct.opt = TRUE;
    serverInitStruct.max_clients = MAX_CLIENT_AMOUNT;
    serverInitStruct.ipVersion = AF_INET;
    serverInitStruct.sockLevel = SOL_SOCKET;
    serverInitStruct.optname = SO_REUSEADDR;

    serverInitStruct.address.sin_family = serverInitStruct.ipVersion;
    serverInitStruct.address.sin_addr.s_addr = inet_addr(addressStr.c_str());
    serverInitStruct.address.sin_port = htons(port);
    serverInitStruct.addrlen = sizeof(serverInitStruct.address);

    for (int i = 0; i < serverInitStruct.max_clients; i++){
        serverInitStruct.client_socket[i] = 0;
    }

    if (protocol == 0) serverInitStruct.protocolType = SOCK_STREAM;
    else if (protocol == 1) serverInitStruct.protocolType = SOCK_DGRAM;
    else {
        std::cout << "Protocol must be SOCK_STREAM or SOCK_DGRAM" << '\n';
        exit(EXIT_FAILURE);
    }
    return serverInitStruct;
}

int initSocketOnListeningMode(int ipVersion, int protocolType, int opt, int sockLevel, int optname, struct sockaddr_in address){
    int master_socket;

    if( (master_socket = socket(ipVersion , protocolType , 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if( setsockopt(master_socket, sockLevel, optname, (char *)&opt, sizeof(opt)) < 0 ){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(master_socket, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return master_socket;
}

void printConnectionMsgs(int connectedSocket,struct sockaddr_in address){
    char *connectionMsg = "Connected to ncat_analog listening port\r\n\n";
    std::cout<<"New connection , socket fd is "<<connectedSocket<<
      " , ip is : "<<inet_ntoa(address.sin_addr)<<
      " , port : "<<ntohs(address.sin_port)<<"\n\n";

    if( send(connectedSocket, connectionMsg, strlen(connectionMsg), 0) != strlen(connectionMsg) ){
        perror("send");
    }
}

void sendBufferToAllClients(char buffer[BUFFER_SIZE_BYTES],int max_clients,int client_socket[MAX_CLIENT_AMOUNT]){
    for (int i = 0; i < max_clients; i++){
        if (client_socket[i]!=0){
            send(client_socket[i] , buffer , strlen(buffer) , 0 );
        }
    }
}
