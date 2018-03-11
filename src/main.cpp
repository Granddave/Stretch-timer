#include "mainwindow.h"
#include "darkStyle.h"

#include <QApplication>
#include <QCoreApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    //qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    QApplication a(argc, argv);

    a.setApplicationName("StretchTimer");
    a.setOrganizationName("StretchTimer");
    a.setWindowIcon(QIcon("://icon.ico"));

    QSettings settings;
    if (settings.value("DarkTheme", false).toBool())
    {
        a.setStyle(new DarkStyle);
    }

    MainWindow w;
    w.readGeometry();
    w.show();

    return a.exec();
}
