#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "countdowntimer.h"

// Qt
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readGeometry();

private slots:
    void setTimer();
    void pauseUnpause();
    void stopTimer();
    void showTimeoutMessage();         // Timer has run out
    void showMainWindow();
    void closeEvent(QCloseEvent *e);
    void closeApp();
    void hideApp();
    void SystemTrayTriggered(QSystemTrayIcon::ActivationReason e);
    void tickUpdate(int rem);

    void on_spinBox_Interval_valueChanged(int val);
    void on_slider_interval_valueChanged(int val);

    void about();

private:
    void initUI();
    void initSystemTray();
    void initCountdownTimer();

    Ui::MainWindow *_ui;
    CountdownTimer *_countdownTimer;

    QSystemTrayIcon *_trayIcon;
    QMenu *_trayIconMenu;
    QAction *_actionSet;
    QAction *_actionPauseUnpause;
    QAction *_actionStop;
    QAction *_actionAbout;
    QAction *_actionQuit;
};

#endif // MAINWINDOW_H
