#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include "common.h"
#include "idletimer.h"

#ifdef AGGRESSIVE_MODE_SUPPORTED

// Qt
#include <QDialog>
#include <QKeyEvent>

namespace Ui
{
class AlarmDialog;
}

class AlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmDialog(QWidget* parent = nullptr);
    ~AlarmDialog();

private slots:
    void update(int time);

private:
    void keyPressEvent(QKeyEvent* e);
    Ui::AlarmDialog* m_ui;
    IdleTimer* m_idleTimer;
};

#endif // AGGRESSIVE_MODE_SUPPORTED
#endif // ALARMDIALOG_H
