#ifndef AUTH_SOCKET_HPP_
#define AUTH_SOCKET_HPP_

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif
#include <set>

namespace ir_remote {
  struct AuthSocket {
    IPAddress ip;
    uint16_t port;

    static bool compare(AuthSocket a, AuthSocket b) {
      return a.ip == b.ip && a.port == b.port;
    }
  };

  using AuthSocketSet = 
    std::set<AuthSocket, decltype(AuthSocket::compare)*>;
}

#endif // !AUTH_SOCKET_HPP_