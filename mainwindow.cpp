#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    // Tray icon
    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setIcon(QIcon("://myappico.png"));
    _trayIcon->setVisible(true);

    // Tray actions
    _actionQuit = new QAction(this);
    _actionQuit->setText(QString("Quit"));

    _actionPauseUnpause = new QAction(this);
    _actionPauseUnpause->setText(QString("Pause timer"));

    connect(_actionQuit,SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(_actionPauseUnpause,SIGNAL(triggered(bool)), this, SLOT(pauseUnpause()));

    _trayIconMenu = new QMenu(this);

    _trayIconMenu->addAction(_actionPauseUnpause);
    _trayIconMenu->addAction(_actionQuit);
    _trayIcon->setContextMenu(_trayIconMenu);


    // Timer
    interval = 10 * 1000; // Timer interval in ms

    _timer = new QTimer(this);
    _timer->setTimerType(Qt::TimerType::CoarseTimer);
    _timer->start(interval);

    connect(_timer, SIGNAL(timeout()), this, SLOT(showMessage()));
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::pauseUnpause()
{
    if(_timer->isActive())
    {
        int remaining = _timer->remainingTime();
        _timer->stop();
        _timer->setInterval(remaining);
        _actionPauseUnpause->setText(QString("Start timer"));
    }
    else
    {
        _timer->start(interval);
        _actionPauseUnpause->setText(QString("Pause timer"));
    }
}

void MainWindow::showMessage()
{
    _trayIcon->showMessage( QString("Time to stretch!"),QString(""),QSystemTrayIcon::NoIcon, 1000);
}

void MainWindow::setTimer(/*Interval<w*/)
{
    //TODO
}
