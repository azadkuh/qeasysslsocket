#include "include/config.hpp"
#include "serversidesslsocket.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtNetwork/QTcpServer>
////////////////////////////////////////////////////////////////////////////////
class EchoEngine : public am::ServerSideSslSocket
{
public:
    explicit        EchoEngine(QObject* parent = 0) :  am::ServerSideSslSocket(parent) {

        QObject::connect(this, &QSslSocket::disconnected, [this](){
            qDebug("socket %lld has been disconnected.", socketDescriptor());
            this->deleteLater();
        });

        QObject::connect(this, &EchoEngine::connectionVerified, [this](){
            qDebug("SSL connection is now connected and certified.");

            write("welcome to echo engine server!\n");
            flush();
        });

        QObject::connect(this, &EchoEngine::readyRead, [this](){
            QByteArray data = readAll();
            qDebug("client [%s:%d] says: %s",
                   qPrintable(peerAddress().toString()),
                   peerPort(),
                   data.constData());

            if ( data.startsWith("kill server") ) {
                qDebug("requset to quit by the client.");
                disconnectFromHost();
                QCoreApplication::instance()->quit();
            }

            write(QByteArray("    < server echoes: ").append(data));
            flush();
        });
    }
};
///////////////////////////////////////////////////////////////////////////////
/** an SSL server is nothing but an ordinary QTcpServer! */
class EchoServer : public QTcpServer
{
public:
    explicit        EchoServer(QObject* parent) : QTcpServer(parent) {
    }

    virtual void    incomingConnection(qintptr sokDesc) {
        // loading private key and local certificate from qrc.
        EchoEngine *echo = new EchoEngine(this);
        echo->setPKI(":/pkey", ":/cert");

        // force to drop un-certified clients!
        echo->setClientCertificate(":/client_cert");
        echo->setSocketDescriptor(sokDesc);
    }
};

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv) {
    QCoreApplication app(argc, argv);

    uint16_t portNumber     = 4433;

    // set listen port number from optional command line arguments.
    QStringList args = app.arguments();
    if ( args.size() >= 2 ) {
        portNumber = (uint16_t) args.at(1).toUInt();
    }


    EchoServer  svc(&app);
    if ( !svc.listen(QHostAddress::Any, portNumber) ) {
        qDebug("can not listen on %d !\nserver closed.", portNumber);
        return 0;
    }

    app.exec();
}
///////////////////////////////////////////////////////////////////////////////
