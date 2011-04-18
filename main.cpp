#include "mainwindow.h"

#include <QApplication>
#include <QList>
#include <QString>
#include <QUrl>
#include <QSettings>
#include <QProcessEnvironment>
#include <QNetworkProxyFactory>

#include "qgeoserviceprovider.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("K0l40a");
    QApplication::setApplicationName("wlan-navi");

    MainWindow mw;

    mw.resize(200,200);
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
    mw.showMaximized();
#else
    mw.show();
#endif

    return a.exec();
}
