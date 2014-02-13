/** @file sslsocketbase.hpp
  *
  *
  * @date 2014-02-11
  * @author amir zamani
  * @version 1.0.0 \n
  *
  */

#ifndef SSLSOCKETBASE_HPP
#define SSLSOCKETBASE_HPP

///////////////////////////////////////////////////////////////////////////////
#include "include/config.hpp"
#include "sslkey.hpp"

#include <QtNetwork/QSslSocket>

///////////////////////////////////////////////////////////////////////////////
namespace am {
///////////////////////////////////////////////////////////////////////////////
/** a base class for client or server SSL socket.
 * @sa ServerSideSslSocket and @sa ClientSideSslSocket
 */
class SslSocketBase : public QSslSocket
{
    Q_OBJECT

public:
    explicit        SslSocketBase(QObject* parent = 0);

    virtual        ~SslSocketBase();

    /** set a pair of private key and local certificate for this socket. */
    void            setPKI(const QString& keyFilePath,
                           const QString& certFilePath);

    /** set a pair of private key and local certificate for this socket. */
    void            setPKI(const QSslKey& privateKey,
                           const QSslCertificate& localCertificate);


public:
    /** [optional] set a new list of ignorable errors.
     * @sa iignorableErrors . */
    void            setIgnorableErrors(const QList<QSslError>& errors) {
        iignorableErrors = errors;
    }

    /** [optiona] adds a new QSslError to the ignorable list.
     * @sa iignorableErrors . */
    void            addIgnorableError(QSslError err) {
        iignorableErrors << err;
    }

protected slots:
    virtual void    onSslErrors(const QList<QSslError>&);

protected:
    /** list of ignorable SSL errors. */
    QList<QSslError> iignorableErrors;
};

///////////////////////////////////////////////////////////////////////////////
} // namespace am
///////////////////////////////////////////////////////////////////////////////
#endif // SSLSOCKETBASE_HPP
