#ifndef IDLETIMER_H
#define IDLETIMER_H

#include "common.h"

#ifdef AGGRESSIVE_MODE_SUPPORTED

#include "countdowntimer.h"

// Qt
#include <QObject>

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
    void sendTick(const int t);

private:
    CountdownTimer* m_timer;
    int m_interval;
};

#endif // AGGRESSIVE_MODE_SUPPORTED
#endif // IDLETIMER_H
