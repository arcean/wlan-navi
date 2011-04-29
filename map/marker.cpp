#include "marker.h"

#include "qgeomappixmapobject.h"
#include "qgeosearchmanager.h"
#include "qgeocoordinate.h"
#include "qgraphicsgeomap.h"
#include "qgeoaddress.h"
#include "qgeosearchreply.h"

#include <iostream>
using namespace std;
using namespace QtMobility;

Marker::Marker(MarkerType type) :
    QGeoMapPixmapObject()
{

    d=new MarkerPrivate();
    //cout<<"\ndoszlo 1\n";
    setMarkerType(type);
}

void Marker::setMarkerType(MarkerType type)
{
    QString filename;
    QPoint offset;
    int scale;
    d->type = type;
  //  cout<<"\ndoszlo 1\n";
    switch (d->type) {
        case MyLocationMarker:
            filename = ":/icons/mylocation.png";
            break;
        case SearchMarker:
            filename = ":/icons/searchmarker.png";
            break;
        case WaypointMarker:
            filename = ":/icons/waypointmarker.png";
            break;
        case StartMarker:
            filename = ":/icons/startmarker.png";
            break;
        case EndMarker:
            filename = ":/icons/endmarker.png";
            break;
        case PathMarker:
            filename = ":/icons/pathmarker.png";
            break;
       case OpenWlanMarker:
           filename = ":/icons/openwlanmarker.png";
             break;
    }

    //cout<<"\ndoszlo 2\n";

    if (d->type == MyLocationMarker) {
        offset = QPoint(-13,-13);
        scale = 25;
    } else {
        offset = QPoint(-15, -36);
        scale = 30;
    }

    //cout<<"\ndoszlo 3\n";
    setOffset(offset);
    setPixmap(QPixmap(filename).scaledToWidth(scale, Qt::SmoothTransformation));

    //cout<<"\ndoszlo 4\n";
}
