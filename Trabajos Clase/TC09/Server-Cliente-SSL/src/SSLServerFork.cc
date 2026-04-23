#include "SSLSocket.h"
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstring>

#define PORT 4321

void Service(SSLSocket *client) {

    char buf[1024] = {0};

    int bytes = client->Read(buf, sizeof(buf));
    buf[bytes] = 0;

    printf("Client: %s\n", buf);

    client->Write("<OK>Fork Server</OK>", 22);

    client->Close();
}

int main() {

    SSLSocket *server = new SSLSocket("ci0123.pem", "key0123.pem", true);

    server->Bind(PORT);
    server->MarkPassive(10);

    while (true) {

        SSLSocket *client = (SSLSocket *)server->AcceptConnection();

        pid_t pid = fork();

        if (pid == 0) {
            // proceso hijo

            client->Copy(server);

            Service(client);

            exit(0);

        } else if (pid > 0) {
            // proceso padre

            delete client;

            // evitar zombies
            waitpid(-1, nullptr, WNOHANG);
        }
    }
}