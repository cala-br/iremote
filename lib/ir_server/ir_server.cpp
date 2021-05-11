#include <auth_socket.hpp>
#include "ir_server.hpp"

using namespace ir_remote;


IRServer::IRServer(IRAuthServer& authServer)
  : _authServer(authServer)
{}

void IRServer::begin() {
  _udpServer.begin(7382);
}


bool IRServer::tryParsePacket() {
  int packetSize = _udpServer.parsePacket();
  return packetSize > 0;
}

bool IRServer::isRemoteAuthorized() {
  const auto authSocket = AuthSocket{
    .ip = _udpServer.remoteIP(),
    .port = _udpServer.remotePort(),
  };

  return _authServer.isAuthorized(authSocket);
}

bool IRServer::tryReadCommand() {
  int bytesRead = 
    _udpServer.read(_command, MAX_COMMAND_LEN);
  
  if (bytesRead == 0)
    return false; 

  _command[bytesRead] = '\0';
  return true;
}