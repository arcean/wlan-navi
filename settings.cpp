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

#include "settings.h"
#include "ui_settings.h"
#include <QDebug>

#ifdef Q_WS_MAEMO_5
    #include <QMaemo5InformationBox>
#endif

Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowTitle("Settings");
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));

    loadItemsCB();
    loadQGeoProvider();
}

Settings::~Settings()
{
    delete ui;
}

/**
  Adds items to the mapProviderCB combobox
*/
void Settings::loadItemsCB()
{
    ui->mapProviderCB->addItem("OpenStreetMap", "openstreetmap");
    ui->mapProviderCB->addItem("Nokia OVI Maps", "nokia");
}

/**
  Checks what plugin should be set as default
*/
void Settings::loadQGeoProvider()
{
    QString plugin = "";

    GetKeyString(&plugin, "qgeoplugin");
    if(!plugin.compare("nokia"))
    {
        int index = ui->mapProviderCB->findData("nokia");
        qDebug() << "H: " << index;
        ui->mapProviderCB->setCurrentIndex(index);
    }
    else
    {
        int index = ui->mapProviderCB->findData("openstreetmap");
        qDebug() << "H2: " << index;
        ui->mapProviderCB->setCurrentIndex(index);
    }
}

/**
  Saves default QGeoServiceProvider plugin
*/
void Settings::saveQGeoProvider()
{
    QString plugin = ui->mapProviderCB->itemData(ui->mapProviderCB->currentIndex()).toString();
    if(!plugin.compare(""))
        StoreKeyString("openstreetmap", "qgeoplugin");
    else
        StoreKeyString(plugin, "qgeoplugin");
}

void Settings::saveSettings()
{
    saveQGeoProvider();
    #ifdef Q_WS_MAEMO_5
        QMaemo5InformationBox::information(this, "Settings saved");
    #endif
}
