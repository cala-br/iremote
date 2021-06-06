#ifndef IREMOTE_CERTIFICATES_BAG_HPP_
#define IREMOTE_CERTIFICATES_BAG_HPP_

#include <ESP8266WebServerSecure.h>
#include <memory>

namespace iremote {
  struct CertificatesBag {
    CertificatesBag(const char *cert, const char *key)
        : 
        cert(new X509List{cert}),
        key(new PrivateKey{key})
    {}

    std::shared_ptr<X509List> cert;
    std::shared_ptr<PrivateKey> key;
  };
}

#endif // !IREMOTE_CERTIFICATES_BAG_HPP_
