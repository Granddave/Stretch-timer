#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QTimer>
#include <QTime>

class Alarm : public QObject
{
    Q_OBJECT
public:
    explicit Alarm(QObject *parent = 0);
    explicit Alarm(QObject *parent = 0, int interval = 10);

    void pauseUnpause();    // Pause/unpause timer
    void stop();
    void start();
    int remainingTime();

    bool isActive() const { return _timer->isActive(); }
    bool paused()   const { return _paused; }
    int interval()  const { return _interval; }
    void setInterval(int interval) { _interval = interval; }


signals:
    void timeout();

public slots:
    void sendTimeout();

private:

    void setUp();

    QTimer *_timer;
    QTime *_time;
    bool _paused;
    int _interval;          // Time in seconds
};

#endif // ALARM_H
