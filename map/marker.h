#ifndef MARKER_H
#define MARKER_H

#include <QSignalMapper>

#include "qgeomappixmapobject.h"
#include "qgeosearchmanager.h"
#include "qgeocoordinate.h"
#include "qgraphicsgeomap.h"
#include "qgeoaddress.h"
#include "qgeosearchreply.h"

using namespace QtMobility;

class MarkerPrivate;
class Marker : public QGeoMapPixmapObject{
     Q_OBJECT

    // Q_PROPERTY(MarkerType markerType READ markerType WRITE setMarkerType)

 public:
     enum MarkerType {
         MyLocationMarker,
         SearchMarker,
         WaypointMarker,
         StartMarker,
         EndMarker,
         PathMarker,
         OpenWlanMarker
     };

     explicit Marker(MarkerType type);

     MarkerType markerType() const;
     void setMarkerType(MarkerType type);

 private:
     MarkerPrivate *d;

 };

 class MarkerPrivate
 {
 public:
     Marker::MarkerType type;
 };


#endif // MARKER_H
