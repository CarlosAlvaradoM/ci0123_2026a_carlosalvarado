#include "SSLSocket.h"
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

#define FAIL -1

SSLSocket::SSLSocket(bool IPv6)
    : Socket('s', IPv6) {
    context = nullptr;
    ssl = nullptr;
}

SSLSocket::SSLSocket(const char *certFile, const char *keyFile, bool IPv6)
    : Socket('s', IPv6) {

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    InitContext(true);
    LoadCertificates(certFile, keyFile);
}

SSLSocket::~SSLSocket() {
    if (ssl) SSL_free(ssl);
    if (context) SSL_CTX_free(context);
}

void SSLSocket::InitContext(bool server) {
    const SSL_METHOD *method;

    if (server)
        method = TLS_server_method();
    else
        method = TLS_client_method();

    context = SSL_CTX_new(method);

    if (!context) {
        ERR_print_errors_fp(stderr);
        abort();
    }
}

void SSLSocket::Init() {
    ssl = SSL_new(context);

    if (!ssl) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    SSL_set_fd(ssl, this->sockId);
}

void SSLSocket::LoadCertificates(const char *certFile, const char *keyFile) {

    if (SSL_CTX_use_certificate_file(context, certFile, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    if (SSL_CTX_use_PrivateKey_file(context, keyFile, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    if (!SSL_CTX_check_private_key(context)) {
        fprintf(stderr, "Key mismatch\n");
        abort();
    }
}

void SSLSocket::Copy(SSLSocket *original) {

    this->context = original->context;

    ssl = SSL_new(context);

    if (!ssl) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    SSL_set_fd(ssl, this->sockId);

    AcceptSSL();
}

void SSLSocket::AcceptSSL() {
    if (SSL_accept(ssl) == FAIL) {
        ERR_print_errors_fp(stderr);
    }
}

int SSLSocket::ConnectSSL() {
    if (SSL_connect(ssl) == FAIL) {
        ERR_print_errors_fp(stderr);
        return FAIL;
    }
    return 1;
}

const char *SSLSocket::GetCipher() {
    return SSL_get_cipher(ssl);
}

void SSLSocket::ShowCerts() {
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);

    if (cert != nullptr) {
        printf("Certificates:\n");

        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);

        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);

        X509_free(cert);
    } else {
        printf("No certificates\n");
    }
}

size_t SSLSocket::Read(void *buffer, size_t size) {
    return (size_t) SSL_read(ssl, buffer, size);
}

size_t SSLSocket::Write(const void *buffer, size_t size) {
    return (size_t) SSL_write(ssl, buffer, size);
}

VSocket *SSLSocket::AcceptConnection() {
    int clientFd = this->WaitForConnection();

    SSLSocket *client = new SSLSocket();
    client->sockId = clientFd;

    return client;
}

void SSLSocket::Close() {
    int sd = SSL_get_fd(ssl);
    SSL_free(ssl);
    close(sd);
}