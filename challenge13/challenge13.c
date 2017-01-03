#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

// Start, it will listen on :5001
// ./challenge5

// Exploit:
// python bof5.py | nc localhost 5001

// Access shell:
// nc localhost 4444


// hash of: "ourteacheristehbest"
const char *adminHash = "$6$saaaaalty$cjw9qyAKmchl7kQMJxE5c1mHN0cXxfQNjs4EhcyULLndQR1wXslGCaZrJj5xRRBeflfvmpoIVv6Vs7ZOQwhcx.";


int checkPassword(char *password) {
	char *hash;

	// $6$ is SHA256
	hash = crypt(password, "$6$saaaaalty");

	if (strcmp(hash, adminHash) == 0) {
		return 1;
	} else {
		return 0;
	}
}



void handleData(char *username, char *password) {
	int isAdmin = 0;
	char firstname[256];

	isAdmin = checkPassword(password);
	strcpy(firstname, username);

	if(isAdmin > 0) {
		printf("You ARE admin!\nBe the force with you.\nisAdmin: 0x%x\n", isAdmin);
	} else {
		printf("You are not admin.\nLame.\n");
	}
}

void doprocessing (int sock) {
	char username[1024];
	char password[1024];

	printf("Client connected\n");

	bzero(username, sizeof(username));
	bzero(password, sizeof(password));

	int n;

	n = read(sock, username, 1023);
	//n = read(sock, password, 1023);

	printf("Username: %s\n", username);
	//printf("Password: %s\n", password);

	handleData(username, password);
}


int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
   /* Now start listening for the clients, here
      * process will go in sleep mode and will wait
      * for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   while (1) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
  /* Create child process */
      pid = fork();
		
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         /* This is the client process */
         close(sockfd);
         doprocessing(newsockfd);
         exit(0);
      }
      else {
         close(newsockfd);
      }
		
   } /* end of while */
}



