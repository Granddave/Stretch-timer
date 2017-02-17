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

    void stop();
    void start();
    void pauseUnpause();    // Pause/unpause timer
    int remainingTime();

    bool isActive() const { return _timer->isActive(); }
    bool paused()   const { return _paused; }
    void setPaused(bool b){ _paused = b;}
    int interval()  const { return _interval; }
    void setInterval(int interval) { _interval = interval; }
    int remaining() const { return _remaining; }

signals:
    void timeout();

public slots:
    void sendTimeout();

private:

    void setUp();

    QTimer *_timer;
    QTime *_time;
    bool _paused;
    int _remaining;
    int _interval;          // Time in seconds
};

#endif // ALARM_H
