#include "alarm.h"

Alarm::Alarm(QObject *parent) : QObject(parent), _interval(10)
{
    setUp();
}

Alarm::Alarm(QObject *parent, int interval) : QObject(parent), _interval(interval)
{
    setUp();
}

void Alarm::setUp()
{
    _timer = new QTimer(this);
    _timer->setTimerType(Qt::TimerType::CoarseTimer);
    _timer->setSingleShot(true);
    _timer->setInterval(_interval * 1000);

    connect(_timer, SIGNAL(timeout()), this, SLOT(sendTimeout()));

    _time = new QTime();
}

void Alarm::sendTimeout()
{
    emit timeout();     // Sends timeout signal
}

void Alarm::pauseUnpause()
{
    if(!_paused)
    {
        static int remaining;
        remaining = _timer->remainingTime();
        _timer->stop();
        _timer->setInterval(remaining);
        _paused = true;
    }
    else
    {
        _timer->start(_interval);
        _time->start();
        _paused = false;
    }
}

void Alarm::stop()
{
    _timer->stop();
}

void Alarm::start()
{
    _timer->stop();
    _timer->start(_interval * 1000);
    _time->start();
}

int Alarm::remainingTime()
{
    return (_timer->interval()-_time->elapsed()) / 1000 + 1;
}
