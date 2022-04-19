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


int checkPassword(char *password) {
   char *adminHash = "$6$saaaaalty$cjw9qyAKmchl7kQMJxE5c1mHN0cXxfQNjs4EhcyULLndQR1wXslGCaZrJj5xRRBeflfvmpoIVv6Vs7ZOQwhcx.";
   char *hash = crypt(password, "$6$saaaaalty");
   if (strcmp(hash, adminHash) == 0) {
      return 1;
   } else {
      return 0;
   }
}

int handleData(char *username, char *password) {
   int isAdmin = 0;
   char name[128];

   isAdmin = checkPassword(password);
   strcpy(name, username);

   if(isAdmin > 0) {
      return 1;
   } else {
      return 0;
   }
}

void handleClient (int socket) {
   char username[1024];
   char password[1024];

   bzero(username, sizeof(username));
   bzero(password, sizeof(password));

   write(socket, "Username: ", 10);
   read(socket, username, 1023);

   write(socket, "Password: ", 10);
   read(socket, password, 1023);

   int ret = handleData(username, password);
   if (ret) {
      write(socket, "You are admin", 13);
   } else {
      write(socket, "Not admin.", 10);
   }
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

   int serverSocket = makeServer(5001);
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



