#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "version.h"

#include <QIcon>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QShortcut>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    setWindowTitle("Stretch Timer");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(closeApp()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(hideApp()));

    QSettings settings;
    qDebug() << "SETTINGS: Config file located at" << settings.fileName();

    initSystemTray();

    int userInterval = settings.value("interval", 30).toInt();
    _countdownTimer = new CountdownTimer(this, userInterval);
    connect(_countdownTimer, SIGNAL(timeout()), this, SLOT(showMessage()));
    connect(_countdownTimer, SIGNAL(tick(int)), this, SLOT(tickUpdate(int)));

    _ui->spinBox_Interval->setValue(_countdownTimer->interval());
    _ui->slider_interval->setValue(_countdownTimer->interval());

    connect(_ui->button_setTimer, SIGNAL(clicked()), this, SLOT(setTimer()));
    connect(_ui->button_pause, SIGNAL(clicked()), this, SLOT(pauseUnpause()));
    connect(_ui->button_stopTimer, SIGNAL(clicked()), this, SLOT(stopTimer()));
    connect(_ui->button_hide, SIGNAL(clicked()), this, SLOT(hide()));

    _ui->button_pause->setEnabled(false);
    _ui->button_stopTimer->setEnabled(false);

    // Initialize label
    tickUpdate(0);
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::initSystemTray()
{
    // Tray icon
    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setIcon(QIcon("://myappico.png"));
    _trayIcon->setVisible(true);

    connect(_trayIcon, SIGNAL(messageClicked()),this, SLOT(showMainWindow()));
    connect(_trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(SystemTrayTriggered(QSystemTrayIcon::ActivationReason)));

    // Tray actions
    _actionSet= new QAction("Set timer", this);
    connect(_actionSet, SIGNAL(triggered(bool)), this, SLOT(setTimer()));

    _actionPauseUnpause = new QAction("Pause timer", this);
    _actionPauseUnpause->setEnabled(false);
    connect(_actionPauseUnpause, SIGNAL(triggered()), this, SLOT(pauseUnpause()));

    _actionStop = new QAction("Stop timer", this);
    _actionStop->setEnabled(false);
    connect(_actionStop, SIGNAL(triggered()), this, SLOT(stopTimer()));

    _actionAbout = new QAction("About", this);
    connect(_actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    _actionQuit = new QAction("Quit", this);
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
    _ui->button_pause->setText(QString("Pause"));
}

/* Pause/Unpause the countdown timer */
void MainWindow::pauseUnpause()
{
    if(!_countdownTimer->paused())
    {
        _countdownTimer->pauseUnpause();
        _actionPauseUnpause->setText(QString("Resume timer"));
        _ui->button_pause->setText(QString("Resume"));
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
void MainWindow::showMessage()
{
    QSettings settings;
    int time = settings.value("secondsToDisplay", 5).toInt();

    // Max 20 seconds
    if(time > 20)
        time = 20;

    _trayIcon->showMessage( QString("Time to stretch!"),QString(""),QSystemTrayIcon::NoIcon, time * 1000);
    _countdownTimer->start();
}

/* Show and set focus on the main window */
void MainWindow::showMainWindow()
{
    this->showNormal();
    this->activateWindow();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    hideApp();
}

void MainWindow::closeApp()
{
    qApp->quit();
}

void MainWindow::hideApp()
{
    if (_trayIcon->isVisible())
    {
        _trayIcon->showMessage("Still running...",
                               "Stretch Timer is still running. "
                               "To terminate the program, "
                               "choose <b>Quit</b> in the context menu "
                               "or <b>Ctrl+Q</b> when the window is open.",
                               QSystemTrayIcon::NoIcon,
                               5000);
        hide();
    }
}

/* The system tray is activated */
void MainWindow::SystemTrayTriggered(QSystemTrayIcon::ActivationReason e)
{
    if(e == QSystemTrayIcon::Trigger)
        showMainWindow();
}

/* Update the label with the remaining time */
void MainWindow::tickUpdate(int rem)
{
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
    msgBox.setTextFormat(Qt::RichText); // this does the magic trick and allows you to click the link
    msgBox.setWindowTitle("About Stretch Timer "STRETCHTIMER_VERSION);
    msgBox.setText("Stretch Timer is an opensource project "
                   "that help people to stand up and stretch between their "
                   "work sessions. <br/><br/>"
                   "Developed by David Isaksson<br/>"
                   "<a href=\"https://github.com/Granddave/Stretch-timer\">https://github.com/Granddave/Stretch-timer</a>");
    msgBox.exec();
}



