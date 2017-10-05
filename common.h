#ifndef COMMON
#define COMMON

#include <qsystemdetection.h>
#ifdef Q_OS_WIN
#define AGGRESSIVE_MODE_COMP
#endif

/* Changes the minute countdown timers to seconds. */
#define TIME_DEBUG 0

#endif // COMMON
