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

    void on_spinBox_Interval_valueChanged(int val);
    void on_slider_interval_valueChanged(int val);

    void on_button_setTimer_clicked();
    void on_button_Cancel_clicked();



private:

    void setTimer(); // Slot?

    Ui::MainWindow *_ui;

    QTimer *_timer;
    bool _timerIsActive;
    int _interval;          // Time in seconds

    QSystemTrayIcon *_trayIcon;
    QMenu *_trayIconMenu;
    QAction *_actionExit;
    QAction *_actionPauseUnpause;
};

#endif // MAINWINDOW_H
