#include "idletimer.h"

#ifdef AGGRESSIVE_MODE_SUPPORTED

// Qt
#include <QSettings>
#include <QDebug>

// Headers for getting time of idle
#if defined(Q_OS_WIN32)
#include <windows.h>
#elif defined(Q_OS_LINUX)
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/extensions/scrnsaver.h>
#endif

#define IDLE_TIMER_DEFAULT 10 // sec

IdleTimer::IdleTimer(QObject* parent) : QObject(parent)
{
    QSettings settings;
    _interval = settings.value("idleTimer", IDLE_TIMER_DEFAULT).toInt();
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
#if defined(Q_OS_WIN32)
    LASTINPUTINFO li;
    li.cbSize = sizeof(LASTINPUTINFO);
    GetLastInputInfo(&li);
    DWORD te = GetTickCount();
    int t = (te - li.dwTime) / 1000;

    return t;
#elif defined(Q_OS_LINUX) // Cred to https://stackoverflow.com/a/4702411
    time_t idle_time;
    static XScreenSaverInfo* mit_info;
    Display* display;
    int screen;
    mit_info = XScreenSaverAllocInfo();
    if ((display = XOpenDisplay(NULL)) == NULL)
    {
        return (-1);
    }
    screen = DefaultScreen(display);
    XScreenSaverQueryInfo(display, RootWindow(display, screen), mit_info);
    idle_time = (mit_info->idle) / 1000;
    XFree(mit_info);
    XCloseDisplay(display);
    return idle_time;
#endif
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
    if (countDown < _interval - getIdleTime())
    {
        _timer->start();
        emit tick(_interval);
    }
    else
    {
        emit tick(countDown);
    }
}

#endif // AGGRESSIVE_MODE_SUPPORTED
