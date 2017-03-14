#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>


// Fake /bin/sh string. used for first part of ROP writeup. 
const char *binsh = "/bin/sh";

void write2sock(int sock, char *str) {
        write(sock, str, strlen(str));
}


void readStrInput(int sock, int len) {
        char buffer[128];
        ssize_t ret;

        bzero(buffer, sizeof(buffer));

        dprintf(sock, "Input string: \n");
        dprintf(sock, "> ");
        fflush(stdout);
        ret = read(sock, &buffer, len);

        dprintf(sock, "I've read: %li bytes\n", ret);
}


void handleBofInput(int sock) {
        char input[16];
        int inputLen;

        dprintf(sock, "How many bytes do you want to read?\n");
        dprintf(sock, "> ");

        read(sock, input, sizeof(input) - 1);
        inputLen = atoi(input);

        if (inputLen > 0) {
                dprintf(sock, "Ok, i'll read %i bytes\n", inputLen);
                readStrInput(sock, inputLen);
        }

        dprintf(sock, "Ok, done\n");
}

void doprocessing (int sock) {
        char selection[4];
        int selectedNr = -1;
        bzero(selection, sizeof(selection));

        dprintf(sock, "Press: \n");
        dprintf(sock, "  0   To quit\n");
        dprintf(sock, "  1   To stack overflow\n");

        dprintf(sock, "> ");
        fflush(stdout);

        read(sock, selection, sizeof(selection) - 1);
        selectedNr = atoi(selection);

        switch(selectedNr) {
                case 0: return;
                case 1: return handleBofInput(sock);
                default: return;
        }
}


/* This is a dummy function. It is never called. 
   Its only use is to add some important gadgets into
   the code section.
   Because this example is of small size, the gadgets
   do not appear naturally in it. 
*/
int dummy(int argc, char *argv) {
	char x[16];
	unsigned int y; 
	unsigned int z; 
	z = 16;
	y = x[z];
	asm ("pop %rax; ret\n\t");
	asm ("syscall; ret\n\t");
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


        int enable = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
            perror("setsockopt(SO_REUSEADDR) failed");
            /* Initialize socket structure */
             bzero((char *) &serv_addr, sizeof(serv_addr));
             portno = 5002;

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

             printf("Listen on port: %i\n", portno);

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

