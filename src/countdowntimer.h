#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

// Qt
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QTime>

#include "common.h"

enum class TimerType
{
    seconds,
    minutes
};

class CountdownTimer : public QObject
{
    Q_OBJECT
public:
    explicit CountdownTimer(const TimerType timerType,
                            const int interval = 30,
                            QObject* parent = nullptr);

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
    bool setInterval(const int interval);

private slots:
    void sendTimeout(); // Triggers void timeout()
    void sendTick();    // Triggers int tick(int)

signals:
    void timeout();      // Sends signal when countdown timer hit zero.
    int tick(const int); // Sends update signal.

private:
    void calculateRemainder();

    TimerType m_timerType;
    QTimer* m_countDownTimer; // Main countdown timer.
    QTimer* m_tickTimer;      // Sends update tick every second.
    QTime m_elapsedTimer;     // Needed to calculate remaining time.
    bool m_paused = false;    // If timer is paused or not.
    int m_remaining{};        // Seconds remaining, needed if paused.
    int m_interval;           // Time in seconds.
};

#endif // COUNTDOWNTIMER_H
