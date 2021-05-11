#ifndef IR_SERVER_HPP_
#define IR_SERVER_HPP_

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#else
  #include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <ir_auth_server.hpp>

namespace ir_remote {
  constexpr byte MAX_COMMAND_LEN = 24;
  using IRCommand = char[MAX_COMMAND_LEN];

  class IRServer {
  public:
    IRServer(IRAuthServer& authServer);
    
    void begin();

    template <typename CommandHandler>
    void handleNext(CommandHandler handler);
  private:
    IRAuthServer& _authServer;
    WiFiUDP _udpServer;
    IRCommand _command;

    bool tryParsePacket();
    bool isRemoteAuthorized();
    bool tryReadCommand();
  };


  template <typename CommandHandler>
  void IRServer::handleNext(CommandHandler handler) {
    if (!tryParsePacket())      return;
    if (!isRemoteAuthorized())  return;
    if (!tryReadCommand())      return;

    handler(_command);
  }
}

#endif // !IR_SERVER_HPP_