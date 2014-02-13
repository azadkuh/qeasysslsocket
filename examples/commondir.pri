QT        += core network
QT        -= gui
CONFIG    += c++11


unix {
    TEMPDIR          = ../../tmp/unix/$$TARGET
    QMAKE_CFLAGS    += -std=gnu99
    QMAKE_CXXFLAGS  += -Wno-unused-parameter
}
macx {
    CONFIG          -= app_bundle
}
win32 {
    TEMPDIR          = ../../tmp/win32/$$TARGET
    warning(sorry! I don`t have enough time or interest to test and verify this code under Windows. please contribute by testing and give me your feedback.)
}



# specifying common dirs
INCLUDEPATH    +=  . ../../ ../../lib

DESTDIR         = ../../xbin
DEPENDPATH     += ../../xbin
UI_DIR          = $$TEMPDIR/Ui
MOC_DIR         = $$TEMPDIR
RCC_DIR         = $$TEMPDIR
OBJECTS_DIR     = $$TEMPDIR
