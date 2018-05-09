#ifndef IDLETIMER_H
#define IDLETIMER_H

#include "countdowntimer.h"

// Qt
#include <QObject>

class IdleTimer : public QObject
{
    Q_OBJECT
public:
    explicit IdleTimer(QObject *parent = 0);
    void start();

signals:
    int tick(int);

private slots:
    int getIdleTime();
    void stopTimer();
    void sendTick(int t);

private:
    CountdownTimer* _timer;
    int _interval;
};

#endif // IDLETIMER_H
