/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"

#include <QCoreApplication>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QAction>
#include <QVBoxLayout>
#include <QMap>

#include <iostream>

using namespace std;


/**
Tworzy kontener na kolejne kontrolki
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

    setWindowTitle("Mapki");

    //otwieranie sygnalu z siecią (wifi)
    netConfigManager = new QNetworkConfigurationManager;
    connect(netConfigManager, SIGNAL(updateCompleted()),
            this, SLOT(openNetworkSession()));
    netConfigManager->updateConfigurations();
}

/**
  Otwiera połączenie z siecią
  */
void MainWindow::openNetworkSession()
{
    // standardowa konfiguracja sieci
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

//Trzeba zmienić żeby wskazywało na moją aktualną pozycję będzie trzeba wykorzystać gpsa
void MainWindow::goToMyLocation()
{
    mapsWidget->map()->setFocus();
    tracking = true;
}


//Inicjalizacja komponentów
void MainWindow::initialize()
{
    if (serviceProvider)
        delete serviceProvider;

    //dorzucam standardowych providerów
    QList<QString> providers = QGeoServiceProvider::availableServiceProviders();

    //QGeoServiceProvider serviceProvider("openstreetmap");
    //QGeoMappingManager *manager = serviceProvider.mappingManager();
    //QStringList ble = serviceProvider.availableServiceProviders ();

    //wyświetlanie dostępnych providerów (do sprawdzenia czy mamy OSM)
    for (int i = 0; i < providers.size(); ++i)
       cout << providers.at(i).toLocal8Bit().constData() << endl;


    //brak możliwych providerów
    if (providers.size() < 1) {
        QMessageBox::information(this, tr("Mapki problem"),
                                 tr("No service providers are available"));
        QCoreApplication::quit();
        return;
    }


    //dodawanie serwerów z tileami OSM
    QMap<QString, QVariant >  parameters;

      parameters["mapping.servers"] = QStringList("http://a.tile.opencyclemap.org/cycle/")
          << "http://b.tile.opencyclemap.org/cycle/"
          << "http://c.tile.opencyclemap.org/cycle/";




//    foreach (QString provider, providers) {
      //dodanie do sP OSM z podanymi wcześniej tileami
      serviceProvider = new QGeoServiceProvider("openstreetmap", parameters);

//
  //      if (serviceProvider->mappingManager() &&
    //            serviceProvider->searchManager() &&
      //          serviceProvider->routingManager())
            //break;
  //  }
/*
    if (serviceProvider->error() != QGeoServiceProvider::NoError) {
        QMessageBox::information(this, tr("Maps Demo"),
                                 tr("Error loading geoservice plugin"));
        QCoreApplication::quit();
        return;
    }

    if (!serviceProvider->mappingManager() ||
            !serviceProvider->searchManager() ||
            !serviceProvider->routingManager()) {
        QMessageBox::information(this, tr("Maps Demo"),
                                 tr("No geoservice found with mapping/search/routing"));
        QCoreApplication::quit();
        return;
    }
*/
    // start initialising things (maps, searching, routing)



    mapsWidget->initialize(serviceProvider->mappingManager());

    // Marker *mme = new Marker(Marker::MyLocationMarker);
    //  mme->setCoordinate(QGeoCoordinate(-27.5796, 153.1));
    //  d->map->addMapObject(mme);
    connect(mapsWidget, SIGNAL(mapPanned()),
            this, SLOT(disableTracking()));

    if (positionSource)
        delete positionSource;

    // set up position feeds (eg GPS)

    positionSource = QGeoPositionInfoSource::createDefaultSource(this);

    if (!positionSource) {
        mapsWidget->setMyLocation(QGeoCoordinate(51.11, 17.022222));//wrocław
        //mapsWidget->setMyLocation(QGeoCoordinate(-27.5796, 153.1));
        //mapsWidget->setMyLocation(QGeoCoordinate(21.1813, -86.8455));
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

//info do geo szerokość i długość geograficzna
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
