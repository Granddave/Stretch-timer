#include "mainwindow.h"
#include "darkstyle.h"

#include <QApplication>
#include <QCoreApplication>
#include <QSettings>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("stretch-timer");
    a.setOrganizationName("StretchTimer");
    a.setWindowIcon(QIcon("://icon.ico"));

    QSettings settings;
    if (settings.value("darkTheme", true).toBool())
    {
        a.setStyle(new DarkStyle);
    }

    MainWindow w;
    w.readGeometry();
    w.show();

    return a.exec();
}
