#include "countdowntimer.h"

CountdownTimer::CountdownTimer(QObject *parent,
                               int interval) :
    QObject(parent),
    _interval(interval)
{
    _countDownTimer = new QTimer(this);
    _countDownTimer->setSingleShot(true);
    _countDownTimer->setInterval(_interval * 1000 * 60);
    connect(_countDownTimer, SIGNAL(timeout()), this, SLOT(sendTimeout()));

    _tickTimer = new QTimer(this);
    _tickTimer->start(1000);
    connect(_tickTimer, SIGNAL(timeout()), this, SLOT(sendTick()));

    _elapsedTimer = new QElapsedTimer();
    _elapsedTimer->start();

    _paused = false;
    sendTick();
}

void CountdownTimer::start()
{
    _paused = false;
    _countDownTimer->stop();
    _countDownTimer->start(_interval * 1000 * 60);
    _tickTimer->start(1000);
    _elapsedTimer->restart();

    sendTick();
}

void CountdownTimer::pauseUnpause()
{
    if(!_paused)
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

void CountdownTimer::stop()
{
    _paused = false;
    _countDownTimer->stop();
    _tickTimer->stop();

    sendTick();
}

int CountdownTimer::remainingTime()
{
    if(_paused)
        return _remaining;

    return _remaining = qRound((float)(_countDownTimer->interval() - _elapsedTimer->elapsed()) / 1000);
}

void CountdownTimer::sendTimeout()
{
    emit timeout();
}

void CountdownTimer::sendTick()
{
    emit tick(remainingTime());
}
