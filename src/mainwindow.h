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
#include <QShortcut>
#include <QSettings>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void readGeometry();

private slots:
    void setTimer();
    void pauseUnpause();
    void stopTimer();
    void showTimeoutMessage();
    void showMainWindow();
    void closeEvent(QCloseEvent* e);
    void closeApp();
    void hideApp();
    void SystemTrayTriggered(QSystemTrayIcon::ActivationReason e);
    void tickUpdate(int rem);

    void on_spinBox_Interval_valueChanged(int val);
    void on_slider_interval_valueChanged(int val);

    void settings();
    void about();

private:
    void initUI();
    void initSystemTray();
    void initCountdownTimer();

    Ui::MainWindow* m_ui;
    CountdownTimer* m_countdownTimer;

    QSystemTrayIcon* m_trayIcon;
    QMenu* m_trayIconMenu;

    struct
    {
        QAction* setTimer;
        QAction* pauseUnpauseTimer;
        QAction* stopTimer;
        QAction* openSettings;
        QAction* openAbout;
        QAction* quit;
    } m_actions;

    struct
    {
        QShortcut* close;
        QShortcut* hide;
        QShortcut* settings;
    } m_shortcuts;
};

#endif // MAINWINDOW_H
