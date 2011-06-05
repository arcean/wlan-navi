#############################################################################
# Makefile for building: wlan_navi
# Generated by qmake (2.01a) (Qt 4.7.3) on: niedz. cze 5 02:19:57 2011
# Project:  wlan_navi.pro
# Template: app
# Command: /home/Tomek/QtSDK/Simulator/Qt/gcc/bin/qmake -spec /home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/linux-g++-64 CONFIG+=debug -o Makefile wlan_navi.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB
CFLAGS        = -m64 -pipe -g -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -pthread -I/usr/include/hildon-1 -I/usr/include/gtk-2.0 -I/usr/lib64/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/dbus-1.0 -I/usr/lib64/dbus-1.0/include -DORBIT2=1 -pthread -I/usr/include/gconf/2 -I/usr/include/orbit-2.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -pthread -I/usr/include/hildon-1 -I/usr/include/gtk-2.0 -I/usr/lib64/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/dbus-1.0 -I/usr/lib64/dbus-1.0/include -DORBIT2=1 -pthread -I/usr/include/gconf/2 -I/usr/include/orbit-2.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/linux-g++-64 -I. -I/home/Tomek/QtSDK/Simulator/Qt/gcc/include/QtCore -I/home/Tomek/QtSDK/Simulator/Qt/gcc/include/QtNetwork -I/home/Tomek/QtSDK/Simulator/Qt/gcc/include/QtGui -I/home/Tomek/QtSDK/Simulator/Qt/gcc/include -I/home/Tomek/QtSDK/Simulator/Qt/gcc/include/QtLocation -I/home/Tomek/QtSDK/Simulator/Qt/gcc/include/QtMobilitySimulator -I/home/Tomek/QtSDK/Simulator/QtMobility/gcc/include -I/home/Tomek/QtSDK/Simulator/QtMobility/gcc/include/QtMobility -I/home/Tomek/QtSDK/Simulator/QtMobility/gcc/include/QtLocation -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-rpath,/home/Tomek/QtSDK/Simulator/Qt/gcc/lib -Wl,-rpath,/home/Tomek/QtSDK/Simulator/QtMobility/gcc/lib
LIBS          = $(SUBLIBS)  -L/home/Tomek/QtSDK/Simulator/Qt/gcc/lib -pthread -lhildon-1 -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lpng12 -lm -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -L/lib64 -ldbus-1 -lrt -lgconf-2 -lglib-2.0 -L/home/Tomek/QtSDK/Simulator/QtMobility/gcc/lib -lQtMobilitySimulator -lQtLocation -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /home/Tomek/QtSDK/Simulator/Qt/gcc/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		mapswidget.cpp \
		WlanMaemo.cpp \
		marker.cpp \
		wlanavailable.cpp \
		config.cpp \
		settings.cpp moc_mainwindow.cpp \
		moc_mapswidget.cpp \
		moc_WlanMaemo.cpp \
		moc_marker.cpp \
		moc_wlanavailable.cpp \
		moc_settings.cpp \
		qrc_wlan_navi.cpp
OBJECTS       = main.o \
		mainwindow.o \
		mapswidget.o \
		WlanMaemo.o \
		marker.o \
		wlanavailable.o \
		config.o \
		settings.o \
		moc_mainwindow.o \
		moc_mapswidget.o \
		moc_WlanMaemo.o \
		moc_marker.o \
		moc_wlanavailable.o \
		moc_settings.o \
		qrc_wlan_navi.o
DIST          = /home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/common/g++.conf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/common/unix.conf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/common/linux.conf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/qconfig.pri \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/modules/qt_webkit_version.pri \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/qt_functions.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/qt_config.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/exclusive_builds.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/default_pre.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/debug.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/default_post.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/link_pkgconfig.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/mobility.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/warn_on.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/qt.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/unix/thread.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/moc.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/resources.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/uic.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/yacc.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/lex.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/include_source_dir.prf \
		wlan_navi.pro
QMAKE_TARGET  = wlan_navi
DESTDIR       = 
TARGET        = wlan_navi

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_wlanavailable.h ui_settings.h ui_markerinfo.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: wlan_navi.pro  /home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/linux-g++-64/qmake.conf /home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/common/g++.conf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/common/unix.conf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/common/linux.conf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/qconfig.pri \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/modules/qt_webkit_version.pri \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/qt_functions.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/qt_config.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/exclusive_builds.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/default_pre.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/debug.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/default_post.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/link_pkgconfig.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/mobility.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/warn_on.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/qt.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/unix/thread.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/moc.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/resources.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/uic.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/yacc.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/lex.prf \
		/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/include_source_dir.prf \
		/home/Tomek/QtSDK/Simulator/QtMobility/gcc/lib/libQtMobilitySimulator.prl \
		/home/Tomek/QtSDK/Simulator/QtMobility/gcc/lib/libQtLocation.prl
	$(QMAKE) -spec /home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/linux-g++-64 CONFIG+=debug -o Makefile wlan_navi.pro
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/common/g++.conf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/common/unix.conf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/common/linux.conf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/qconfig.pri:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/modules/qt_webkit_version.pri:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/qt_functions.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/qt_config.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/exclusive_builds.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/default_pre.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/debug.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/default_post.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/link_pkgconfig.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/mobility.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/warn_on.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/qt.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/unix/thread.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/moc.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/resources.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/uic.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/yacc.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/lex.prf:
/home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/features/include_source_dir.prf:
/home/Tomek/QtSDK/Simulator/QtMobility/gcc/lib/libQtMobilitySimulator.prl:
/home/Tomek/QtSDK/Simulator/QtMobility/gcc/lib/libQtLocation.prl:
qmake:  FORCE
	@$(QMAKE) -spec /home/Tomek/QtSDK/Simulator/Qt/gcc/mkspecs/linux-g++-64 CONFIG+=debug -o Makefile wlan_navi.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/wlan_navi1.0.0 || $(MKDIR) .tmp/wlan_navi1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/wlan_navi1.0.0/ && $(COPY_FILE) --parents mainwindow.h mapswidget.h WlanMaemo.h marker.h wlanavailable.h config.h settings.h .tmp/wlan_navi1.0.0/ && $(COPY_FILE) --parents wlan_navi.qrc .tmp/wlan_navi1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp mapswidget.cpp WlanMaemo.cpp marker.cpp wlanavailable.cpp config.cpp settings.cpp .tmp/wlan_navi1.0.0/ && $(COPY_FILE) --parents wlanavailable.ui settings.ui markerinfo.ui .tmp/wlan_navi1.0.0/ && (cd `dirname .tmp/wlan_navi1.0.0` && $(TAR) wlan_navi1.0.0.tar wlan_navi1.0.0 && $(COMPRESS) wlan_navi1.0.0.tar) && $(MOVE) `dirname .tmp/wlan_navi1.0.0`/wlan_navi1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/wlan_navi1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_mapswidget.cpp moc_WlanMaemo.cpp moc_marker.cpp moc_wlanavailable.cpp moc_settings.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_mapswidget.cpp moc_WlanMaemo.cpp moc_marker.cpp moc_wlanavailable.cpp moc_settings.cpp
moc_mainwindow.cpp: mapswidget.h \
		marker.h \
		WlanMaemo.h \
		wlanavailable.h \
		mainwindow.h \
		settings.h \
		config.h \
		mainwindow.h
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_mapswidget.cpp: marker.h \
		WlanMaemo.h \
		mapswidget.h
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/moc $(DEFINES) $(INCPATH) mapswidget.h -o moc_mapswidget.cpp

moc_WlanMaemo.cpp: marker.h \
		WlanMaemo.h
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/moc $(DEFINES) $(INCPATH) WlanMaemo.h -o moc_WlanMaemo.cpp

moc_marker.cpp: marker.h
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/moc $(DEFINES) $(INCPATH) marker.h -o moc_marker.cpp

moc_wlanavailable.cpp: WlanMaemo.h \
		marker.h \
		mainwindow.h \
		mapswidget.h \
		wlanavailable.h \
		settings.h \
		config.h \
		wlanavailable.h
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/moc $(DEFINES) $(INCPATH) wlanavailable.h -o moc_wlanavailable.cpp

moc_settings.cpp: config.h \
		settings.h
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/moc $(DEFINES) $(INCPATH) settings.h -o moc_settings.cpp

compiler_rcc_make_all: qrc_wlan_navi.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_wlan_navi.cpp
qrc_wlan_navi.cpp: wlan_navi.qrc \
		icons/openwlanmarker.png \
		icons/pathmarker.png \
		icons/endmarker.png \
		icons/waypointmarker.png \
		icons/mylocation.png \
		icons/searchmarker.png \
		icons/startmarker.png
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/rcc -name wlan_navi wlan_navi.qrc -o qrc_wlan_navi.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_wlanavailable.h ui_settings.h ui_markerinfo.h
compiler_uic_clean:
	-$(DEL_FILE) ui_wlanavailable.h ui_settings.h ui_markerinfo.h
ui_wlanavailable.h: wlanavailable.ui
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/uic wlanavailable.ui -o ui_wlanavailable.h

ui_settings.h: settings.ui
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/uic settings.ui -o ui_settings.h

ui_markerinfo.h: markerinfo.ui
	/home/Tomek/QtSDK/Simulator/Qt/gcc/bin/uic markerinfo.ui -o ui_markerinfo.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		mapswidget.h \
		marker.h \
		WlanMaemo.h \
		wlanavailable.h \
		settings.h \
		config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		mapswidget.h \
		marker.h \
		WlanMaemo.h \
		wlanavailable.h \
		settings.h \
		config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

mapswidget.o: mapswidget.cpp mapswidget.h \
		marker.h \
		WlanMaemo.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mapswidget.o mapswidget.cpp

WlanMaemo.o: WlanMaemo.cpp WlanMaemo.h \
		marker.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WlanMaemo.o WlanMaemo.cpp

marker.o: marker.cpp marker.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o marker.o marker.cpp

wlanavailable.o: wlanavailable.cpp wlanavailable.h \
		WlanMaemo.h \
		marker.h \
		mainwindow.h \
		mapswidget.h \
		settings.h \
		config.h \
		ui_wlanavailable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o wlanavailable.o wlanavailable.cpp

config.o: config.cpp config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o config.o config.cpp

settings.o: settings.cpp settings.h \
		config.h \
		ui_settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o settings.o settings.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_mapswidget.o: moc_mapswidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mapswidget.o moc_mapswidget.cpp

moc_WlanMaemo.o: moc_WlanMaemo.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_WlanMaemo.o moc_WlanMaemo.cpp

moc_marker.o: moc_marker.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_marker.o moc_marker.cpp

moc_wlanavailable.o: moc_wlanavailable.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_wlanavailable.o moc_wlanavailable.cpp

moc_settings.o: moc_settings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_settings.o moc_settings.cpp

qrc_wlan_navi.o: qrc_wlan_navi.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_wlan_navi.o qrc_wlan_navi.cpp

####### Install

install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/usr/local/bin/ || $(MKDIR) $(INSTALL_ROOT)/usr/local/bin/ 
	-$(INSTALL_PROGRAM) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/usr/local/bin/$(QMAKE_TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/usr/local/bin/$(QMAKE_TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/local/bin/ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:

