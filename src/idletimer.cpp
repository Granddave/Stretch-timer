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
    const QSettings settings;
    m_interval = settings.value("idleTimer", IDLE_TIMER_DEFAULT).toInt();
    m_timer = new CountdownTimer(TimerType::seconds, m_interval, this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(stopTimer()));
    connect(m_timer, SIGNAL(tick(int)), this, SLOT(sendTick(int)));
}

void IdleTimer::start()
{
    m_timer->start();
    emit tick(m_interval);
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
    static XScreenSaverInfo* mit_info;

    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr)
    {
        return -1;
    }
    const int screen = DefaultScreen(display);
    mit_info = XScreenSaverAllocInfo();
    XScreenSaverQueryInfo(display, RootWindow(display, screen), mit_info);
    const time_t idle_time = (mit_info->idle) / 1000;
    XFree(mit_info);
    XCloseDisplay(display);
    return static_cast<int>(idle_time);
#endif
}

/* Stops the timer */
void IdleTimer::stopTimer()
{
    m_timer->stop();
    qDebug() << "IDLETIMER: Idletimer has been stopped";
}

/* Sends sends tick from countdown timer
 * or reset timer if the computer isn't left alone. */
void IdleTimer::sendTick(const int countDown)
{
    const int timeLeft = m_interval - getIdleTime();
    if (countDown < timeLeft)
    {
        m_timer->start();
        emit tick(m_interval);
    }
    else
    {
        emit tick(countDown);
    }
}

#endif // AGGRESSIVE_MODE_SUPPORTED
