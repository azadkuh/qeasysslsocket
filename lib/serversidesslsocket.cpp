#include "serversidesslsocket.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace am {
///////////////////////////////////////////////////////////////////////////////
ServerSideSslSocket::ServerSideSslSocket(QObject *parent) : SslSocketBase(parent) {

    // ignore self-signed certificates. helpful it test environment without an oficial CA.
    iignorableErrors << QSslError::SelfSignedCertificate
                     << QSslError::HostNameMismatch;

    // set peer (clients) verification mode
    setPeerVerifyMode(QSslSocket::VerifyPeer);

    // check if the client's key is qualified with iclientCert as soon as SSL connection establishes
    QObject::connect(this,    &QSslSocket::encrypted,
                     this,    &ServerSideSslSocket::onEncrypted);
}

ServerSideSslSocket::~ServerSideSslSocket() {
}

bool
ServerSideSslSocket::setSocketDescriptor(qintptr sokDec, SocketState socketState, OpenMode openMode) {

    // set ignorable ssl errors (prevents from dropping the connection)
    ignoreSslErrors(iignorableErrors);

    // set socket descriptor. delete this object if fails.
    if ( !QSslSocket::setSocketDescriptor(sokDec, socketState, openMode) ) {
        deleteLater();
        return false;
    }

    // start handshaking and other TLS/SSL stuff.
    startServerEncryption();
    return true;
}

void
ServerSideSslSocket::onEncrypted() {
    // check client's public key if it is already set
    if ( peerVerifyMode() == QSslSocket::VerifyPeer ) {

        QSslKey clientPub = iclientCert.publicKey();

        if ( !clientPub.isNull() ) {

            if ( clientPub != peerCertificate().publicKey() ) {
                qDebug("unknown certificate. connection dropped forcefully!");
                disconnectFromHost();

                return;
            }
        }
    }

    emit connectionVerified();
}

///////////////////////////////////////////////////////////////////////////////
} // namespace am
///////////////////////////////////////////////////////////////////////////////

