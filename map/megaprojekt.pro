QT += network

TARGET = megaprojekt
TEMPLATE = app

RESOURCES += megaprojekt.qrc

#include(../mobility_examples.pri)

#INCLUDEPATH += ../../src/location \
#               ../../src/location/maps \
#               ../../src/location/maps/tiled \
#               ../../src/location/landmarks

CONFIG += mobility
MOBILITY += location
equals(QT_MAJOR_VERSION, 4):lessThan(QT_MINOR_VERSION, 7){
    MOBILITY += bearer
#    INCLUDEPATH += ../../src/bearer
} else {
    # use Bearer Management classes in QtNetwork module
}

symbian: {
    TARGET.CAPABILITY = Location \
                        NetworkServices \
                        ReadUserData \
                        WriteUserData
}

HEADERS += \
    mapswidget.h \
    mainwindow.h \
    marker.h

SOURCES += \
    mapswidget.cpp \
    main.cpp \
    mainwindow.cpp \
    marker.cpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/bin
    } else {
        target.path = /usr/local/bin
    }
    INSTALLS += target
}
