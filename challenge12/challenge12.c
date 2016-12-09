#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>

/* hash of: "ourteacheristehbest" */
const char *adminHash = "$6$saaaaalty$cjw9qyAKmchl7kQMJxE5c1mHN0cXxfQNjs4EhcyULLndQR1wXslGCaZrJj5xRRBeflfvmpoIVv6Vs7ZOQwhcx.";


int checkPassword(char *password) {
    char *hash;

    /* $6$ is SHA256 */
    hash = crypt(password, "$6$saaaaalty");

    if (strcmp(hash, adminHash) == 0) {
        return 1;
    } else {
        return 0;
    }
}


void handleData(char *username, char *password) {
    int isAdmin = 0;
    char name[64]; // should be enough for all usernames

    // Check if user has admin privileges
    isAdmin = checkPassword(password);

    // create internal username
    sprintf(name, "%s-%s", "cmd", username);

    if(isAdmin > 0) {
        printf("Hello %s.\nYou are admin!\nisAdmin: 0x%x\n", name, isAdmin);
    } else {
        printf("Hello %s.\nYou are not admin.\nisAdmin: 0x%x\n", name, isAdmin);
    }
}


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Call: %s <name> <password>\n", argv[0]);
        exit(0);
    }

    handleData(argv[1], argv[2]);
}
