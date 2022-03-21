#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>

const char *adminHash = "$6$saaaaalty$cjw9qyAKmchl7kQMJxE5c1mHN0cXxfQNjs4EhcyULLndQR1wXslGCaZrJj5xRRBeflfvmpoIVv6Vs7ZOQwhcx.";

int checkPassword(char *password) {
    char *hash = crypt(password, "$6$saaaaalty");
    if (strcmp(hash, adminHash) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void handleData(char *username, char *password) {
    int isAdmin = 0;
    char name[64];
    memset(name, 'X', 64);
    
    isAdmin = checkPassword(password);
    strcpy(name, username);

    if(isAdmin > 0) {
        printf("You are admin!\nisAdmin: 0x%x\n", isAdmin);
    } else {
        printf("You are not admin.\nisAdmin: 0x%x\n", isAdmin);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Arguments: %s <name> <password>\n", argv[0]);
        exit(0);
    }
    handleData(argv[1], argv[2]);
}
