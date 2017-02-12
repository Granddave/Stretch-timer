#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("://myappico.png"));
    trayIcon->setVisible(true);
    trayIcon->showMessage( QString("Time to stretch!"),QString(""),QSystemTrayIcon::NoIcon, 10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
