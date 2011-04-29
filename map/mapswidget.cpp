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

#include "mapswidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTimer>

#include "qgeocoordinate.h"

//
GeoMap::GeoMap(QGeoMappingManager *manager, MapsWidget *mapsWidget) :
    QGraphicsGeoMap(manager), mapsWidget(mapsWidget)
{
    this->setFocus();
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
}

void GeoMap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

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
{   qreal panx = event->pos().x() - size().width() / 2.0;
    qreal pany = event->pos().y() - size().height() / 2.0;
    pan(panx, pany);
    if (event->delta() > 0) {   // zoom in
        if (zoomLevel() < maximumZoomLevel()) {
            setZoomLevel(zoomLevel() + 1);
        }
    } else {                    // zoom out
        if (zoomLevel() > minimumZoomLevel()) {
            setZoomLevel(zoomLevel() - 1);
        }
    }
    pan(-panx, -pany);
    event->accept();
}

void GeoMap::keyPressEvent(QKeyEvent *event)
{
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


class MapsWidgetPrivate
{
public:
    GeoMap *map;
    QGraphicsView *view;
    ZoomButtonItem *zoomButtonItem;
};

MapsWidget::MapsWidget(QWidget *parent) :
    QWidget(parent),
    d(new MapsWidgetPrivate)
{
    d->map = 0;
    d->view = 0;
}

MapsWidget::~MapsWidget()
{
}

void MapsWidget::initialize(QGeoMappingManager *manager)
{
    d->map = new GeoMap(manager, this);

    connect(d->map, SIGNAL(panned()),
            this, SIGNAL(mapPanned()));

    QGraphicsScene *sc = new QGraphicsScene;
    sc->addItem(d->map);

    d->map->setPos(0, 0);
    d->map->resize(this->size());

    d->view = new FixedGraphicsView(sc, this);
    d->view->setVisible(true);
    d->view->setInteractive(true);
    d->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    d->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    d->view->resize(this->size());
    d->view->centerOn(d->map);

   // d->zoomButtonItem = new ZoomButtonItem(d->map);
   // sc->addItem(d->zoomButtonItem);


    //wstawianie markera

    Marker *me = new Marker(Marker::MyLocationMarker);
    me->setCoordinate(QGeoCoordinate(51.11, 17.022222));
    d->map->addMapObject(me);


    Marker *wlan = new Marker(Marker::StartMarker);
    wlan->setCoordinate(QGeoCoordinate(51.112, 17.022225));
    d->map->addMapObject(wlan);

    resizeEvent(0);



    d->map->setCenter(QGeoCoordinate(-51.11 , 17.0));
    d->map->setZoomLevel(50);


}

void MapsWidget::setMyLocation(QGeoCoordinate location, bool center)
{
    if (d->map && center)
        d->map->setCenter(location);

   // Marker *mme = new Marker(Marker::MyLocationMarker);
    //  mme->setCoordinate(QGeoCoordinate(-27.5796, 153.1));
    //  d->map->addMapObject(mme);
}

QGraphicsGeoMap *MapsWidget::map() const
{
    return d->map;
}


//nowe okno robi czasami problemy
void MapsWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    if (d->view && d->map) {
        d->view->resize(size());
        d->map->resize(width()-2, height()-2);
        d->view->centerOn(d->map);
    }
}

//przewijanie mapy
void MapsWidget::animatedPanTo(QGeoCoordinate center)
{
    if (!d->map)
        return;

    QPropertyAnimation *latAnim = new QPropertyAnimation(d->map, "centerLatitude");
    latAnim->setEndValue(center.latitude());
    latAnim->setDuration(200);

    QPropertyAnimation *lonAnim = new QPropertyAnimation(d->map, "centerLongitude");
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

/*********************************/

class ZoomButtonItemPrivate
{
public:
    GeoMap *map;

    QGraphicsSimpleTextItem *plusText;
    QGraphicsSimpleTextItem *minusText;

    bool pressedOverTopHalf;
    bool pressedOverBottomHalf;
};

ZoomButtonItem::ZoomButtonItem(GeoMap *map)
{
    d = new ZoomButtonItemPrivate;
    d->map = map;
    d->pressedOverBottomHalf = false;
    d->pressedOverTopHalf = false;
    setPen(QPen(QBrush(), 0));
    setBrush(QBrush(QColor(0,0,0,150)));

    d->plusText = new QGraphicsSimpleTextItem(this);
    d->plusText->setText("+");
    d->plusText->setBrush(QBrush(Qt::white));

    d->minusText = new QGraphicsSimpleTextItem(this);
    d->minusText->setText("-");
    d->minusText->setBrush(QBrush(Qt::white));
}

void ZoomButtonItem::setRect(qreal x, qreal y, qreal w, qreal h)
{
    QGraphicsRectItem::setRect(x, y, w, h);

    QFont f;
    f.setFixedPitch(true);
    f.setPixelSize(h/3.0);
    d->plusText->setFont(f);
    d->minusText->setFont(f);

    QRectF plusBound = d->plusText->boundingRect();
    QPointF plusCenter(x+w/2.0, y+h/4.0);
    QPointF plusDelta = plusCenter - plusBound.center();
    d->plusText->setPos(plusDelta);

    QRectF minusBound = d->minusText->boundingRect();
    QPointF minusCenter(x+w/2.0, y+3.0*h/4.0);
    QPointF minusDelta = minusCenter - minusBound.center();
    d->minusText->setPos(minusDelta);
}

void ZoomButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    const QPointF pos = event->pos();
    if (!d->pressedOverTopHalf && !d->pressedOverBottomHalf) {
        if (isTopHalf(pos)) {
            d->pressedOverTopHalf = true;
        } else if (isBottomHalf(pos)) {
            d->pressedOverBottomHalf = true;
        }
    }
    d->map->setFocus();
    event->accept();
}

bool ZoomButtonItem::isTopHalf(const QPointF &point)
{
    return QRectF(rect().x(), rect().y(),
                  rect().width(), rect().height()/2).contains(point);
}

bool ZoomButtonItem::isBottomHalf(const QPointF &point)
{
    return QRectF(rect().x(), rect().y() + rect().height()/2,
                  rect().width(), rect().height()/2).contains(point);
}

void ZoomButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    const QPointF pos = event->pos();
    if (isTopHalf(pos) && d->pressedOverTopHalf) {
        d->map->setZoomLevel(d->map->zoomLevel() + 1.0);
    } else if (isBottomHalf(pos) && d->pressedOverBottomHalf) {
        d->map->setZoomLevel(d->map->zoomLevel() - 1.0);
    }
    d->pressedOverBottomHalf = false;
    d->pressedOverTopHalf = false;
    d->map->setFocus();
    event->accept();
}

void ZoomButtonItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}


