/** @file serversslsocket.hpp
  *
  *
  * @date 2014-02-11
  * @author amir zamani
  * @version 1.0.0 \n
  *
  */

#ifndef SERVERSIDESSLSOCKET_HPP
#define SERVERSIDESSLSOCKET_HPP

///////////////////////////////////////////////////////////////////////////////
#include "sslsocketbase.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace am {
///////////////////////////////////////////////////////////////////////////////
class ServerSideSslSocket : public SslSocketBase
{
    Q_OBJECT

public:
    explicit        ServerSideSslSocket(QObject* parent = 0);

    virtual        ~ServerSideSslSocket();

    /** set the socket descriptor of this server-side SSL socket.
     * this function maked ServerSideSslSocket suitable even in multi-threaded scenario.
     * @sa QAbstractSocket::setSocketDescriptor .
     * @return true as success or false for failure.
     */
    virtual bool    setSocketDescriptor(qintptr sokDec,
                                        SocketState socketState = ConnectedState,
                                        OpenMode openMode = ReadWrite);

signals:
    /** ServerSideSslSocket emits this signal when an SSL connection is approved.
     * sequence of an SSL socket connection-signals: connected() -> encrypted() -> connectionVerified()
     * - a socket may be connected (befor SSL/TLS handshake) first
     * - then after a successful TLS handshake and key exchanges, enters to encrypted() mode
     * - finally if the client's certificate is approved by this class, connectionVerified() is emitted.
     */
    void            connectionVerified();

public:
    /** [optional] set client certificate.
     * the clients will be disconnected immediately if they have different certificate.
     * @warning if this certificate is null or verifyMode != QSslSocket::VerifyPeer the certificate is not checked.
     */
    void            setClientCertificate(const QSslCertificate& c) {
        iclientCert = c;
    }

    /** [optional] set client certificate by file path.
     * @sa setClientCertificate()
     */
    void            setClientCertificate(const QString& certFilePath) {
        setClientCertificate( am::Ssl::loadCertificate(certFilePath) );
    }


protected slots:
    virtual void    onEncrypted();

protected:
    /** client's certificate to be verified. default is a null certificate. */
    QSslCertificate iclientCert;
};

///////////////////////////////////////////////////////////////////////////////
} // namespace am
///////////////////////////////////////////////////////////////////////////////

/** @class am::ServerSideSslSocket
 * a server-side SSL socket class.
 * usage:
 * @code
    class EchoEngine : public am::ServerSideSslSocket
    {
    public:
        explicit        EchoEngine(QObject* parent = 0) :  am::ServerSideSslSocket(parent) {

            QObject::connect(this, &EchoEngine::disconnected, [this](){
                this->deleteLater();
            });

            QObject::connect(this, &EchoEngine::connectionVerified, [this](){
                // do something useful
            });

            QObject::connect(this, &EchoEngine::readyRead, [this](){
                // do something useful
            });
        }
    };

    class EchoServer : public QTcpServer
    {
    public:
        virtual void    incomingConnection(qintptr sokDesc) {
            // loading private key and local certificate from qrc.
            EchoEngine *echo = new EchoEngine(this);
            echo->setPKI(":/pkey", ":/cert");

            // force to drop un-certified clients!
            echo->setClientCertificate(":/client_cert");
            echo->setSocketDescriptor(sokDesc);
        }
    };
 * @endcode
 */

#endif // SERVERSIDESSLSOCKET_HPP
