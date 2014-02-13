/** @file clientsidesslsocket.hpp
  *
  *
  * @date 2014-02-11
  * @author amir zamani
  * @version 1.0.0 \n
  *
  */

#ifndef CLIENTSIDESSLSOCKET_HPP
#define CLIENTSIDESSLSOCKET_HPP

///////////////////////////////////////////////////////////////////////////////
#include "sslsocketbase.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace am {
///////////////////////////////////////////////////////////////////////////////
class ClientSideSslSocket : public SslSocketBase
{
    Q_OBJECT

public:
    explicit        ClientSideSslSocket(QObject* parent = 0);

    virtual        ~ClientSideSslSocket();

    /** connects to a SSL socket server.
     * adjust ignorable SSL errors based on iserverCert and iignorableErrors.
     * @sa QSslSocket::connectToHostEncrypted . */
    virtual void    connectToHostEncrypted(const QString& hostname,
                                           quint16 portNumber);
public:
    /** [optional] set server certificate.
     * this client will be disconnected immediately if server certificate missmatches.
     */
    void            setServerCertificate(const QSslCertificate& c) {
        iserverCert = c;
    }

    /** [optional] set server certificate by file path.
     * @sa setClientCertificate()
     */
    void            setServerCertificate(const QString& certFilePath) {
        setServerCertificate( am::Ssl::loadCertificate(certFilePath) );
    }


protected:
    /** server's certificate to be verified. default is a null certificate. */
    QSslCertificate iserverCert;
};

///////////////////////////////////////////////////////////////////////////////
} // namespace am
///////////////////////////////////////////////////////////////////////////////

/** @class am::ClientSideSslSocket
 * client side SSL socket. simplifies self-signed certificates to be used.
 * usage:
 * @code
    ClientSideSslSocket   sok;
    sok.setPKI(":/pkey", ":/cert");
    sok.setServerCertificate(":/server_cert");
    sok.connectToHostEncrypted(ipAddress, portNumber);
 * @endcode
 */

#endif // CLIENTSIDESSLSOCKET_HPP
