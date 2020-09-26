#include "countdowntimer.h"

namespace
{
/* Changes the minute countdown timers to seconds. */
int getSeconds(const TimerType type)
{
#define TIME_DEBUG 0
#if TIME_DEBUG
    Q_UNUSED(type);
    return 1;
#else
    switch (type)
    {
        case TimerType::seconds:
            return 1;
        case TimerType::minutes:
            return 60;
    }

    qDebug() << "Unhandled case in getSeconds()!";
    return 60;
#endif
}
} // namespace

CountdownTimer::CountdownTimer(const TimerType timerType, const int interval, QObject* parent)
    : QObject(parent), m_timerType(timerType), m_interval(interval)
{
    m_countDownTimer = new QTimer(this);
    m_countDownTimer->setSingleShot(true);
    m_countDownTimer->setInterval(m_interval * 1000 * getSeconds(m_timerType));
    connect(m_countDownTimer, SIGNAL(timeout()), this, SLOT(sendTimeout()));

    m_tickTimer = new QTimer(this);
    m_tickTimer->start(1000);
    connect(m_tickTimer, SIGNAL(timeout()), this, SLOT(sendTick()));

    m_elapsedTimer.start();

    calculateRemainder();
    stop();
}

/* Starts timer */
void CountdownTimer::start()
{
    m_paused = false;
    m_countDownTimer->stop();
    m_countDownTimer->start(m_interval * 1000 * getSeconds(m_timerType));
    m_tickTimer->start(1000);
    m_elapsedTimer.restart();

    sendTick();
}

/* Toggles between paused and unpaused */
void CountdownTimer::pauseUnpause()
{
    if (!m_paused)
    {
        // Pause timer
        m_countDownTimer->stop();
        m_countDownTimer->setInterval(m_remaining);
        m_tickTimer->stop();
        m_paused = true;
    }
    else
    {
        // Unpause timer
        m_countDownTimer->start(m_remaining * 1000);
        m_tickTimer->start(1000);
        m_elapsedTimer.restart();
        m_paused = false;
    }

    sendTick();
}

/* Stops timer */
void CountdownTimer::stop()
{
    m_paused = false;
    m_countDownTimer->stop();
    m_tickTimer->stop();

    emit tick(0);
}

/* Returning number of seconds remaining */
int CountdownTimer::remainingTime()
{
    if (m_paused)
    {
        return m_remaining;
    }

    calculateRemainder();

    return m_remaining;
}

/* Sets new interval */
bool CountdownTimer::setInterval(const int interval)
{
    if (interval < 1)
    {
        qDebug() << "WARNING: The interval is less than 1. interval: " << interval;
        return false;
    }

    m_interval = interval;
    return true;
}

/* Sends timeout signal */
void CountdownTimer::sendTimeout()
{
    this->stop();
    emit timeout();
}

/* Sends tick signal every second.
 * Helps with updating UI */
void CountdownTimer::sendTick()
{
    emit tick(remainingTime());
}

void CountdownTimer::calculateRemainder()
{
    const int interval = m_countDownTimer->interval();
    const qint64 elapsed = m_elapsedTimer.elapsed();
    m_remaining = qRound(static_cast<double>(interval - elapsed) / 1000);
}
