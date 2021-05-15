# iremote

## Instantiating the AuthServer

This server will be responsible of authorizing the remote client to use an UDP connection.

It uses basic authentication, and can be configured to use SSL certificates, so that the authentication and authorization processes are secure.

```c++
iremote::AuthServer authServer {
  "username",
  "password",
};

void setup() {
  authServer.setCertificates(CERT, KEY);
  authServer.begin();
}

void loop() {
  authServer.handleNext();
}
```

One can then know if a remote socket is authorized by using the `authServer.isAuthenticated(sock)` method, where `sock` is an `AuthSocket`:

```c++
authServer.isAuthenticated(
  AuthSocket{ipAddress, port}
);
```

---

In order to authorize/unauthorize a port you can send a `POST` request to the server.

| path          | method | query              | returns    |
|---------------|--------|--------------------|------------|
| `/register`   | `POST` | `?port={uint16_t}` | `200, 401` |
| `/deregister` | `POST` | `?port={uint16_t}` | `401`      |


*Libraries will probably require you to provide the certificates in order to connect.*

---

An example using the nodejs fetch API:
```js
const authReq = (action, udpPort, credentials) => {
  return fetch(`https://x.x.x.x/${action}?port=${udpPort}`, {
    method: 'POST',
    headers: {
      host: 'hostname',
      authorization: `Basic ${credentials}`
    },
    agent: new https.Agent({
      ca: ca,
    }),
  });
}

authReq('register', 5050, 'username:password');
authReq('deregister', 5050, 'username:password');
```

Where:
  - `host: 'hostname'`
    - The domain name specified in the SSL certificate.
    You should provide it if you are connecting to the server using its IP address.

  - `ca: ca`
    - The certificate that the server is using, if you are using a self-signed one.

---

## Instantiating the UdpServerSecure
```c++
iremote::UdpServerSecure udpServer {authServer};

void setup() {
  udpServer.begin(udpPort);
}

void loop() {
  udpServer.handleNext(callback);
}

void callback(UdpString msg) {
  Serial.println(msg);
}
```

*The UdpServer requires a reference to the authentication server.*

It will drop any packet that is coming from any unauthorized socket.