TARGET     = appserver
TEMPLATE   = app

include(../commondir.pri)

HEADERS   += \
    ../../lib/sslsocketbase.hpp \
    ../../lib/serversidesslsocket.hpp \
    ../../lib/sslkey.hpp


SOURCES   += \
    main.cpp \
    ../../lib/sslsocketbase.cpp \
    ../../lib/serversidesslsocket.cpp


LIBS      +=

RESOURCES += ../res/appserver.qrc
