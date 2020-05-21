#include "mongoose.h"
#include "http.h"

static const char *s_http_port = "8000";


static void ev_handler(struct mg_connection *c, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;

        if (mg_vcmp(&hm->uri, "/auth") == 0) {
            printf("Auth\n");
            rest_auth(c, hm);
        } else if (mg_vcmp(&hm->uri, "/ping") == 0) {
            rest_ping(c, hm);
        } else if (mg_vcmp(&hm->uri, "/login") == 0) {
            rest_login(c, hm);
        } else if (mg_vcmp(&hm->uri, "/logout") == 0) {
            rest_logout(c, hm);
        } else {
            printf("No handler found for URL: %.*s\n", (int)hm->uri.len, hm->uri.p);
        }
    }
}


int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *c;
    printf("Start Webserver on port: %s\n", s_http_port);

    mg_mgr_init(&mgr, NULL);
    c = mg_bind(&mgr, s_http_port, ev_handler);
    mg_set_protocol_http_websocket(c);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}
