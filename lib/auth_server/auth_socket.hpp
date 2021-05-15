#ifndef AUTH_SOCKET_HPP_
#define AUTH_SOCKET_HPP_

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

namespace iremote {
  struct AuthSocket : public Printable {
    IPAddress ip;
    uint16_t port;

    AuthSocket(IPAddress ip, uint16_t port)
      : ip(ip), port(port)
    {}

    bool operator<(const AuthSocket& o) const {
      return ip.v4() < o.ip.v4() && port < o.port;
    }

    size_t printTo(Print& p) const {
      return 
        p.print(ip) +
        p.print(":") +
        p.print(port);
    }
  };
}

#endif // !AUTH_SOCKET_HPP_