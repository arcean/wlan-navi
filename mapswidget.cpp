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

#include "qgeocoordinate.h"

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

    this->setFocus();
    event->accept();
}

void GeoMap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    panActive = false;

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


class MapsWidgetPrivate
{
public:
    GeoMap *map;
    QGraphicsView *view;

    FullscreenButtonItem *fsButtonItem;
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

    d->fsButtonItem = new FullscreenButtonItem(d->map);
    sc->addItem(d->fsButtonItem);
    connect(d->fsButtonItem, SIGNAL(mouseReleaseEventSignal()), this->parentWidget(), SLOT(toggleFullScreen()));

    d->view->resize(this->size());
    d->view->centerOn(d->map);

    resizeEvent(0);

    d->map->setCenter(QGeoCoordinate(-27.5796, 153.1));
    d->map->setZoomLevel(15);
}

void MapsWidget::setMyLocation(QGeoCoordinate location, bool center)
{
    if (d->map && center)
        d->map->setCenter(location);
}

QGraphicsGeoMap *MapsWidget::map() const
{
    return d->map;
}

void MapsWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    if (d->view && d->map) {
        d->view->resize(size());
        d->map->resize(width()-2, height()-2);
        d->view->centerOn(d->map);

        d->fsButtonItem->setRect(width() - 40, height() - 40, 40, 40);
    }
}

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


class FullscreenButtonItemPrivate
{
public:
    GeoMap *map;
    QGraphicsSimpleTextItem *fsText;


    bool pressedFullscreenButton;
};

FullscreenButtonItem::FullscreenButtonItem(GeoMap *map) :
    d(new FullscreenButtonItemPrivate)
{
    d->map = map;
    d->pressedFullscreenButton = false;

    setPen(QPen(QBrush(), 0));
    setBrush(QBrush(QColor(0,0,0,150)));

    d->fsText = new QGraphicsSimpleTextItem(this);
    d->fsText->setText("FS");
    d->fsText->setBrush(QBrush(Qt::white));
}

void FullscreenButtonItem::setRect(qreal x, qreal y, qreal w, qreal h)
{
    QGraphicsRectItem::setRect(x, y, w, h);

    QFont f;
    f.setFixedPitch(true);
    f.setPixelSize(h/3.0);
    d->fsText->setFont(f);

    QRectF fsBound = d->fsText->boundingRect();
    QPointF fsCenter(x+w/2.0, y+3.0*h/4.0);
    QPointF fsDelta = fsCenter - fsBound.center();
    d->fsText->setPos(fsDelta);
}

void FullscreenButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    const QPointF pos = event->pos();

    d->pressedFullscreenButton = true;
    d->map->setFocus();
    event->accept();
}

void FullscreenButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseReleaseEventSignal();
    d->pressedFullscreenButton = false;
    d->map->setFocus();
    event->accept();
}

void FullscreenButtonItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}
