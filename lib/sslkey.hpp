/** @file sslkey.hpp
  * SSL/TLS key and certificate loader.
  *
  * @copyright (C) 2014 R&D Co.\n
  *    All rights reserved.
  *
  * @date 2014-02-11
  * @author amir zamani
  * @version 1.0.0 \n
  *
  */
#ifndef SSLKEY_HPP
#define SSLKEY_HPP

#include <QtCore/QFile>
#include <QtNetwork/QSslKey>
#include <QtNetwork/QSslCertificate>

///////////////////////////////////////////////////////////////////////////////
namespace am {
///////////////////////////////////////////////////////////////////////////////
/** a utility class for loading a key or certificate from a file path. */
class Ssl
{
public:

    /** loads an SSL certificate from filePath. */
    static QSslCertificate
    loadCertificate(const QString& filePath,
                    QSsl::EncodingFormat format = QSsl::Pem) {
        QFile f(filePath);
        if ( f.open(QIODevice::ReadOnly) ) {
            QByteArray arr = f.readAll();

            return QSslCertificate(arr, format);
        }

        return QSslCertificate();
    }

    /** loads an SSL key from filePath. */
    static QSslKey
    loadKey(const QString& filePath,
            QSsl::KeyAlgorithm alg = QSsl::Rsa,
            QSsl::EncodingFormat format = QSsl::Pem) {
        QFile f(filePath);
        if ( f.open(QIODevice::ReadOnly) ) {
            QByteArray arr = f.readAll();

            return QSslKey(arr, alg, format);
        }

        return QSslKey();
    }

};
///////////////////////////////////////////////////////////////////////////////
} // namespace am
///////////////////////////////////////////////////////////////////////////////
#endif // SSLKEY_HPP
