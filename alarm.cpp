#include "alarm.h"

Alarm::Alarm(QObject *parent) : QObject(parent), _interval(10)
{
    setUp();
}

void Alarm::setUp()
{
    _timer = new QTimer(this);
    //_timer->setTimerType(Qt::TimerType::CoarseTimer);
    _timer->setSingleShot(true);
    _timer->setInterval(_interval * 1000 * 60);

    connect(_timer, SIGNAL(timeout()), this, SLOT(sendTimeout()));

    _time = new QTime();
    _time->start();
    _paused = false;
}

void Alarm::sendTimeout()
{
    emit timeout();     // Sends timeout signal
}

void Alarm::pauseUnpause()
{
    if(!_paused)
    {
		_remaining = remainingTime();
		stop();
        _timer->setInterval(_remaining);
        _paused = true;
    }
    else
    {
		_timer->start(_remaining * 1000);
        _time->restart();
        _paused = false;
    }
}

void Alarm::stop()
{
    _paused = false;
    _timer->stop();
}

void Alarm::start()
{
    _paused = false;
    _timer->stop();
    _timer->start(_interval * 1000 *60);
    _time->restart();
}

int Alarm::remainingTime()
{
    if(_paused)
    {
        return _remaining;
    }
    return _remaining = (_timer->interval() - _time->elapsed()) / 1000;
}
