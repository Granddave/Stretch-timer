#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("StretchTimer");
    a.setOrganizationName("StretchTimer");

    MainWindow w;
    w.show();
    w.readGeometry();

    return a.exec();
}
