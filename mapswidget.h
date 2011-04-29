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

#ifndef MAPSWIDGET_H
#define MAPSWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>

#include "qgraphicsgeomap.h"
#include "qgeomappingmanager.h"
#include "qgeocoordinate.h"

using namespace QtMobility;

class MapsWidget;

// The graphics item that actually contains the map
class GeoMap : public QGraphicsGeoMap
{
    Q_OBJECT

    Q_PROPERTY(double centerLatitude READ centerLatitude WRITE setCenterLatitude)
    Q_PROPERTY(double centerLongitude READ centerLongitude WRITE setCenterLongitude)

public:
    explicit GeoMap(QGeoMappingManager *manager, MapsWidget *mapsWidget);
    ~GeoMap();

    double centerLatitude() const;
    void setCenterLatitude(double lat);
    double centerLongitude() const;
    void setCenterLongitude(double lon);

private:
    MapsWidget *mapsWidget;

    bool panActive;
    bool markerPressed;
    QGeoMapObject *pressed;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void panned();
    void mapTouched();
};

class FixedGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    FixedGraphicsView(QGraphicsScene *scene, QWidget *parent);

protected:
    void scrollContentsBy(int dx, int dy);
};

// A widget to hold the view and scene for a GeoMap, as well
// as control widgets
class MapsWidgetPrivate;
class MapsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapsWidget(QWidget *parent = 0);
    ~MapsWidget();

    QGraphicsGeoMap *map() const;

    void animatedPanTo(QGeoCoordinate center);
    void setMyLocation(QGeoCoordinate location, bool center=true);

public slots:
    void initialize(QGeoMappingManager *manager);
    void showFullscreenButton();

signals:
    void mapPanned();

private:
    MapsWidgetPrivate *d;

    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
};

class FullscreenButtonItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit FullscreenButtonItem(GeoMap *map);

    QGraphicsPixmapItem *fsPixmap;
    QTimer *timer;

    void setRect(qreal x, qreal y, qreal w, qreal h);

public slots:
    void onTimeOut();

private:
    GeoMap *map;
    bool pressedFullscreenButton;

signals:
    void mouseReleaseEventSignal();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MAPSWIDGET_H
