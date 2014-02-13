#include "include/config.hpp"
#include "clientsidesslsocket.hpp"

#include <QtCore/QCoreApplication>
#include <QtNetwork/QSslSocket>
////////////////////////////////////////////////////////////////////////////////
class TestSslSocket : public am::ClientSideSslSocket
{
public:
    TestSslSocket(QObject* parent = 0) : am::ClientSideSslSocket(parent) {

        QObject::connect(this, &QSslSocket::encrypted, [this](){
            qDebug("connected to SSL socket");

            char stdinBuffer[257] = {0};
            fread(stdinBuffer, 1, 256, stdin);
            write(stdinBuffer);
            flush();
        });

        QObject::connect(this, &QSslSocket::readyRead, [this](){
            QByteArray incommingData = readAll();
            qDebug("server says: %s", incommingData.constData());
        });

    }
};

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv) {
    QCoreApplication app(argc, argv);

    // default ip:port
    uint16_t portNumber     = 4433;
    QString  ipAddress      = "127.0.0.1";

    // try to update from command line arguments
    QStringList args = app.arguments();
    if ( args.size() >= 2 ) {
        QStringList server = args.at(1).split(':', QString::SkipEmptyParts);
        if ( server.size() >= 1)
            ipAddress   = server.at(0);
        if ( server.size() >= 2 )
            portNumber  = (uint16_t) server.at(1).toInt();
    }


    // socket
    TestSslSocket   sok(&app);
    sok.setPKI(":/pkey", ":/cert");
    sok.setServerCertificate(":/server_cert");
    qDebug("connecting to %s:%d", qPrintable(ipAddress), portNumber);
    sok.connectToHostEncrypted(ipAddress, portNumber);

    QObject::connect(&sok, &QSslSocket::disconnected, [&app](){
        app.quit();
    });

    app.exec();
}

