#ifndef IR_AUTH_SERVER_HPP_
#define IR_AUTH_SERVER_HPP_

#include <ESP8266WebServerSecure.h>
#include "auth_socket.hpp"

namespace iremote {
  class AuthServer {
  public:
    AuthServer(const char *username, const char *password);

    void setCertificates(const char *cert, const char *key);
    void begin();
    void handleNext();

    bool isAuthorized(AuthSocket socket);
  private:
    const char *_username;
    const char *_password;
    ESP8266WebServerSecure _server;
    AuthSocketSet _authorizedClients;

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