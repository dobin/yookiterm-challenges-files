#include "mongoose.h"

#ifndef HTTP
#define HTTP
#endif

void rest_auth(struct mg_connection *c, struct http_message *hm);
void rest_ping(struct mg_connection *c, struct http_message *hm);
void rest_login(struct mg_connection *c, struct http_message *hm);
void rest_logout(struct mg_connection *c, struct http_message *hm);

void logout_handler(void);