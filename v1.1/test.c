//
//
// file for testing
//
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

void launch(struct Server *server) {
   char buffer[30000];

   const char *hello =
       "HTTP/1.1 200 OK\n"
       "Date: Mon, 27 Jan 2025, 10:00:00 CET\n"
       "Server: Apache/2.2.13 (Win32)\n"
       "Last-Modified: Wed, 27 Jan 2025 09:00:00 CET\n"
       "Content-length: 88\n"
       "Content-Type: text/html\n"
       "Connection: Closed\n"
       "\n"
       "<html><body><h1>UNGA BUNGA BUNGA UNGA</h1></body></html>";

   int address_length = sizeof(server->address);
   int new_socket;

   while (1) {
      printf("--- WAITING FOR CONNECTION ---\n");
      new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
      read(new_socket, buffer, 30000);
      printf("%s\n", buffer);
      write(new_socket, hello, strlen(hello));
      close(new_socket);
   }
}

int main() {
   struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
   server.launch(&server);
}
