#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QShortcut>
#include <QSettings>

#include "countdowntimer.h"

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
    void systemTrayTriggered(QSystemTrayIcon::ActivationReason e);
    void tickUpdate(const int rem);

    void spinBoxIntervalChanged(int val);
    void sliderIntervalChanged(int val);

    void settings();
    void about();

private:
    void initUI();
    void initSystemTray();
    void initCountdownTimer();

    Ui::MainWindow* m_ui;

    CountdownTimer* m_countdownTimer{};
    QSystemTrayIcon* m_trayIcon{};
    QMenu* m_trayIconMenu{};

    struct
    {
        QAction* setTimer;
        QAction* pauseUnpauseTimer;
        QAction* stopTimer;
        QAction* openSettings;
        QAction* openAbout;
        QAction* quit;
    } m_actions{};

    struct
    {
        QShortcut* close;
        QShortcut* hide;
        QShortcut* settings;
    } m_shortcuts{};
};

#endif // MAINWINDOW_H
