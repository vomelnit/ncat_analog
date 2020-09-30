#ifndef CLIENT_H
# define CLIENT_H
# include <stdio.h>
# include <iostream>
# include <string.h>   //strlen
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>   //close
# include <arpa/inet.h>    //close
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

# define BUFFER_SIZE_BYTES 1025
# define MAX_CONNECTION_AMOUNT 5

typedef struct{
    int socketDescriptor;
    socklen_t AddrLen;
    struct sockaddr_in Address;
} connectSocketData;

typedef struct {
  int opt;
  int clientSocket;
  int addrlen;
  int new_socket;
  //int connectSocket[MAX_CONNECTION_AMOUNT];
  int max_conn_amount;
  int activity;
  int valread;
  int sd;
  int max_sd;
  struct sockaddr_in connAddress;
  connectSocketData connectSocket[MAX_CONNECTION_AMOUNT];
  char buffer[BUFFER_SIZE_BYTES];
  fd_set readfds;
  fd_set writefds;
  int protocolType;
  int ipVersion;

} clientStruct;

void clientActivate(int port, std::string addr, int protocol);

clientStruct initClientStruct(int port, std::string address, int protocol);

int connectSocketToServer(int ipVersion, int protocolType, struct sockaddr_in address);

#endif
