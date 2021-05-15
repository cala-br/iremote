#include "auth_server.hpp"

using iremote::AuthServer;
using iremote::AuthSocket;


AuthServer::AuthServer(
  const char *username, 
  const char *password
) : 
  _username(username),
  _password(password),
  _server({443}),
  _authorizedClients({AuthSocket::compare})
{
  _server.on("/try-register", HTTP_POST, [this] {
    this->tryRegister();
  });

  _server.on("/deregister", HTTP_POST, [this] {
    this->deregister();
  });
}


void AuthServer::setCertificates(const char *cert, const char *key) {
  _server
    .getServer()
    .setRSACert(new X509List{cert}, new PrivateKey{key});
}


void AuthServer::begin() {
  _server.begin();
}

void AuthServer::handleNext() {
  _server.handleClient();
}


bool AuthServer::isAuthorized(AuthSocket socket) {
  const auto target = 
    _authorizedClients.find(socket);
  
  return target != _authorizedClients.end();
}


void AuthServer::tryRegister() {
  if (!clientAuthenticated()) {
    unauthorized();
    return;
  }

  if (!_server.hasArg("port")) {
    badRequest();
    return;
  }
  
  registerClient();
  ok();
}

void AuthServer::deregister() {
  deregisterClient();
  unauthorized();
}


bool AuthServer::clientAuthenticated() {
  return _server.authenticate(_username, _password);
}


void AuthServer::registerClient() {
  const auto client = getClientAuthSocket();
  _authorizedClients.insert(client);
}

void AuthServer::deregisterClient() {
  const auto client = getClientAuthSocket();
  const auto entry = 
    _authorizedClients.find(client);

  if (entry != _authorizedClients.end())
    _authorizedClients.erase(entry);
}


AuthSocket AuthServer::getClientAuthSocket() {
  auto client = _server.client();
  auto clientIP = client.remoteIP();
  auto clientPort = _server.arg("port");
  return {
    .ip = clientIP,
    .port = uint16_t(clientPort.toInt()),
  };
}


void AuthServer::ok() {
  _server.send(200, "text/plain", "OK");
}

void AuthServer::badRequest() {
  _server.send(400, "text/plain", "BAD_REQUEST");
}

void AuthServer::unauthorized() {
  _server.send(401, "text/plain", "UNAUTHORIZED");
}