#-------------------------------------------------
#
# Project created by QtCreator 2011-04-03T14:41:23
#
#-------------------------------------------------

QT       += core gui network

TARGET = wlan_navi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
	mapswidget.cpp \
    WlanMaemo.cpp

HEADERS  += mainwindow.h \
		mapswidget.h \
    WlanMaemo.h

FORMS    +=

CONFIG += mobility11

CONFIG += link_pkgconfig
PKGCONFIG += glib-2.0 liblocation hildon-1 dbus-1

MOBILITY = location

symbian {
    TARGET.UID3 = 0xedb44722
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
