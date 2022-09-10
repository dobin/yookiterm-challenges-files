#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>


void handleClient (int socket) {
   char data[1024];
   int ret = 0;

   bzero(data, sizeof(data));
   write(socket, "Data: ", 6);

   ret = read(socket, data, 2048); // reads up to 2048 bytes into a 1024 buffer
   printf("I've read %i bytes\n", ret);
}


int makeServer(int portno) {
   int sockfd, newsockfd, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;

   signal(SIGCHLD, SIG_IGN);

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   if (listen(sockfd, 5) < 0) {
      perror("ERROR on listen");
      exit(1);
   }

   return sockfd;
}


int main( int argc, char *argv[] ) {
   struct sockaddr_in cli_addr;
   int clilen = sizeof(cli_addr);
   int port = 5001;

   printf("Starting server on port: %i\n", port);
   int serverSocket = makeServer(port);
   while (1) {
      int newsockfd = accept(serverSocket, (struct sockaddr *) &cli_addr, &clilen);
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      printf("Client connected\n");

      int pid = fork();
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      if (pid == 0) {
         /* This is the client process */
         close(serverSocket);
         handleClient(newsockfd);
         exit(0);
      } else {
         close(newsockfd);
      }
   }
}
