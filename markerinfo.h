#ifndef MARKERINFO_H
#define MARKERINFO_H

#include <QMainWindow>
#include <QList>
#include <QString>

#include "WlanMaemo.h"
#include "marker.h"

namespace Ui {
    class MarkerInfo;
}

class MarkerInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit MarkerInfo(QWidget *parent = 0, Marker *marker = 0, QList<Network> *wlans = 0);
    ~MarkerInfo();

private slots:
    void loadInfo();

private:
    Ui::MarkerInfo *ui;
    Marker *marker;
    QList<Network> *wlans;
};

#endif // MARKERINFO_H
