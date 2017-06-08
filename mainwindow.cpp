#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "version.h"

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
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    QSettings settings;
    qDebug() << "SETTINGS: Config file located at" << settings.fileName();

    initUI();
    initSystemTray();
    initCountdownTimer();

    tickUpdate(0); // To initialize label in the mainwindow
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::initUI()
{
    _ui->setupUi(this);
    setWindowTitle("Stretch Timer");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    connect(_ui->button_setTimer, SIGNAL(clicked()), this, SLOT(setTimer()));
    connect(_ui->button_pause, SIGNAL(clicked()), this, SLOT(pauseUnpause()));
    connect(_ui->button_stopTimer, SIGNAL(clicked()), this, SLOT(stopTimer()));

    _ui->button_pause->setEnabled(false);
    _ui->button_stopTimer->setEnabled(false);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(closeApp()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(hide()));
}

void MainWindow::initSystemTray()
{
    // Tray icon
    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setIcon(QIcon("://resources/icon.ico"));
    _trayIcon->setVisible(true);

    // Click on message from tray icon
    connect(_trayIcon, SIGNAL(messageClicked()),this, SLOT(showMainWindow()));
    // Click on tray icintervalon
    connect(_trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(SystemTrayTriggered(QSystemTrayIcon::ActivationReason)));

    // Tray actions
    _actionSet= new QAction("&Set timer", this);
    connect(_actionSet, SIGNAL(triggered(bool)), this, SLOT(setTimer()));

    _actionPauseUnpause = new QAction("&Pause timer", this);
    _actionPauseUnpause->setEnabled(false);
    connect(_actionPauseUnpause, SIGNAL(triggered()), this, SLOT(pauseUnpause()));

    _actionStop = new QAction("St&op timer", this);
    _actionStop->setEnabled(false);
    connect(_actionStop, SIGNAL(triggered()), this, SLOT(stopTimer()));

    _actionAbout = new QAction("&About", this);
    connect(_actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    _actionQuit = new QAction("&Quit", this);
    _actionQuit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    connect(_actionQuit, SIGNAL(triggered()), this, SLOT(closeApp()));

    _trayIconMenu = new QMenu(this);
    _trayIconMenu->addAction(_actionSet);
    _trayIconMenu->addAction(_actionPauseUnpause);
    _trayIconMenu->addAction(_actionStop);
    _trayIconMenu->addSeparator();
    _trayIconMenu->addAction(_actionAbout);
    _trayIconMenu->addAction(_actionQuit);
    _trayIcon->setContextMenu(_trayIconMenu);
}

void MainWindow::initCountdownTimer()
{
    QSettings settings;
    int userInterval = settings.value("interval", 30).toInt();
    _countdownTimer = new CountdownTimer(this, userInterval);
    connect(_countdownTimer, SIGNAL(timeout()), this, SLOT(showTimeoutMessage()));
    connect(_countdownTimer, SIGNAL(tick(int)), this, SLOT(tickUpdate(int)));

    _ui->spinBox_Interval->setValue(_countdownTimer->interval());
    _ui->slider_interval->setValue(_countdownTimer->interval());
}

/* Load window position from settings.
 * The window will be placed in the center of the screen if it
 * was opened for the first time.
 */
void MainWindow::readGeometry()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
}

/* Set the countdown timer to the value on the slider and spinbox
 * If the timer is already running, it will be stopped before started.*/
void MainWindow::setTimer()
{
    int interval = _ui->slider_interval->value();

    QSettings settings;
    settings.setValue("interval", interval);
    _countdownTimer->setInterval(interval);

    _countdownTimer->start();

    _actionPauseUnpause->setEnabled(true);
    _ui->button_pause->setEnabled(true);

    _actionStop->setEnabled(true);
    _ui->button_stopTimer->setEnabled(true);

    _actionPauseUnpause->setText(QString("Pause timer"));
    _ui->button_pause->setText(QString("&Pause"));
}

/* Pause/Unpause the countdown timer */
void MainWindow::pauseUnpause()
{
    if(!_countdownTimer->paused())
    {
        _countdownTimer->pauseUnpause();
        _actionPauseUnpause->setText(QString("Resume timer"));
        _ui->button_pause->setText(QString("&Resume"));
    } else {
        _countdownTimer->pauseUnpause();
        _actionPauseUnpause->setText(QString("Pause timer"));
        _ui->button_pause->setText(QString("Pause"));
    }
}

/* Stops and resets the countdown timer */
void MainWindow::stopTimer()
{
    _countdownTimer->stop();
    _actionPauseUnpause->setEnabled(false);
    _ui->button_pause->setEnabled(false);
    _actionStop->setEnabled(false);
    _ui->button_stopTimer->setEnabled(false);
}

/* Show "Time to stretch" in the system tray */
void MainWindow::showTimeoutMessage()
{
    QSettings settings;
    int time = settings.value("secondsToDisplay", 5).toInt();

    // Max 20 seconds
    if(time > 20)
    {
        time = 20;
    }

    _trayIcon->showMessage(
                "StretchTimer",
                "Time to stretch!",
                QSystemTrayIcon::NoIcon,
                time * 1000);

#ifdef Q_OS_UNIX
    // Cred: https://www.freesound.org/people/SpiceProgram/sounds/387217/
    QSound::play("://resources/ping.wav");
#endif

    _countdownTimer->start();
}

/* Show and set focus on the main window */
void MainWindow::showMainWindow()
{
    this->showNormal();
    this->activateWindow();
}

/* This gets called when the user presses the close button */
void MainWindow::closeEvent(QCloseEvent *e)
{
    QSettings settings;
    bool quitOnClose = settings.value("quitOnClose", false).toBool();

    if(quitOnClose)
    {
        closeApp();
    }
    else
    {
        hideApp();
        e->ignore();
    }
}

/* This really closes the application and saves the
 * geometry of the window
 */
void MainWindow::closeApp()
{
    // Save position on screen
    QSettings settings;
    settings.setValue("geometry", saveGeometry());

    qApp->quit();
}

/* Hides the application and displays a "hide message" */
void MainWindow::hideApp()
{
    if (_trayIcon->isVisible())
    {
        _trayIcon->showMessage("Still running...",
                               "Stretch Timer is still running. "
                               "To terminate the program, "
                               "choose Quit in the context menu "
                               "or Ctrl+Q when the window is open.",
                               QSystemTrayIcon::NoIcon,
                               5000);
        hide();
    }
}

/* The system tray is activated */
void MainWindow::SystemTrayTriggered(QSystemTrayIcon::ActivationReason e)
{
    if(e == QSystemTrayIcon::Trigger)
    {
        showMainWindow();
    }
}

/* Update the label with the remaining time */
void MainWindow::tickUpdate(int rem)
{
    if(rem < 0)
    {
        /* Missed the timeout.
         * Could be because OS went to sleep etc.
         */
        _countdownTimer->start();
        return;
    }

    QString str, sec, min, hour;

    sec  = QString::number(rem % 60).rightJustified(2, '0');
    min  = QString::number((rem / 60) % 60).rightJustified(2, '0');
    hour = QString::number((rem / 3600) % 24).rightJustified(2, '0');

    if(_countdownTimer->isActive())
    {
        QTextStream(&str) << "Time left: " << hour << ":"<< min << ":" << sec;
    }
    else if(_countdownTimer->paused())
    {
        QTextStream(&str) << "Timer is paused at " << min << ":" << sec;
    }
    else
    {
        QTextStream(&str) << "Timer is stopped";
    }

    _ui->label_timeLeft->setText(str);
    _trayIcon->setToolTip(str);
}

/* Sync the slider with the spinbox */
void MainWindow::on_spinBox_Interval_valueChanged(int val)
{
    _ui->slider_interval->setValue(val);
}

/* Sync the spinbox with the slider */
void MainWindow::on_slider_interval_valueChanged(int val)
{
    _ui->spinBox_Interval->setValue(val);
}

/* Shows the about dialog */
void MainWindow::about()
{
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setWindowTitle(QString("About Stretch Timer ") + QString(STRETCHTIMER_VERSION));
    msgBox.setText("Stretch Timer is an opensource project "
                   "that help people to stand up and stretch between their "
                   "work sessions. <br/><br/>"
                   "Developed by David Isaksson<br/>"
                   "<a href=\"https://github.com/Granddave/Stretch-timer\">https://github.com/Granddave/Stretch-timer</a>");
    msgBox.exec();
}





