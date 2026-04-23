#include "SSLSocket.h"
#include <cstdio>
#include <cstring>

int main() {

    SSLSocket *client = new SSLSocket();

    client->InitContext(false);

    client->Connect("127.0.0.1", 4321);

    client->Init();

    client->ConnectSSL();

    printf("Cipher: %s\n", client->GetCipher());

    const char *msg =
        "\n<Body>\n\t<UserName>piro</UserName>\n\t<Password>ci0123</Password>\n</Body>\n";

    client->Write(msg, strlen(msg));

    char buf[1024];
    int bytes = client->Read(buf, sizeof(buf));
    buf[bytes] = 0;

    printf("Server: %s\n", buf);

    client->Close();
}