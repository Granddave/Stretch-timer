#include "alarmdialog.h"
#include "ui_alarmdialog.h"

AlarmDialog::AlarmDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::AlarmDialog)
{
    _ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    _idleTimer = new IdleTimer(this);

    connect(_idleTimer, SIGNAL(tick(int)), this, SLOT(update(int)));
    connect(_ui->button_close, SIGNAL(clicked(bool)), this, SLOT(close()));

    _idleTimer->start();
}

AlarmDialog::~AlarmDialog()
{
    delete _ui;
}

/* Disable Esc to close dialog */
void AlarmDialog::keyPressEvent(QKeyEvent *e)
{
    if(e->key() != Qt::Key_Escape)
        QDialog::keyPressEvent(e);
}

/* Update text and button */
void AlarmDialog::update(int time)
{
    if(time == 0)
        _ui->button_close->setDisabled(false);

    _ui->label_timeLeft->setText("Don't touch the computer for another <b>"
                                 + QString::number(time)
                                 + "</b> seconds.");
}
