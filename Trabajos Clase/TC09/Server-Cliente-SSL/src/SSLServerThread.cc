#include "SSLSocket.h"
#include <thread>
#include <cstdio>
#include <cstring>

#define PORT 4321

void Service(SSLSocket *client) {

    char buf[1024] = {0};

    int bytes = client->Read(buf, sizeof(buf));
    buf[bytes] = 0;

    printf("Client: %s\n", buf);

    client->Write("<OK>Thread Server</OK>", 24);

    client->Close();
}

int main() {

    // IPv6
    SSLSocket *server = new SSLSocket("ci0123.pem", "key0123.pem", true);

    server->Bind(PORT);
    server->MarkPassive(10);

    while (true) {
        SSLSocket *client = (SSLSocket *)server->AcceptConnection();

        client->Copy(server);

        std::thread(Service, client).detach();
    }
}