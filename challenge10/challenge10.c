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


void handleIsAdmin(void) {
        printf("You are admin!\n");
}

void handleIsNotAdmin(void) {
        printf("You are not admin.\n");
}


int checkName(char *username) {
    char name[64]; // should be enough for all usernames

    // create according username
    sprintf(name, "%s-%s", "cmd", username);

    // atm we accept all usernames
    return 1;
}


void handleData(char *username, char *password) {
    if (! checkName(username)) {
        return;
    }

    // Check if user has admin privileges
    if(checkPassword(password)) {
        handleIsAdmin();
    } else {
        handleIsNotAdmin();
    }
}


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Call: %s <name> <password>\n", argv[0]);
        exit(0);
    }

    handleData(argv[1], argv[2]);
}
