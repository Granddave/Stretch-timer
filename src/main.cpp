#include <QApplication>
#include <QCoreApplication>
#include <QSettings>

#include "mainwindow.h"
#include "darkstyle.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("stretch-timer");
    QApplication::setOrganizationName("StretchTimer");
    QApplication::setWindowIcon(QIcon("://icon.ico"));

    const QSettings settings;
    if (settings.value("darkTheme", true).toBool())
    {
        QApplication::setStyle(new DarkStyle);
    }

    MainWindow w;
    w.readGeometry();
    w.show();

    return QApplication::exec();
}
