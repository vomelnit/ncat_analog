#include "client.h"

void clientActivate(int port, std::string addressStr, int protocol){
    int activity, valread;
    clientStruct client;
    client = initClientStruct(port, addressStr, protocol);
    client.clientSocket = connectSocketToServer(client.ipVersion, client.protocolType, client.connectSocket[0].Address);
    client.connectSocket[0].socketDescriptor = client.clientSocket;

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
            std::cout << "Server" << '\n';
            valread = read( client.clientSocket , client.buffer, BUFFER_SIZE_BYTES-1);
            if (valread == 0) {
                close(client.clientSocket);
                std::cout << "Host disconnected" << '\n';
                exit(EXIT_SUCCESS);
            }
            else if (valread>0){
            client.buffer[valread] = '\0';
            std::cout << client.buffer;
            }
            else {
              std::cout << "Read message length with negative value" << '\n';
              exit(EXIT_FAILURE);
            }
        }


        if (FD_ISSET(0, &client.readfds)){
            //std::cout << "I/O" << '\n';
            valread = read(0 , client.buffer, BUFFER_SIZE_BYTES-1);
            std::cout << "valread"<<valread << '\n';
            client.buffer[valread] = '\0';

            if (client.protocolType == SOCK_STREAM){
                // std::cout << "buffer: " << client.buffer;
                send(client.clientSocket, client.buffer, strlen(client.buffer), 0 );
            }
            else if (client.protocolType == SOCK_DGRAM){
              std::cout << "/* message */" << '\n';
                sendto(client.clientSocket, client.buffer, strlen(client.buffer),MSG_CONFIRM,
                  (const struct sockaddr *) &client.connectSocket[0].Address, client.connectSocket[0].AddrLen);
            }
        }
      }
}

clientStruct initClientStruct(int port, std::string addressStr, int protocol){
    clientStruct clientInit;
    clientInit.ipVersion = AF_INET;
    clientInit.max_conn_amount = MAX_CONNECTION_AMOUNT;

    clientInit.connectSocket[0].Address.sin_family = clientInit.ipVersion;
    clientInit.connectSocket[0].Address.sin_addr.s_addr = inet_addr(addressStr.c_str());
    clientInit.connectSocket[0].Address.sin_port = htons(port);
    clientInit.connectSocket[0].AddrLen = sizeof(clientInit.connectSocket[0].Address);

    for (int i = 0; i < clientInit.max_conn_amount; i++){
        clientInit.connectSocket[i].socketDescriptor = 0;
    }

    if (protocol == 0) clientInit.protocolType = SOCK_STREAM;
    else if (protocol == 1) clientInit.protocolType = SOCK_DGRAM;
    else std::cout << "Protocol must be SOCK_STREAM or SOCK_DGRAM" << '\n';

    return clientInit;
}

int connectSocketToServer(int ipVersion, int protocolType, struct sockaddr_in address){
    int clientSocket, connSocket;
    if ((clientSocket = socket(ipVersion, protocolType, 0)) < 0){
        perror("SocketInit:");
        exit(EXIT_FAILURE);
    }

    if (protocolType == SOCK_STREAM) {

        if (connect(clientSocket, (struct sockaddr *)&address, sizeof(address)) < 0){
            perror("SocketConnect");
            exit(EXIT_FAILURE);
        }
        return clientSocket;
    }
    else if (protocolType == SOCK_DGRAM) return clientSocket;
    else {
        std::cout << "Protocol must be SOCK_STREAM or SOCK_DGRAM" << '\n';
        exit(EXIT_FAILURE);
    }
}
