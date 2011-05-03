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

#include "mapswidget.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTimer>
#include <QDebug>
#include <QPixmap>

#include "qgeocoordinate.h"

GeoMap::GeoMap(QGeoMappingManager *manager, MapsWidget *mapsWidget) :
    QGraphicsGeoMap(manager), mapsWidget(mapsWidget)
{
    this->setFocus();
    connect(this, SIGNAL(mapTouched()), mapsWidget, SLOT(showFullscreenButton()));
}

GeoMap::~GeoMap()
{
}

double GeoMap::centerLatitude() const
{
    return center().latitude();
}

double GeoMap::centerLongitude() const
{
    return center().longitude();
}

void GeoMap::setCenterLatitude(double lat)
{
    QGeoCoordinate c = center();
    c.setLatitude(lat);
    setCenter(c);
}

void GeoMap::setCenterLongitude(double lon)
{
    QGeoCoordinate c = center();
    c.setLongitude(lon);
    setCenter(c);
}

void GeoMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    panActive = true;

    this->setFocus();
    event->accept();
}

void GeoMap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    panActive = false;

    emit mapTouched();
    this->setFocus();
    event->accept();
}

void GeoMap::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (panActive) {
        QPointF delta = event->lastPos() - event->pos();
        pan(delta.x(), delta.y());
        emit panned();
    }

    this->setFocus();
    event->accept();
}

void GeoMap::wheelEvent(QGraphicsSceneWheelEvent *event)
{

}

void GeoMap::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_F7:
            if (zoomLevel() < maximumZoomLevel()) {
                setZoomLevel(zoomLevel() + 1);
            }
            break;
        case Qt::Key_F8:
            if (zoomLevel() > minimumZoomLevel()) {
                setZoomLevel(zoomLevel() - 1);
            }
            break;
    }
    emit mapTouched();
    this->setFocus();
    event->accept();
}

FixedGraphicsView::FixedGraphicsView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
}

void FixedGraphicsView::scrollContentsBy(int dx, int dy)
{
    Q_UNUSED(dx)
    Q_UNUSED(dy)
}

MapsWidget::MapsWidget(QWidget *parent) :
    QWidget(parent)
{
    geomap = 0;
    view = 0;
}

MapsWidget::~MapsWidget()
{
}

void MapsWidget::initialize(QGeoMappingManager *manager)
{
    geomap = new GeoMap(manager, this);

    connect(geomap, SIGNAL(panned()),
            this, SIGNAL(mapPanned()));

    QGraphicsScene *sc = new QGraphicsScene;
    sc->addItem(geomap);

    geomap->setPos(0, 0);
    geomap->resize(this->size());

    view = new FixedGraphicsView(sc, this);
    view->setVisible(true);
    view->setInteractive(true);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    fsButtonItem = new FullscreenButtonItem(geomap);
    sc->addItem(fsButtonItem);
    sc->addItem(fsButtonItem->fsPixmap);
    connect(fsButtonItem, SIGNAL(mouseReleaseEventSignal()), this->parentWidget(), SLOT(toggleFullScreen()));
    fsButtonItem->timer = new QTimer(this);
    fsButtonItem->timer->setInterval(500);
    connect(fsButtonItem->timer, SIGNAL(timeout()), fsButtonItem, SLOT(onTimeOut()));
    fsButtonItem->timer->start();

    view->resize(this->size());
    view->centerOn(geomap);

    Marker *me = new Marker(Marker::MyLocationMarker);
    me->setCoordinate(QGeoCoordinate(51.11, 17.022222));
    geomap->addMapObject(me);


    Marker *wlan = new Marker(Marker::StartMarker);
    wlan->setCoordinate(QGeoCoordinate(51.112, 17.022225));
    geomap->addMapObject(wlan);

    resizeEvent(0);

    //Ugly hack for resizing mapsWidget, without that it has 800x423 (wtf!?)
    if(width() > height())
    {
        //We are in landscape mode
        view->resize(802,424);
        geomap->resize(800 - 2, 424 - 2);
    }
    else
    {
        //We are in portrait mode
        view->resize(482, 744);
        geomap->resize(480 - 2, 744 - 2);
    }
    view->centerOn(geomap);
    geomap->setCenter(QGeoCoordinate(51.11, 17.022222));
    geomap->setZoomLevel(15);

}

void MapsWidget::showFullscreenButton()
{
    fsButtonItem->fsPixmap->show();
    fsButtonItem->timer->start();
}

void MapsWidget::setMyLocation(QGeoCoordinate location, bool center)
{
    if (geomap && center)
        geomap->setCenter(location);
}

QGraphicsGeoMap *MapsWidget::map() const
{
    return geomap;
}

void MapsWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    if (view && geomap) {
        view->resize(size());
        geomap->resize(width()-2, height()-2);
        view->centerOn(geomap);

        fsButtonItem->setRect(width() - 48, height() - 48, 48, 48);
    }
}

void MapsWidget::animatedPanTo(QGeoCoordinate center)
{
    if (!geomap)
        return;

    QPropertyAnimation *latAnim = new QPropertyAnimation(geomap, "centerLatitude");
    latAnim->setEndValue(center.latitude());
    latAnim->setDuration(200);
    QPropertyAnimation *lonAnim = new QPropertyAnimation(geomap, "centerLongitude");
    lonAnim->setEndValue(center.longitude());
    lonAnim->setDuration(200);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(latAnim);
    group->addAnimation(lonAnim);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void MapsWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    resizeEvent(0);
}

FullscreenButtonItem::FullscreenButtonItem(GeoMap *map)
{
    map = map;
    pressedFullscreenButton = false;

    setPen(QPen(QBrush(), 0));
    setBrush(QBrush(Qt::transparent));

    fsPixmap = new QGraphicsPixmapItem(QPixmap("/usr/share/icons/hicolor/48x48/hildon/general_fullsize.png"));
}

void FullscreenButtonItem::setRect(qreal x, qreal y, qreal w, qreal h)
{
    QGraphicsRectItem::setRect(x, y, w, h);

    QRectF fsBound = fsPixmap->boundingRect();
    QPointF fsCenter(x+w/2.0, y+h/2.0);
    QPointF fsDelta = fsCenter - fsBound.center();
    fsPixmap->setPos(fsDelta);

}

void FullscreenButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    const QPointF pos = event->pos();

    pressedFullscreenButton = true;
    timer->start();
    fsPixmap->show();
    event->accept();
}

void FullscreenButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseReleaseEventSignal();
    pressedFullscreenButton = false;
    event->accept();
}

void FullscreenButtonItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void FullscreenButtonItem::onTimeOut()
{
    this->fsPixmap->hide();
    this->timer->stop();
}
