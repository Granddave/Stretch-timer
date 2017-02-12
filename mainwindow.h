#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QString>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void pauseUnpause();    // Pause/unpause timer
    void showMessage();     // Timer has run out

private:

    void setTimer(/*interval*/); // Slot?


    Ui::MainWindow *_ui;


    int interval;
    QTimer *_timer;
    QSystemTrayIcon *_trayIcon;
    QMenu *_trayIconMenu;
    QAction *_actionQuit;
    QAction *_actionPauseUnpause;
};

#endif // MAINWINDOW_H
