#ifndef TCP_SERVER_H
# define TCP_SERVER_H

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
//# define PORT 9999
# define MAX_CLIENT_AMOUNT 5
# define BUFFER_SIZE_BYTES 1025

//! A clientSocketData struct.
/*! Consist of socket descriptor and address:port of this socket. */
typedef struct{
    int socketDescriptor;
    socklen_t clientAddrlen;
    struct sockaddr_in socketAddress;
} clientSocketData;

//! A server struct.
/*! Consist of fields that define server executions. */
typedef struct {
  int opt;
  int master_socket;
  int addrlen;
  int client_socket[MAX_CLIENT_AMOUNT];
  int max_clients;
  int max_sd;
  struct sockaddr_in address;
  char buffer[BUFFER_SIZE_BYTES];
  fd_set readfds;
  //fd_set writefds;
  int protocolType;
  int ipVersion;
  int sockLevel;
  int optname;
  clientSocketData clientSocket[MAX_CLIENT_AMOUNT];

} server;

//! Normally create server on addr:port and handle traffic using select()
/*!
  \param port an integer argument.
  \param addr a std::string.
  \param protocol an integer argument.
*/
*/
void serverActivate(int port, std::string addr, int protocol);

//! Initialized struct server's fiels
/*!
  \param port an integer argument.
  \param addr a std::string.
  \param protocol an integer argument.
  \return server structure
*/
server initServerStruct(int port, std::string address, int protocol);

//! Create socket, bind and set on listen mode and return socket descriptor
/*!
  \param ipVersion an integer argument.
  \param protocolType an integer argument.
  \param opt an integer argument.
  \param sockLevel an integer argument.
  \param optname an integer argument.
  \param address a struct sockaddr_in.
  \return integer
*/
int initSocketOnListeningMode(int ipVersion, int protocolType, int opt, int sockLevel, int optname, struct sockaddr_in address);

//! Send init message to new connected socket
/*!
  \param connectedSocket an integer argument.
  \param address a struct sockaddr_in.
*/
void printConnectionMsgs(int connectedSocket, struct sockaddr_in address);

//! Send message in buffer to all connected sockets
/*!
  \param buffer[BUFFER_SIZE_BYTES] a character argument.
  \param max_clients an integer argument.
  \param client_socket[MAX_CLIENT_AMOUNT] a struct clientSocketData.
*/
void sendBufferToAllClients(char buffer[BUFFER_SIZE_BYTES],int max_clients,clientSocketData client_socket[MAX_CLIENT_AMOUNT]);

#endif
