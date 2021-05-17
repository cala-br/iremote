#include <auth_socket.hpp>
#include "udp_server_secure.hpp"

using namespace iremote;


UdpServerSecure::UdpServerSecure(AuthServer& authServer)
  : _authServer(authServer)
{}


AuthServer& UdpServerSecure::auth() {
  return _authServer;
}

void UdpServerSecure::begin(uint16_t udpPort) {
  _udpServer.begin(udpPort);
}


bool UdpServerSecure::tryParsePacket() {
  int packetSize = _udpServer.parsePacket();
  return packetSize > 0;
}

bool UdpServerSecure::isRemoteAuthorized() {
  const auto authSocket = AuthSocket{
    .ip = _udpServer.remoteIP(),
    .port = _udpServer.remotePort(),
  };

  return _authServer.isAuthorized(authSocket);
}

bool UdpServerSecure::tryReadCommand() {
  int bytesRead = 
    _udpServer.read(_command, MAX_COMMAND_LEN);
  
  if (bytesRead == 0)
    return false; 

  _command[bytesRead] = '\0';
  return true;
}