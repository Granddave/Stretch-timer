#include "countdowntimer.h"

#include <QDebug>

CountdownTimer::CountdownTimer(TimerType timerType, QObject* parent, int interval)
    : QObject(parent), _timerType(timerType), _interval(interval)
{
    _countDownTimer = new QTimer(this);
    _countDownTimer->setSingleShot(true);
    _countDownTimer->setInterval(_interval * 1000 * _timerType);
    connect(_countDownTimer, SIGNAL(timeout()), this, SLOT(sendTimeout()));

    _tickTimer = new QTimer(this);
    _tickTimer->start(1000);
    connect(_tickTimer, SIGNAL(timeout()), this, SLOT(sendTick()));

    _elapsedTimer = new QTime();
    _elapsedTimer->start();

    _paused = false;
    stop();
}

/* Starts timer */
void CountdownTimer::start()
{
    _paused = false;
    _countDownTimer->stop();
    _countDownTimer->start(_interval * 1000 * _timerType);
    _tickTimer->start(1000);
    _elapsedTimer->restart();

    sendTick();
}

/* Toggles between paused and unpaused */
void CountdownTimer::pauseUnpause()
{
    if (!_paused)
    {
        // Pause timer
        _countDownTimer->stop();
        _countDownTimer->setInterval(_remaining);
        _tickTimer->stop();
        _paused = true;
    }
    else
    {
        // Unpause timer
        _countDownTimer->start(_remaining * 1000);
        _tickTimer->start(1000);
        _elapsedTimer->restart();
        _paused = false;
    }

    sendTick();
}

/* Stops timer */
void CountdownTimer::stop()
{
    _paused = false;
    _countDownTimer->stop();
    _tickTimer->stop();

    emit tick(0);
}

/* Returning number of seconds remaining */
int CountdownTimer::remainingTime()
{
    if (_paused)
    {
        return _remaining;
    }

    int interval = _countDownTimer->interval();
    qint64 elapsed = _elapsedTimer->elapsed();

    _remaining = qRound((double)(interval - elapsed) / 1000);

    return _remaining;
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
        _interval = interval;
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
