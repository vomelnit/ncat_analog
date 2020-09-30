#include "client.h"

void clientActivate(int port, std::string addressStr, int protocol){
    int activity, valread;
    clientStruct client;
    client = initClientStruct(port, addressStr, protocol);
    client.clientSocket = connectSocketToServer(client.ipVersion, client.protocolType, client.connAddress);

    while(true){
            FD_ZERO(&client.readfds);
            FD_SET(0, &client.readfds);
            FD_SET(client.clientSocket, &client.readfds);
            client.max_sd = client.clientSocket;

            activity = select(client.max_sd + 1, &client.readfds, NULL, NULL, NULL);
            if (activity < 0){
                perror("Client Select:");
                exit(EXIT_FAILURE);
            }

                if (FD_ISSET(client.clientSocket, &client.readfds)){
                  valread = read( client.clientSocket , client.buffer, BUFFER_SIZE_BYTES-1);
                  if (valread == 0) {
                      close(client.clientSocket);
                      std::cout << "Host disconnected" << '\n';
                      exit(EXIT_SUCCESS);
                  }
                  if (valread>0){
                      client.buffer[valread] = '\0';
                      std::cout << client.buffer;
                  }
                }
                if (FD_ISSET(0, &client.readfds)){
                    valread = read(0 , client.buffer, BUFFER_SIZE_BYTES-1);
                    client.buffer[valread] = '\0';
                    send(client.clientSocket, client.buffer, strlen(client.buffer), 0 );
                  }
      }
}

clientStruct initClientStruct(int port, std::string addressStr, int protocol){
    clientStruct clientInit;
    clientInit.ipVersion = AF_INET;
    clientInit.connAddress.sin_family = clientInit.ipVersion;
    clientInit.connAddress.sin_addr.s_addr = inet_addr(addressStr.c_str());
    clientInit.connAddress.sin_port = htons(port);
    clientInit.addrlen = sizeof(clientInit.connAddress);

    if (protocol == 0) clientInit.protocolType = SOCK_STREAM;
    else if (protocol == 1) clientInit.protocolType = SOCK_DGRAM;
    else std::cout << "Wrong protocol" << '\n';

    return clientInit;
}

int connectSocketToServer(int ipVersion, int protocolType, struct sockaddr_in address){
    int clientSocket, connSocket;
    if ((clientSocket = socket(ipVersion, protocolType, 0)) < 0){
        perror("SocketInit:");
        exit(EXIT_FAILURE);
    }

    if (connSocket = connect(clientSocket, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("SocketConnect:");
        exit(EXIT_FAILURE);
    }
    std::cout <<"ConnSocket"<< connSocket << '\n';
    return clientSocket;
}
