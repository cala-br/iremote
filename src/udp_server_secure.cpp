#include <auth_socket.hpp>
#include "udp_server_secure.hpp"

using namespace iremote;


UdpServerSecure::UdpServerSecure(std::shared_ptr<AuthServer> authServer)
  : _authServer(authServer)
{}


auto UdpServerSecure::auth() -> std::shared_ptr<AuthServer> {
  return _authServer;
}

void UdpServerSecure::begin(uint16_t udpPort) {
  _authServer->begin();
  _udpServer.begin(udpPort);
}


bool UdpServerSecure::tryParsePacket() {
  int packetSize = _udpServer.parsePacket();
  return packetSize > 0;
}

bool UdpServerSecure::isRemoteAuthorized() {
  const auto authSocket = AuthSocket{
    _udpServer.remoteIP(),
    _udpServer.remotePort(),
  };

  return _authServer->isAuthorized(authSocket);
}

bool UdpServerSecure::tryReadCommand() {
  int bytesRead = 
    _udpServer.read(_command, MAX_COMMAND_LEN);
  
  _command[bytesRead] = '\0';
  return bytesRead > 0;
}