#include "mongoose.h"
#include "http.h"

// An authenticated user
struct t_authenticated {
    int role;
    char sessionid[128];
    void (*logout_handler)();
};

// Only supports 1 authenticated user for now
struct t_authenticated *Authenticated;


// REST: /ping
void rest_ping(struct mg_connection *c, struct http_message *hm) {
    int len = (int)hm->query_string.len;

    printf("Ping\n");
    printf("  Allocating: %i = len\n", len);

    // Answer - copy query_string and send it back
    void* qs = malloc(len);
    memcpy(qs, hm->query_string.p, hm->query_string.len);

    mg_send_head(c, 200, len, "Content-Type: text/plain");
    mg_send(c, qs, len);

    free(qs);
}


#define RESPONSE_LEN 128
// REST: /login
void rest_login(struct mg_connection *c, struct http_message *hm) {
    char response[RESPONSE_LEN];

    printf("Login\n");

    // Malloc and init for Authenticated struct
    Authenticated = malloc(sizeof(struct t_authenticated));
    Authenticated->logout_handler = &logout_handler;
    Authenticated->role = 23;
    strcpy(Authenticated->sessionid, "5"); // chosen by a fair dice roll
    printf("  Allocated for t_authenticated %li(0x%lx) at %p\n", 
        sizeof(struct t_authenticated), sizeof(struct t_authenticated), Authenticated);

    strncpy(response, Authenticated->sessionid, 8);

    mg_send_head(c, 200, RESPONSE_LEN, "Content-Type: text/plain");
    mg_send(c, response, RESPONSE_LEN);
}


// REST: /logout
void rest_logout(struct mg_connection *c, struct http_message *hm) {
    char response[512];

    // Debug
    printf("Logout\n");
    printf("  Authenticated:\n");
    printf("    role          : 0x%x\n", Authenticated->role);
    printf("    sessionid     : %s\n", Authenticated->sessionid);
    printf("    Logout handler: %p\n", Authenticated->logout_handler);

    // Send answer
    sprintf(response, "Logout %i\r\n", Authenticated->role);
    mg_send_head(c, 200, strlen(response), "Content-Type: text/plain");
    mg_printf(c, "%s", response);

    // Cleanup
    (*Authenticated->logout_handler)();
    free(Authenticated);
}


void logout_handler(void) {
    printf("  Logout event handler\n");
    // Lets clean up later
}


void rest_auth(struct mg_connection *c, struct http_message *hm) {
    char response[512];
    void *bla;
    void *bla2;
    int len = 250;

    // Answer
    strcpy(response, "Authed\r\n");

    // HEAP
    bla = malloc(len);
    bla2 = malloc(len);
    printf("Allocated1 0x%x at %p\n", len, bla);
    printf("Allocated2 0x%x at %p\n", len, bla2);

    mg_send_head(c, 200, strlen(response), "Content-Type: text/plain");
    mg_printf(c, "%s", response);
}


int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    uint8_t api = Data[0];
    Data += 1;
    Size -= 1;

    // Init data structures
    struct http_message hm;
    hm.query_string.p = (const char*) Data;
    hm.query_string.len = Size;

    struct mg_connection c;
    struct mbuf out;
    mbuf_init(&c.send_mbuf, 0);

    // API
    api = api % 3;
    //printf("Api: %i", api);
    switch(api) {
        case 0:
            rest_ping(&c, &hm);
            break;
        case 1:
            rest_login(&c, &hm);
            break;
        case 2:
            rest_logout(&c, &hm);
            break;
    }

    return 0;
}