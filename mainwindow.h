#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QTime>
#include <QDebug>

#include "alarm.h"

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
    void pauseUnpause();
    void stopTimer();
    void showMessage();     // Timer has run out
    void tickUpdate();
    void restartTick();

    void on_spinBox_Interval_valueChanged(int val);
    void on_slider_interval_valueChanged(int val);

    void on_button_setTimer_clicked();
    void on_button_Cancel_clicked();

private:

    Ui::MainWindow *_ui;

    Alarm *_alarm;
    QTimer *_tick;
    int _tickInterval;

    QSystemTrayIcon *_trayIcon;
    QMenu *_trayIconMenu;
    QAction *_actionExit;
    QAction *_actionPauseUnpause;
};

#endif // MAINWINDOW_H
