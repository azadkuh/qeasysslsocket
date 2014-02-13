TARGET     = appclient
TEMPLATE   = app

include(../commondir.pri)

HEADERS   += \
    ../../lib/sslsocketbase.hpp \
    ../../lib/clientsidesslsocket.hpp

SOURCES   += \
    main.cpp \
    ../../lib/sslsocketbase.cpp \
    ../../lib/clientsidesslsocket.cpp


LIBS      +=

RESOURCES += ../res/appclient.qrc

