#include "idletimer.h"

// Qt
#include <QSettings>
#include <QDebug>

// Windows
#include <windows.h>

IdleTimer::IdleTimer(QObject *parent) : QObject(parent)
{
    QSettings settings;
    _interval = settings.value("idleTimer", 10).toInt();
    _timer = new CountdownTimer(seconds, this, _interval);

    connect(_timer, SIGNAL(timeout()), this, SLOT(stopTimer()));
    connect(_timer, SIGNAL(tick(int)), this, SLOT(sendTick(int)));
}

void IdleTimer::start()
{
    _timer->start();
    emit tick(_interval);
    qDebug() << "IDLETIMER: Idletimer has started";
}

/* Returns the idle time in seconds */
int IdleTimer::getIdleTime()
{
    LASTINPUTINFO li;
    li.cbSize = sizeof(LASTINPUTINFO);
    GetLastInputInfo(&li);
    DWORD te = GetTickCount();
    int t = (te - li.dwTime) / 1000;

    return t;
}

/* Stops the timer */
void IdleTimer::stopTimer()
{
    _timer->stop();
    qDebug() << "IDLETIMER: Idletimer has been stopped";
}

/* Sends sends tick from countdown timer
 * or reset timer if the computer isn't left alone. */
void IdleTimer::sendTick(int countDown)
{
    if(countDown < _interval - getIdleTime())
    {
        _timer->start();
        emit tick(_interval);
    }
    else
    {
        emit tick(countDown);
    }
}
