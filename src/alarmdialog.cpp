#include "alarmdialog.h"

#ifdef AGGRESSIVE_MODE_SUPPORTED

#include "ui_alarmdialog.h"

AlarmDialog::AlarmDialog(QWidget* parent) : QDialog(parent), m_ui(new Ui::AlarmDialog)
{
    m_ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    m_idleTimer = new IdleTimer(this);

    connect(m_idleTimer, SIGNAL(tick(int)), this, SLOT(update(int)));
    connect(m_ui->button_close, SIGNAL(clicked(bool)), this, SLOT(close()));

    m_idleTimer->start();
}

AlarmDialog::~AlarmDialog()
{
    delete m_ui;
}

/* Disable Esc to close dialog */
void AlarmDialog::keyPressEvent(QKeyEvent* e)
{
    if (e->key() != Qt::Key_Escape)
    {
        QDialog::keyPressEvent(e);
    }
}

/* Update text and button */
void AlarmDialog::update(const int time)
{
    if (time == 0)
    {
        m_ui->button_close->setDisabled(false);
    }

    m_ui->label_timeLeft->setText("Don't touch the computer for another <b>" +
                                  QString::number(time) + "</b> seconds.");
}

#endif // AGGRESSIVE_MODE_SUPPORTED
