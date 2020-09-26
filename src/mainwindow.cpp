#include "mainwindow.h"

// Qt
#include <QIcon>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QShortcut>
#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>
#ifdef Q_OS_UNIX
#include <QSound>
#endif // Q_OS_UNIX

#include "ui_mainwindow.h"
#include "version.h"
#include "settingswidget.h"
#include "aboutdialog.h"
#include "common.h"

#ifdef AGGRESSIVE_MODE_SUPPORTED
#include "alarmdialog.h"
#endif // AGGRESSIVE_MODE_SUPPORTED

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    const QSettings settings;
    qDebug() << "SETTINGS: Config file located at" << settings.fileName();

    initUI();
    initSystemTray();
    initCountdownTimer();

    // Initialize label in the main window
    tickUpdate(0);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

/* Initialize UI elements */
void MainWindow::initUI()
{
    m_ui->setupUi(this);
    qApp->setQuitOnLastWindowClosed(false);

    setWindowTitle("Stretch Timer");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    connect(m_ui->button_setTimer, SIGNAL(clicked()), this, SLOT(setTimer()));
    connect(m_ui->button_pause, SIGNAL(clicked()), this, SLOT(pauseUnpause()));
    connect(m_ui->button_stopTimer, SIGNAL(clicked()), this, SLOT(stopTimer()));
    connect(
        m_ui->spinBox_interval, SIGNAL(valueChanged(int)), this, SLOT(spinBoxIntervalChanged(int)));
    connect(
        m_ui->slider_interval, SIGNAL(valueChanged(int)), this, SLOT(sliderIntervalChanged(int)));

    m_ui->button_pause->setEnabled(false);
    m_ui->button_stopTimer->setEnabled(false);

    m_shortcuts.close = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(closeApp()));
    m_shortcuts.hide = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(hide()));
    m_shortcuts.settings =
        new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(settings()));
}

/* Initialize system tray with context menu */
void MainWindow::initSystemTray()
{
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon("://icon.ico"));
    m_trayIcon->setVisible(true);

    connect(m_trayIcon, SIGNAL(messageClicked()), this, SLOT(showMainWindow()));
    connect(m_trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(systemTrayTriggered(QSystemTrayIcon::ActivationReason)));

    // Tray actions
    m_actions.setTimer = new QAction("&Set timer", this);
    connect(m_actions.setTimer, SIGNAL(triggered(bool)), this, SLOT(setTimer()));

    m_actions.pauseUnpauseTimer = new QAction("&Pause timer", this);
    m_actions.pauseUnpauseTimer->setEnabled(false);
    connect(m_actions.pauseUnpauseTimer, SIGNAL(triggered()), this, SLOT(pauseUnpause()));

    m_actions.stopTimer = new QAction("St&op timer", this);
    m_actions.stopTimer->setEnabled(false);
    connect(m_actions.stopTimer, SIGNAL(triggered()), this, SLOT(stopTimer()));

    m_actions.openSettings = new QAction("S&ettings", this);
    m_actions.openSettings->setShortcut(m_shortcuts.settings->key());
    connect(m_actions.openSettings, SIGNAL(triggered()), this, SLOT(settings()));

    m_actions.openAbout = new QAction("&About", this);
    connect(m_actions.openAbout, SIGNAL(triggered()), this, SLOT(about()));

    m_actions.quit = new QAction("&Quit", this);
    m_actions.quit->setShortcut(m_shortcuts.close->key());
    connect(m_actions.quit, SIGNAL(triggered()), this, SLOT(closeApp()));

    m_trayIconMenu = new QMenu(this);
    m_trayIconMenu->addAction(m_actions.setTimer);
    m_trayIconMenu->addAction(m_actions.pauseUnpauseTimer);
    m_trayIconMenu->addAction(m_actions.stopTimer);
    m_trayIconMenu->addSeparator();
    m_trayIconMenu->addAction(m_actions.openSettings);
    m_trayIconMenu->addAction(m_actions.openAbout);
    m_trayIconMenu->addAction(m_actions.quit);
    m_trayIcon->setContextMenu(m_trayIconMenu);
}

/* Initialize the countdown timer object and update relevant UI elements */
void MainWindow::initCountdownTimer()
{
    const QSettings settings;
    const int userInterval = settings.value("interval", 30).toInt();

    m_countdownTimer = new CountdownTimer(TimerType::minutes, userInterval, this);

    connect(m_countdownTimer, SIGNAL(timeout()), this, SLOT(showTimeoutMessage()));
    connect(m_countdownTimer, SIGNAL(tick(int)), this, SLOT(tickUpdate(int)));

    m_ui->spinBox_interval->setValue(m_countdownTimer->interval());
    m_ui->slider_interval->setValue(m_countdownTimer->interval());
}

/* Load window position from settings.
 * The window will be placed in the center of the screen if it
 * was opened for the first time. */
void MainWindow::readGeometry()
{
    const QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
}

/* Set the countdown timer to the value on the slider and spinbox
 * If the timer is already running, it will be stopped before started.*/
void MainWindow::setTimer()
{
    const int interval = m_ui->slider_interval->value();

    if (!m_countdownTimer->setInterval(interval))
    {
        qDebug() << "WARNING: Could not set interval" << interval;
        return;
    }

    QSettings settings;
    settings.setValue("interval", interval);

    m_countdownTimer->start();

    m_actions.pauseUnpauseTimer->setEnabled(true);
    m_ui->button_pause->setEnabled(true);

    m_actions.stopTimer->setEnabled(true);
    m_ui->button_stopTimer->setEnabled(true);

    m_actions.pauseUnpauseTimer->setText("Pause timer");
    m_ui->button_pause->setText("&Pause");

    qDebug() << "TIMER: Setting timer with an interval of" << interval << "minutes.";
}

/* Pause/Unpause the countdown timer */
void MainWindow::pauseUnpause()
{
    if (!m_countdownTimer->paused())
    {
        m_countdownTimer->pauseUnpause();
        m_actions.pauseUnpauseTimer->setText("Resume timer");
        m_ui->button_pause->setText("&Resume");

        qDebug() << "TIMER: Pausing timer with " << m_countdownTimer->remainingTime() / 60
                 << "minutes left.";
    }
    else
    {
        m_countdownTimer->pauseUnpause();
        m_actions.pauseUnpauseTimer->setText("Pause timer");
        m_ui->button_pause->setText("Pause");

        qDebug() << "TIMER: Unpausing timer.";
    }
}

/* Stops and resets the countdown timer */
void MainWindow::stopTimer()
{
    m_countdownTimer->stop();

    m_actions.pauseUnpauseTimer->setEnabled(false);
    m_ui->button_pause->setEnabled(false);
    m_actions.stopTimer->setEnabled(false);
    m_ui->button_stopTimer->setEnabled(false);

    qDebug() << "TIMER: Stopping timer.";
}

/* Show time out message in the system tray */
void MainWindow::showTimeoutMessage()
{
    const QSettings settings;

    const int time = settings.value("secondsToDisplay", 5).toInt();
    const QString message(settings.value("timeoutMessage", "Time to stretch!").toString());

    m_trayIcon->showMessage("StretchTimer", message, QSystemTrayIcon::NoIcon, time * 1000);

#ifdef Q_OS_UNIX
    // Cred: https://www.freesound.org/people/SpiceProgram/sounds/387217/
    QSound::play("://ping.wav");
#endif

#ifdef AGGRESSIVE_MODE_SUPPORTED
    m_countdownTimer->stop();
    qDebug() << "TIMER: Timeout";

    if (settings.value("aggressiveMode", false).toBool())
    {
        auto* d = new AlarmDialog();
        connect(d, SIGNAL(destroyed(QObject*)), this, SLOT(setTimer()));
        d->exec();
        d->deleteLater();
    }
    else
    {
        setTimer();
    }
#else  // AGGRESSIVE_MODE_SUPPORTED
    setTimer();
    qDebug() << "TIMER: Timeout and restarting timer.";
#endif // AGGRESSIVE_MODE_SUPPORTED
}

/* Show and set focus on the main window */
void MainWindow::showMainWindow()
{
    this->showNormal();
    this->activateWindow();
}

/* This gets called when the user presses the close button */
void MainWindow::closeEvent(QCloseEvent* e)
{
    const QSettings settings;
    const bool quitOnClose = settings.value("quitOnClose", false).toBool();

    if (quitOnClose)
    {
        closeApp();
    }
    else
    {
        hideApp();
        e->ignore();
    }
}

/* This really closes the application and saves the geometry of the window */
void MainWindow::closeApp()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());

    qApp->quit();
}

/* Hides the application and displays a "hide message" */
void MainWindow::hideApp()
{
    if (m_trayIcon->isVisible())
    {
        const QSettings settings;
        if (settings.value("showPopupWhenHide", true).toBool())
        {
            m_trayIcon->showMessage("Stretch Timer is still running...",
                                    "To terminate the program, "
                                    "choose Quit in the context menu "
                                    "or Ctrl+Q when the window is open"
                                    "\nThis message can be disable in "
                                    "the settings.",
                                    QSystemTrayIcon::NoIcon,
                                    5000);
        }
        hide();
    }
}

/* The system tray is activated */
void MainWindow::systemTrayTriggered(QSystemTrayIcon::ActivationReason e)
{
    if (e == QSystemTrayIcon::Trigger)
    {
        showMainWindow();
    }
}

/* Update the label with the remaining time */
void MainWindow::tickUpdate(const int rem)
{
    if (rem < 0)
    {
        /* Missed the timeout.
         * Could be because OS went to sleep etc. */
        setTimer();

        qDebug() << "WARNING: Remaining time is < 0:" << rem;
        return;
    }

    const QString hour = QString::number((rem / 3600) % 24).rightJustified(2, '0');
    const QString min = QString::number((rem / 60) % 60).rightJustified(2, '0');
    const QString sec = QString::number(rem % 60).rightJustified(2, '0');

    QString statusText;
    QTextStream qts(&statusText);
    if (m_countdownTimer->isActive())
    {
        qts << "Time left: " << hour << ":" << min << ":" << sec;
    }
    else if (m_countdownTimer->paused())
    {
        qts << "Timer is paused at " << min << ":" << sec;
    }
    else
    {
        qts << "Timer is stopped";
    }

    m_ui->label_timeLeft->setText(statusText);
    m_trayIcon->setToolTip(statusText);
}

/* Sync the slider with the spinbox */
void MainWindow::spinBoxIntervalChanged(int val)
{
    m_ui->slider_interval->setValue(val);
}

/* Sync the spinbox with the slider */
void MainWindow::sliderIntervalChanged(int val)
{
    m_ui->spinBox_interval->setValue(val);
}

/* Opens settings window */
void MainWindow::settings()
{
    SettingsWidget settingsWidget;
    settingsWidget.exec();
}

/* Shows the about dialog */
void MainWindow::about()
{
    AboutDialog dialog;
    dialog.exec();
}
