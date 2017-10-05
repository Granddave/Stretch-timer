#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include "idletimer.h"

// Qt
#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class AlarmDialog;
}

class AlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmDialog(QWidget *parent = 0);
    ~AlarmDialog();

private slots:
    void update(int time);

private:
    void keyPressEvent(QKeyEvent* e);
    Ui::AlarmDialog *_ui;
    IdleTimer* _idleTimer;

};

#endif // ALARMDIALOG_H
