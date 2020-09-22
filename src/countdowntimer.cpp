#include "countdowntimer.h"

#include <QDebug>

CountdownTimer::CountdownTimer(TimerType timerType, QObject* parent, int interval)
    : QObject(parent), m_timerType(timerType), m_interval(interval)
{
    m_countDownTimer = new QTimer(this);
    m_countDownTimer->setSingleShot(true);
    m_countDownTimer->setInterval(m_interval * 1000 * m_timerType);
    connect(m_countDownTimer, SIGNAL(timeout()), this, SLOT(sendTimeout()));

    m_tickTimer = new QTimer(this);
    m_tickTimer->start(1000);
    connect(m_tickTimer, SIGNAL(timeout()), this, SLOT(sendTick()));

    m_elapsedTimer = new QTime();
    m_elapsedTimer->start();

    m_paused = false;
    stop();
}

/* Starts timer */
void CountdownTimer::start()
{
    m_paused = false;
    m_countDownTimer->stop();
    m_countDownTimer->start(m_interval * 1000 * m_timerType);
    m_tickTimer->start(1000);
    m_elapsedTimer->restart();

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
        m_elapsedTimer->restart();
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

    int interval = m_countDownTimer->interval();
    qint64 elapsed = m_elapsedTimer->elapsed();

    m_remaining = qRound((double)(interval - elapsed) / 1000);

    return m_remaining;
}

/* Sets new interval */
bool CountdownTimer::setInterval(int interval)
{
    if (interval < 1)
    {
        qDebug() << "WARNING: The interval is less than 1. interval: " << interval;
        return false;
    }
    else
    {
        m_interval = interval;
        return true;
    }
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
