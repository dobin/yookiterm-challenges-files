#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>

int checkPassword(char *password) {
    char *adminHash = "$6$saaaaalty$cjw9qyAKmchl7kQMJxE5c1mHN0cXxfQNjs4EhcyULLndQR1wXslGCaZrJj5xRRBeflfvmpoIVv6Vs7ZOQwhcx.";
    char *hash = crypt(password, "$6$saaaaalty");
    if (strcmp(hash, adminHash) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void secret() {
    printf("Secret functionality\n");
}

void handleData(char *username, char *password) {
    int isAdmin = 0;
    char name[128];

    isAdmin = checkPassword(password);
    strcpy(name, username);

    printf("isAdmin: 0x%x\n", isAdmin);
    if(isAdmin > 0) {
        printf("You are admin!\n");
    } else {
        printf("Not admin.\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <name> <password>\n", argv[0]);
        exit(0);
    }
    handleData(argv[1], argv[2]);
}
