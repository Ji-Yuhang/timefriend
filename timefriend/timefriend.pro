TEMPLATE = app
DESTDIR = ../bin
QT +=  widgets
QT += sql network

SOURCES += main.cpp \
    timelist.cpp \
    mainwindow.cpp \
    remind.cpp \
    tomato.cpp \
    backtomain.cpp \
    test.cpp \
    database.cpp \
    user.cpp \
    uuid.cpp \
    eventtimeview.cpp \
    typesmodel.cpp \
    eventtimemodel.cpp \
    addeventtimeview.cpp \
    typesview.cpp

RESOURCES += qml.qrc
macx {
    QMAKE_INFO_PLIST = Info.plist
#    LIBS += -L/usr/local/mysql-5.6.20-osx10.8-x86_64/lib/ -lmysqld -lmysqlclient -v
}

DISTFILES += \
    Info.plist \
    bg.jpg

HEADERS += \
    timelist.hxx \
    mainwindow.hxx \
    remind.hxx \
    tomato.hxx \
    backtomain.h \
    test.h \
    database.h \
    user.h \
    uuid.h \
    eventtimeview.h \
    typesmodel.h \
    eventtimemodel.h \
    addeventtimeview.h \
    typesview.h

FORMS += \
    mainwindow.ui \
    remind.ui \
    tomate.ui \
    backtomain.ui \
    eventtimeview.ui \
    addeventtimeview.ui \
    typesview.ui
