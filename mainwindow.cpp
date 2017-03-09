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
    connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(show()));
    connect(_trayIcon, SIGNAL(messageClicked()),this, SLOT(show()));


    // Tray actions
    _actionExit = new QAction(this);
    _actionExit->setText(QString("Exit"));

    _actionPauseUnpause = new QAction(this);
    _actionPauseUnpause->setText(QString("Pause timer"));
	_actionPauseUnpause->setEnabled(false);

    connect(_actionExit,SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(_actionPauseUnpause,SIGNAL(triggered(bool)), this, SLOT(pauseUnpause()));

    _trayIconMenu = new QMenu(this);

    _trayIconMenu->addAction(_actionPauseUnpause);
    _trayIconMenu->addAction(_actionExit);
    _trayIcon->setContextMenu(_trayIconMenu);


    // Timer

    _alarm = new Alarm(this);
    _alarm->setInterval(10);
    connect(_alarm, SIGNAL(timeout()), this, SLOT(showMessage()));

    _tick = new QTimer(this);
    _tickInterval = 400;
    _tick->start(_tickInterval);
    connect(_tick, SIGNAL(timeout()), this, SLOT(tickUpdate()));
    tickUpdate();

    _ui->spinBox_Interval->setValue(_alarm->interval());
    _ui->slider_interval->setValue(_alarm->interval());

    connect(_ui->button_stopTimer, SIGNAL(clicked()), this, SLOT(stopTimer()));
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::pauseUnpause()
{
    if(!_alarm->paused())
    {
        _alarm->pauseUnpause();
        restartTick();
        _actionPauseUnpause->setText(QString("Start timer"));
    } else {
        _alarm->pauseUnpause();
        restartTick();
        _actionPauseUnpause->setText(QString("Pause timer"));
    }
}


void MainWindow::showMessage()
{
    _trayIcon->showMessage( QString("Time to stretch!"),QString(""),QSystemTrayIcon::NoIcon, 2000);
    _alarm->start();
}

void MainWindow::tickUpdate()
{
	QString str, sec, min, hour;
	int rem = _alarm->remainingTime();
	
	sec  = QString::number(rem % 60).rightJustified(2, '0');
	min  = QString::number((rem / 60) % 60).rightJustified(2, '0');
	hour = QString::number((rem / 3600) % 24).rightJustified(2, '0');

	if(_alarm->isActive())
    {
		QTextStream(&str) << "Time left: " << hour << ":"<< min << ":" << sec;
		_ui->label_timeLeft->setText(str);
    }
    else if(_alarm->paused())
    {
		QTextStream(&str) << "Timer is paused at " << min << ":" << sec;
        _ui->label_timeLeft->setText(str);
    }
    else
    {
        _ui->label_timeLeft->setText(QString("Timer is stopped"));
    }
}

void MainWindow::restartTick()
{
    _tick->stop();
    _tick->start(_tickInterval);
    tickUpdate();
}

void MainWindow::on_spinBox_Interval_valueChanged(int val)
{
    _alarm->setInterval(val);
    _ui->slider_interval->setValue(val);
}

void MainWindow::on_slider_interval_valueChanged(int val)
{
    _alarm->setInterval(val);
    _ui->spinBox_Interval->setValue(val);
}

void MainWindow::on_button_setTimer_clicked()
{
    _alarm->start();
    _actionPauseUnpause->setEnabled(true);
    restartTick();
}

void MainWindow::stopTimer()
{
    _alarm->stop();
    _actionPauseUnpause->setEnabled(false);
    restartTick();
}
void MainWindow::on_button_Cancel_clicked()
{
    this->hide();
}
