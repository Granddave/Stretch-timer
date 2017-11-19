#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    QApplication a(argc, argv);

    a.setApplicationName("StretchTimer");
    a.setOrganizationName("StretchTimer");
    a.setWindowIcon(QIcon("://resources/icon.ico"));

    MainWindow w;
    w.show();
    w.readGeometry();

    return a.exec();
}
