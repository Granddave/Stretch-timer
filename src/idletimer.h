#ifndef IDLETIMER_H
#define IDLETIMER_H

#include "common.h"

#ifdef AGGRESSIVE_MODE_SUPPORTED

// Qt
#include <QObject>

#include "countdowntimer.h"

class IdleTimer : public QObject
{
    Q_OBJECT
public:
    explicit IdleTimer(QObject* parent = nullptr);
    void start();

signals:
    int tick(int);

private slots:
    int getIdleTime();
    void stopTimer();
    void sendTick(const int countDown);

private:
    CountdownTimer* m_timer;
    int m_interval;
};

#endif // AGGRESSIVE_MODE_SUPPORTED
#endif // IDLETIMER_H
