/*
  Wlan-navi project.
  Copyright (C) 2011  Wlan-navi team.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "mainwindow.h"

#include <QCoreApplication>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QAction>
#include <QVBoxLayout>
#include <QMap>
#include <QtGui/QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <QDebug>
#ifdef Q_WS_MAEMO_5
    #include <QMaemo5InformationBox>
#endif

/**
    Initialize MainWindow
*/
MainWindow::MainWindow() :
    serviceProvider(0),
    positionSource(0),
    tracking(true),
    firstUpdate(true)
{
    //For auto-rotation, currently unsupported
    //setAttribute(Qt::WA_Maemo5AutoOrientation, true);

    // our actual maps widget is the centre of the mainwindow
    mapsWidget = new MapsWidget;
    setCentralWidget(mapsWidget);

    // set up the menus
    QMenuBar *mbar = new QMenuBar(this);
    mbar->addAction("My Location", this, SLOT(goToMyLocation()));
    mbar->addAction("Update wifi status", this, SLOT(updateWlan()));
    mbar->addAction("Available wlans", this, SLOT(showWlanAvailableWindow()));

    setMenuBar(mbar);
    setWindowTitle("wlan-navi");

    // now begin the process of opening the network link
    netConfigManager = new QNetworkConfigurationManager;
    connect(netConfigManager, SIGNAL(updateCompleted()),
            this, SLOT(openNetworkSession()));
    netConfigManager->updateConfigurations();

    //TODO: load wlan database

    this->grabZoomKeys(true);
    this->initializeWlan();
}

/**
  Update wlan status
*/
void MainWindow::updateWlan()
{
    wlanInterface->UpdateNetworks();
    #ifdef Q_WS_MAEMO_5
        QMaemo5InformationBox::information(this, "Wifi status updated");
    #endif
        qDebug() << "\n SIZE:" << wlans.size() << "\n";
}

/**
  Initialize wlan interface
*/
void MainWindow::initializeWlan()
{
    wlanInterface = new WlanMaemo();
    wlanInterface->setWlans(&wlans);
    wlanInterface->UpdateNetworks();
    if(wlanInterface->networks.size() > 0){
        Network net = wlanInterface->networks.front();

        qDebug() << QString::fromStdString(net.essid) << "\n";
    }
}

/**
  Open a network connection
*/
void MainWindow::openNetworkSession()
{
    session = new QNetworkSession(netConfigManager->defaultConfiguration());
    if (session->isOpen()) {
        initialize();
    } else {
        connect(session, SIGNAL(opened()),
                this, SLOT(initialize()));
        session->open();
    }
}

MainWindow::~MainWindow()
{
    delete mapsWidget;
    if (serviceProvider)
        delete serviceProvider;
}

/**
  Show our position
*/
void MainWindow::goToMyLocation()
{
    mapsWidget->map()->setFocus();
    tracking = true;
}

/**
  Set up the mapsWidget
*/
void MainWindow::initialize()
{
    if (serviceProvider)
        delete serviceProvider;

    QList<QString> providers = QGeoServiceProvider::availableServiceProviders();

    for (int i = 0; i < providers.size(); ++i)
       qDebug() << providers.at(i).toLocal8Bit().constData() << endl;

    if (providers.size() < 1) {
        QMessageBox::information(this, tr("Wlan-navi problem"),
                                 tr("No service providers are available"));
        QCoreApplication::quit();
        return;
    }

    serviceProvider = new QGeoServiceProvider(loadQGeoPlugin());

    mapsWidget->initialize(serviceProvider->mappingManager());
    connect(mapsWidget, SIGNAL(mapPanned()),
            this, SLOT(disableTracking()));

    if (positionSource)
        delete positionSource;

    positionSource = QGeoPositionInfoSource::createDefaultSource(this);

    if (!positionSource) {
        mapsWidget->setMyLocation(QGeoCoordinate(51.11, 17.022222));
    } else {
        me = new Marker(Marker::MyLocationMarker);
        positionSource->setUpdateInterval(1000);
        connect(positionSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(updateMyPosition(QGeoPositionInfo)));
        positionSource->startUpdates();
    }

}

/**
  Load settings // QGeoServiceProvider plugin for maps
*/
QString MainWindow::loadQGeoPlugin()
{
    QString plugin = "";

    GetKey(&plugin);
    if(!plugin.compare("nokia") || !plugin.compare("openstreetmap"))
        return plugin;
    else
        return "openstreetmap";
}

/**
  Save value via GConf
*/
void MainWindow::StoreKey(QString value)
{
    GConfClient* gconfClient = gconf_client_get_default();
    g_assert(GCONF_IS_CLIENT(gconfClient));

    if(!gconf_client_set_string(gconfClient, GCONF_DIR "qgeoplugin", value.toAscii(), NULL)) {
      qDebug() << "Failed to set QGeoService plugin!";
    }

    g_object_unref(gconfClient);
}

/**
  Load value via GConf
*/
void MainWindow::GetKey(QString *value)
{
    GConfClient* gconfClient = gconf_client_get_default();

    g_assert(GCONF_IS_CLIENT(gconfClient));

    GConfValue* gcValue = NULL;
    gcValue = gconf_client_get_without_default(gconfClient, GCONF_DIR "qgeoplugin", NULL);

    if(gcValue == NULL) {
      g_warning(" key %sqgeoplugin not found\n", GCONF_DIR);
      g_object_unref(gconfClient);
      return;
    }

    if(gcValue->type == GCONF_VALUE_STRING) {
      *value = gconf_value_get_string(gcValue);
    }
    else {
      g_warning(" key %smykey is not string\n", GCONF_DIR);
    }

    gconf_value_free(gcValue);
    g_object_unref(gconfClient);
}

void MainWindow::disableTracking()
{
    tracking = false;
}

/**
  Locate us on a map
*/
void MainWindow::updateMyPosition(QGeoPositionInfo info)
{
    if (mapsWidget) {
        mapsWidget->setMyLocation(info.coordinate(), false);
        if (tracking)
            mapsWidget->animatedPanTo(info.coordinate());

        me->setCoordinate(info.coordinate());
        mapsWidget->geomap->addMapObject(me);
    }
    if (firstUpdate) {
        firstUpdate = false;
    }

}

void MainWindow::showNavigateDialog()
{

}

void MainWindow::showSearchDialog()
{

}

void MainWindow::showWlanAvailableWindow()
{
    WlanAvailable *window = new WlanAvailable(this);
    window->setAttribute(Qt::WA_Maemo5StackedWindow);
    //window->setWlans(&wlans);
    window->show();

}

void MainWindow::grabZoomKeys(bool grab)
{
    #ifdef Q_WS_MAEMO_5
        if (!winId()) {
            qWarning("Can't grab keys unless we have a window id");
            return;
        }

        unsigned long val = (grab) ? 1 : 0;
        Atom atom = XInternAtom(QX11Info::display(), "_HILDON_ZOOM_KEY_ATOM", False);
        if (!atom) {
            qWarning("Unable to obtain _HILDON_ZOOM_KEY_ATOM. This will only work "
                    "on a Maemo 5 device!");
            return;
        }

        XChangeProperty (QX11Info::display(),
                winId(),
                atom,
                XA_INTEGER,
                32,
                PropModeReplace,
                reinterpret_cast<unsigned char *>(&val),
                1);
    #endif
}

void MainWindow::toggleFullScreen()
{
    bool isFullScreen = windowState() & Qt::WindowFullScreen;

    if (isFullScreen)
        showNormal();
    else
        showFullScreen();
}
