#-------------------------------------------------
#
# Project created by QtCreator 2011-04-03T14:41:23
#
#-------------------------------------------------

QT       += core gui network maemo5

TARGET = wlan_navi
TEMPLATE = app

RESOURCES += wlan_navi.qrc

SOURCES += main.cpp\
        mainwindow.cpp\
	mapswidget.cpp \
    WlanMaemo.cpp \
    marker.cpp \
    wlanavailable.cpp

HEADERS  += mainwindow.h \
		mapswidget.h \
    WlanMaemo.h \
    marker.h \
    wlanavailable.h

FORMS    += \
    wlanavailable.ui
maemo5 {
    CONFIG += mobility11
} else {
    CONFIG += mobility
}

CONFIG += link_pkgconfig
PKGCONFIG += glib-2.0 liblocation hildon-1 dbus-1

MOBILITY = location

symbian {
    TARGET.UID3 = 0xedb44722
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/bin
    } else {
        target.path = /usr/local/bin
    }
    INSTALLS += target
}
