#ifndef COMMON
#define COMMON

#include <qsystemdetection.h>
#if defined(Q_OS_WIN) | defined(Q_OS_LINUX)
#define AGGRESSIVE_MODE_SUPPORTED
#endif

#endif // COMMON
