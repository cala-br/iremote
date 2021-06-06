#ifndef IR_AUTH_SERVER_HPP_
#define IR_AUTH_SERVER_HPP_

#include <ESP8266WebServerSecure.h>
#include <certificates_bag.hpp>
#include <set>
#include "auth_socket.hpp"

namespace iremote {
  class AuthServer {
  public:
    AuthServer(const char *username, const char *password);
    AuthServer(const char *username, const char *password, CertificatesBag certs);

    void setCertificates(CertificatesBag certs);
    void begin();
    void handleNext();

    bool isAuthorized(AuthSocket socket);
  private:
    const char *_username;
    const char *_password;
    ESP8266WebServerSecure _server;
    std::set<AuthSocket> _authorizedClients;

    void tryRegister();
    void deregister();
    bool clientAuthenticated();

    void registerClient();
    void deregisterClient();
    AuthSocket getClientAuthSocket();

    void hello();
    void ok();
    void badRequest();
    void unauthorized();
  };
}

#endif // !IR_AUTH_SERVER_HPP_