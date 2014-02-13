#include "sslsocketbase.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace am {
///////////////////////////////////////////////////////////////////////////////
SslSocketBase::SslSocketBase(QObject *parent) : QSslSocket(parent) {
    // set peer (clients) verification mode
    setPeerVerifyMode(QSslSocket::VerifyPeer);

    // log SSL errors
    QObject::connect(this,
                     static_cast<void (SslSocketBase::*)(const QList<QSslError>&)>(&SslSocketBase::sslErrors),
                     [this](const QList<QSslError>& arg) {

        this->onSslErrors(arg);
    });
}

SslSocketBase::~SslSocketBase() {
}

void
SslSocketBase::setPKI(const QString &keyFilePath,
                      const QString &certFilePath) {

    setPrivateKey(keyFilePath);
    setLocalCertificate(certFilePath);
}

void
SslSocketBase::setPKI(const QSslKey &privateKey,
                      const QSslCertificate &localCertificate) {

    setPrivateKey(privateKey);
    setLocalCertificate(localCertificate);
}

void
SslSocketBase::onSslErrors(const QList<QSslError> &errors) {
    foreach (QSslError err, errors) {

        fprintf(stderr, "QSslSocket error (# %d): %s\n",
                (int) err.error(),
                qPrintable(err.errorString())
                );
    }
}

///////////////////////////////////////////////////////////////////////////////
} // namespace am
///////////////////////////////////////////////////////////////////////////////

