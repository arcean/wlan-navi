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
	mapswidget.cpp

HEADERS  += mainwindow.h \
		mapswidget.h

FORMS    +=

CONFIG += mobility11
MOBILITY = location

symbian {
    TARGET.UID3 = 0xedb44722
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
