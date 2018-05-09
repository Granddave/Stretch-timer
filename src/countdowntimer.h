#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include "common.h"

// Qt
#include <QObject>
#include <QTimer>
#include <QTime>

enum TimerType
{
    seconds = 1,
#if TIME_DEBUG
    minutes = 1
#else
    minutes = 60
#endif
};

class CountdownTimer : public QObject
{
    Q_OBJECT
public:
    explicit CountdownTimer(TimerType timerType, QObject *parent = 0, int interval = 30);

    void start();               // Start countdown timer with 'interval' seconds
    void pauseUnpause();        // Pause/unpause timer
    void stop();                // Reset countdown timer
    int remainingTime();        // Calculates, sets and returns the remaining time

    bool isActive() const { return _countDownTimer->isActive(); }
    bool paused()   const { return _paused; }
    int interval()  const { return _interval; }
    bool setInterval(int interval);

private slots:
    void sendTimeout();         // Triggers void timeout()
    void sendTick();            // Triggers int tick(int)

signals:
    void timeout();             // Sends signal when countdown timer hit zero.
    int tick(int);              // Sends update signal.

private:
    TimerType _timerType;
    QTimer* _countDownTimer;    // Main countdown timer.
    QTimer* _tickTimer;         // Sends update tick every second.
    QTime* _elapsedTimer;       // Needed to calculate remaining time.
    bool _paused;               // If timer is paused or not.
    int _remaining;             // Seconds remaining, needed if paused.
    int _interval;              // Time in seconds.
};

#endif // COUNTDOWNTIMER_H
