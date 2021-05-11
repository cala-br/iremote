#include "ir_auth_server.hpp"

using ir_remote::IRAuthServer;
using ir_remote::AuthSocket;


IRAuthServer::IRAuthServer(
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


void IRAuthServer::setCertificates(const char *cert, const char *key) {
  _server
    .getServer()
    .setRSACert(new X509List{cert}, new PrivateKey{key});
}


void IRAuthServer::begin() {
  _server.begin();
}

void IRAuthServer::handleNext() {
  _server.handleClient();
}


bool IRAuthServer::isAuthorized(AuthSocket socket) {
  const auto target = 
    _authorizedClients.find(socket);
  
  return target != _authorizedClients.end();
}


void IRAuthServer::tryRegister() {
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

void IRAuthServer::deregister() {
  deregisterClient();
  unauthorized();
}


bool IRAuthServer::clientAuthenticated() {
  return _server.authenticate("calabr", "12345");
}


void IRAuthServer::registerClient() {
  const auto client = getClientAuthSocket();
  _authorizedClients.insert(client);
}

void IRAuthServer::deregisterClient() {
  const auto client = getClientAuthSocket();
  const auto entry = 
    _authorizedClients.find(client);

  if (entry != _authorizedClients.end())
    _authorizedClients.erase(entry);
}


AuthSocket IRAuthServer::getClientAuthSocket() {
  auto client = _server.client();
  auto clientIP = client.remoteIP();
  auto clientPort = _server.arg("port");
  return {
    .ip = clientIP,
    .port = uint16_t(clientPort.toInt()),
  };
}


void IRAuthServer::ok() {
  _server.send(200, "text/plain", "OK");
}

void IRAuthServer::badRequest() {
  _server.send(400, "text/plain", "BAD_REQUEST");
}

void IRAuthServer::unauthorized() {
  _server.send(401, "text/plain", "UNAUTHORIZED");
}