#include "markerinfo.h"
#include "ui_markerinfo.h"

MarkerInfo::MarkerInfo(QWidget *parent, Marker *marker, QList<Network> *wlans) :
    QMainWindow(parent),
    ui(new Ui::MarkerInfo),
    marker(marker),
    wlans(wlans)
{
    ui->setupUi(this);
    setWindowTitle("WLAN info");
    setAttribute(Qt::WA_Maemo5StackedWindow);
    loadInfo();
}

MarkerInfo::~MarkerInfo()
{
    delete ui;
}

void MarkerInfo::loadInfo()
{
    QString wlanName = marker->getName();
    bool found = false;
    int index = -1;

    for(int i = 0; i < wlans->size(); i++)
    {
        if(!wlanName.compare(QString::fromStdString(wlans->at(i).essid)))
        {
            //It's what we're looking for
            found = true;
            index = i;
            break;
        }
    }

    if(found)
    {
        ui->wlanNameLabel->setText(wlanName);
        ui->channelLabel->setText(QString::number(wlans->at(index).channel));
        ui->signalStrengthLabel->setText(QString::number(wlans->at(index).quality) + " %");
        ui->encryptionLabel->setText(encryptionToString(wlans->at(index).encryption));
    }
}
