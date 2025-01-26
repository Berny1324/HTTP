//
//
// server.h
//
//

#ifndef Server_h  // if server_h is undefined, define it, avoids multiple inclusions
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Server {
   int domain;
   int protocol;
   int service;
   u_long interface;
   int port;
   int backlog;

   struct sockaddr_in address;

   int socket;

   void (*launch)(struct Server *server);
};

// function prototype, defines function with all its parameters without creating an instance, good for referencing the function without worrying about where its defined
struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*launch)(struct Server *server)); 

#endif
