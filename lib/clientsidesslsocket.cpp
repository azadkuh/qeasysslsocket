#include "clientsidesslsocket.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace am {
///////////////////////////////////////////////////////////////////////////////
ClientSideSslSocket::ClientSideSslSocket(QObject *parent) : SslSocketBase(parent) {

    // ignore self-signed certificates. helpful it test environment without an oficial CA.
    iignorableErrors << QSslError::SelfSignedCertificate
                     << QSslError::HostNameMismatch;

    // set peer (clients) verification mode
    setPeerVerifyMode(QSslSocket::VerifyPeer);
}

ClientSideSslSocket::~ClientSideSslSocket() {
}

void
ClientSideSslSocket::connectToHostEncrypted(const QString &hostname, quint16 portNumber) {
    // create ignorabe errors for server's certificate
    if ( iserverCert.isNull() ) {
        ignoreSslErrors(iignorableErrors);

    } else {
        addCaCertificate(iserverCert);
        QList<QSslError> errors;
        foreach (const QSslError& err, iignorableErrors) {
            errors << QSslError(err.error(), iserverCert);
        }
        ignoreSslErrors(errors);
    }

    QSslSocket::connectToHostEncrypted(hostname, portNumber);
}

///////////////////////////////////////////////////////////////////////////////
} // namespace am
///////////////////////////////////////////////////////////////////////////////

