#ifndef REFRESHTHREAD_H
#define REFRESHTHREAD_H

#include <QThread>

class refreshThread : public QThread
{
    Q_OBJECT

public:
    explicit refreshThread(QObject * parent = nullptr);
    void run();

signals:
    void refresh();


public slots:
};

#endif // REFRESHTHREAD_H
