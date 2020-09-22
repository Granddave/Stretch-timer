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
    explicit CountdownTimer(TimerType timerType, QObject* parent = nullptr, int interval = 30);

    void start();        // Start countdown timer with 'interval' seconds
    void pauseUnpause(); // Pause/unpause timer
    void stop();         // Reset countdown timer
    int remainingTime(); // Calculates, sets and returns the remaining time

    bool isActive() const
    {
        return m_countDownTimer->isActive();
    }
    bool paused() const
    {
        return m_paused;
    }
    int interval() const
    {
        return m_interval;
    }
    bool setInterval(int interval);

private slots:
    void sendTimeout(); // Triggers void timeout()
    void sendTick();    // Triggers int tick(int)

signals:
    void timeout(); // Sends signal when countdown timer hit zero.
    int tick(int);  // Sends update signal.

private:
    TimerType m_timerType;
    QTimer* m_countDownTimer; // Main countdown timer.
    QTimer* m_tickTimer;      // Sends update tick every second.
    QTime* m_elapsedTimer;    // Needed to calculate remaining time.
    bool m_paused;            // If timer is paused or not.
    int m_remaining;          // Seconds remaining, needed if paused.
    int m_interval;           // Time in seconds.
};

#endif // COUNTDOWNTIMER_H
