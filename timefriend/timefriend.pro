TEMPLATE = app

QT +=  widgets
QT += sql network

SOURCES += main.cpp \
    timelist.cpp \
    mainwindow.cpp \
    remind.cpp \
    tomate.cpp

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
    tomate.hxx

FORMS += \
    mainwindow.ui \
    remind.ui \
    tomate.ui