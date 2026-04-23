#ifndef SSL_SOCKET_H
#define SSL_SOCKET_H

#include "Socket.h"
#include <openssl/ssl.h>
#include <openssl/err.h>

class SSLSocket : public Socket {
private:
    SSL_CTX *context;
    SSL *ssl;

public:
    SSLSocket(bool IPv6 = false);
    SSLSocket(const char *certFile, const char *keyFile, bool IPv6 = false);
    ~SSLSocket() override;

    void InitContext(bool server);
    void Init();

    void LoadCertificates(const char *certFile, const char *keyFile);

    void Copy(SSLSocket *original);

    void AcceptSSL();
    int ConnectSSL();

    const char *GetCipher();
    void ShowCerts();

    size_t Read(void *buffer, size_t size) override;
    size_t Write(const void *buffer, size_t size) override;

    VSocket *AcceptConnection() override;

    void Close();
};

#endif