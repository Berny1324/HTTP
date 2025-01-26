//
// server.c 
//

#include "server.h"
#include <stdio.h> // include here, so you dont import this when importing server.h
#include <stdlib.h>
#include <sys/socket.h>


// create a server object with all parameters, return it to caller
struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*launch)(struct Server *server)) {

   struct Server server; // define server object

   server.domain = domain;
   server.service = service;
   server.protocol = protocol;
   server.interface = interface;
   server.port = port;
   server.backlog = backlog;

   server.address.sin_family = domain; // socket IP addr
   server.address.sin_port = htons(port); // convert integer port into bytes referring to a network port, for little Endian (byte reverse), s = short
   server.address.sin_addr.s_addr = htonl(interface); // same, l = long

   server.socket = socket(domain, service, protocol);

   if (server.socket == 0) {
      perror("failed to connect to socket\n");
      exit(1);
   }

   if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0) { // returns negative value in case of fail
      perror("failed to bind socket\n");
      exit(1);
   } // assigns the address specified by addr, second arg tells the function to treat server.address as a struct sockaddr*

   if (listen(server.socket, server.backlog) < 0) { // returns negative value in case of fail
      perror("failed to start listening\n");
      exit(1);
   }// backlog = a queue, we can only hand out one piece of information at a time
   
   server.launch = launch;

   return server;
} 
