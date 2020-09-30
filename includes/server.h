#ifndef SERVER_H
# define SERVER_H

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

# define TRUE   1
# define FALSE  0
# define PORT 9999
# define MAX_CLIENT_AMOUNT 5
# define BUFFER_SIZE_BYTES 1025

typedef struct {
  int opt;
  int master_socket;
  int addrlen;
  int new_socket;
  int client_socket[MAX_CLIENT_AMOUNT];
  int max_clients;
  int activity;
  int valread;
  int sd;
  int max_sd;
  struct sockaddr_in address;
  char buffer[BUFFER_SIZE_BYTES];
  fd_set readfds;
  fd_set writefds;
  int protocolType;
  int ipVersion;
  int sockLevel;
  int optname;

} server;

void serverActivation(int port, std::string addr, int protocol);

server initServerStruct(int port, std::string address, int protocol);

int initSocketOnListeningMode(int ipVersion, int protocolType, int opt, int sockLevel, int optname, struct sockaddr_in address);

void printConnectionMsgs(int connectedSocket, struct sockaddr_in address);

void sendBufferToAllClients(char buffer[BUFFER_SIZE_BYTES],int max_clients,int client_socket[MAX_CLIENT_AMOUNT]);

#endif
