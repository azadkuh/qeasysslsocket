# qeasysslsocket (Qt5+)
a small set of classes to simplify mutual authentication by QSslSocket 
esp. when you want to use self-signed certificates (without any CA)
> tested under Ubuntu Server (12.04) and OS X (10.9)


**Table Of Contents:**

- [class list](#class-list)
- [usage](#usage)
  - [keys](#1-create-keys)
  - [server](#2-ssl-server)
  - [client](#3-ssl-client)
- [examples](#examples)


## class list
at the moment current classes are presented:

+ `am::Ssl`  
a utility class for loading a QSslKey or QSslCertificate from a file path (or *qresource*).
+ `am::SslSocketBase`  
base class for SSL client / server classes.
+ `am::ServerSideSslSocket`  
server-side SSL socket class.
+ `am::ClientSideSslSocket`  
client-side SSL socket class.

[back to top](#table-of-contents)


# usage

## 1. create keys
a pair of **private key** + **certificate** is required for clients and the server.  
please have a look at [`examples/res/create_client_certificate.sh`](./examples/res/create_client_certificate.sh) and [`examples/res/create_client_certificate.sh`](./examples/res/create_client_certificate.sh) if you like to create new pairs.

[back to top](#table-of-contents)


## 2. SSL server
create a socket class based on `am::ServerSideSslSocket` first (core logic implementation):
```c++
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
```

then use it in a normal TCP server as:
```cpp
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
```

and somewhere in your code:
```cpp
quint16 portNumber = 4433;
EchoServer  svc(&app);
if ( !svc.listen(QHostAddress::Any, portNumber) ) {
    qDebug("failed to listen on %d !\nserver closed.", portNumber);
    return 0;
}
```




to test the server you can use openssl in a console:  
`$> openssl s_client -connect 127.0.0.1:4433`  
the server should block this connection because the client certificate is not yet specified.

`$> openssl s_client -connect 127.0.0.1:4433 -cert client-cert.pem -key client-pkey.pem`  
if the `client-cert.pem` is same as `":/client_cert"` of above code, then the client should be connected.

[back to top](#table-of-contents)




## 3. SSL client
create a socket class first:
```cpp
class TestSslSocket : public am::ClientSideSslSocket
{
public:
    TestSslSocket(QObject* parent = 0) : am::ClientSideSslSocket(parent) {
        
        QObject::connect(this, &QSslSocket::encrypted, [this](){
            // do something useful
        });
        
        QObject::connect(this, &QSslSocket::readyRead, [this](){
            // do something useful
        });
    }
};
```

then to make a connection:
```cpp
TestSslSocket sok(&app);
sok.setPKI(":/pkey", ":/cert");
sok.setServerCertificate(":/server_cert");
sok.connectToHostEncrypted("127.0.0.1", 4433);
```

the client can be connected to a test openssl server:  
`$> openssl s_server 4433 -cert server_cert.pem -key server_key.pem`

[back to top](#table-of-contents)  


# examples
`example` directory provides two samples:

+ **echo server**:  a simple echo server implemented by `am::ServerSideSslSocket`. this server simply returns every message it get from a client.
+ **echo client**: a simple client implemented by `am::ClientSideSslSocket`. send some text to an SSL server.

[back to top](#table-of-contents)


