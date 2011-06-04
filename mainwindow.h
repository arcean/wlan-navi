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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <qnetworksession.h>
#include <qnetworkconfigmanager.h>

#include "qgeoserviceprovider.h"
#include "qgeopositioninfosource.h"
#include "qgeoroutereply.h"
#include "qgeocoordinate.h"

#include "mapswidget.h"
#include "WlanMaemo.h"
#include "marker.h"
#include "wlanavailable.h"
#include "settings.h"
#include "markerinfo.h"

using namespace QtMobility;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
    WlanMaemo *wlanInterface;

    QGeoCoordinate getMyCords();

    QList<Network> wlans;
    QList<Network> tempWlan;

public slots:
    void initialize();
    void toggleFullScreen();
    QString loadQGeoPlugin();

private slots:
    void showSearchDialog();
    void showNavigateDialog();
    void showWlanAvailableWindow();
    void showSettingsWindow();
    void showMarkerInfoWindow(Marker *marker);
    void goToMyLocation();

    void updateMyPosition(QGeoPositionInfo info);
    void disableTracking();
    void updateWlan();
    void updateWlanAddMarker();

    void setNetworkID(int i);
    bool checkIfExists(QString id);
    int getNetworkWithID(QString id);

    void openNetworkSession();
    void grabZoomKeys(bool grab);
    void initializeWlan();

private:
    QGeoServiceProvider *serviceProvider;
    MapsWidget *mapsWidget;
    QGeoPositionInfoSource *positionSource;

    QNetworkSession *session;
    QNetworkConfigurationManager *netConfigManager;

    bool tracking;
    bool firstUpdate;
    QGeoCoordinate myCords;

    Marker *me;
};

#endif // MAINWINDOW_H
