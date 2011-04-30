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

#include <iostream>

using namespace std;


/**
    Initialize MainWindow
*/
MainWindow::MainWindow() :
    serviceProvider(0),
    positionSource(0),
    tracking(true),
    firstUpdate(true)
{
    // our actual maps widget is the centre of the mainwindow
    mapsWidget = new MapsWidget;
    setCentralWidget(mapsWidget);

    // set up the menus
    QMenuBar *mbar = new QMenuBar(this);
    mbar->addAction("My Location", this, SLOT(goToMyLocation()));

    setMenuBar(mbar);
    setWindowTitle("wlan-navi");

    // now begin the process of opening the network link
    netConfigManager = new QNetworkConfigurationManager;
    connect(netConfigManager, SIGNAL(updateCompleted()),
            this, SLOT(openNetworkSession()));
    netConfigManager->updateConfigurations();

    this->grabZoomKeys(true);
    this->initializeWlan();
}

/**
  Initialize wlan interface
*/
void MainWindow::initializeWlan()
{
    wlanInterface = new WlanMaemo();
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
       cout << providers.at(i).toLocal8Bit().constData() << endl;

    if (providers.size() < 1) {
        QMessageBox::information(this, tr("Wlan-navi problem"),
                                 tr("No service providers are available"));
        QCoreApplication::quit();
        return;
    }

    serviceProvider = new QGeoServiceProvider("openstreetmap");

    mapsWidget->initialize(serviceProvider->mappingManager());
    connect(mapsWidget, SIGNAL(mapPanned()),
            this, SLOT(disableTracking()));

    if (positionSource)
        delete positionSource;

    positionSource = QGeoPositionInfoSource::createDefaultSource(this);

    if (!positionSource) {
        mapsWidget->setMyLocation(QGeoCoordinate(51.11, 17.022222));
    } else {
        positionSource->setUpdateInterval(1000);
        connect(positionSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(updateMyPosition(QGeoPositionInfo)));
        positionSource->startUpdates();
    }

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
