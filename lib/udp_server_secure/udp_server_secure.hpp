#ifndef IR_SERVER_HPP_
#define IR_SERVER_HPP_

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#else
  #include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <auth_server.hpp>

namespace iremote {
  constexpr byte MAX_COMMAND_LEN = 24;
  using UdpString = char[MAX_COMMAND_LEN];

  class UdpServerSecure {
  public:
    UdpServerSecure(AuthServer& authServer);
    
    AuthServer& auth();
    void begin(uint16_t udpPort);

    template <typename CommandHandler>
    void handleNext(CommandHandler handler);

  private:
    AuthServer& _authServer;
    WiFiUDP _udpServer;
    UdpString _command;

    bool tryParsePacket();
    bool isRemoteAuthorized();
    bool tryReadCommand();
  };


  template <typename CommandHandler>
  void UdpServerSecure::handleNext(CommandHandler handler) {
    if (!tryParsePacket())      return;
    if (!isRemoteAuthorized())  return;
    if (!tryReadCommand())      return;

    handler(_command);
  }
}

#endif // !IR_SERVER_HPP_