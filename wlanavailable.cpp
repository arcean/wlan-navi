#include <QListWidgetItem>
#include <QString>
#include <QDebug>

#include "wlanavailable.h"
#include "ui_wlanavailable.h"

QList<Network> wlans;

WlanAvailable::WlanAvailable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WlanAvailable)
{
    ui->setupUi(this);
    setWindowTitle("Available wlans");
    this->loadWlans();
}

WlanAvailable::~WlanAvailable()
{
    delete ui;
}
/*
void WlanAvailable::setWlans(QList<Network> *wlans)
{
    this->wlans = wlans;
    qDebug() << "\n WLANS: " << this->wlans->size() << "\n";
}

QList<Network>* WlanAvailable::getWlans()
{
    return wlans;
}*/

void WlanAvailable::loadWlans()
{
    QListWidgetItem *item;
    QString text;
    text = "Network name; signal quality";
    item = new QListWidgetItem(text);
    ui->wlanList->addItem(item);

    if(wlans.size() <= 0)
    {
        qDebug() << "wlans size <= 0 !";
        return;
    }

    for(int i=0; i < wlans.size(); i++)
    {
        text = QString::fromStdString(wlans.at(i).essid) + "; " + QString::number(wlans.at(i).quality) + "%";
        item = new QListWidgetItem(text);
        ui->wlanList->addItem(item);
    }
}
