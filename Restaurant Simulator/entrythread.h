#ifndef ENTRYTHREAD_H
#define ENTRYTHREAD_H

#include <QtCore>
#include <QMutex>
#include <qdebug.h>
#include "restaurant.h"
#include "waitingform.h"
#include "ui_waitingform.h"

class EntryThread : public QThread
{
public:
    Restaurant *restaurant;
    bool active = true;
    bool paused = false;
    QMutex * mutexEntry;
    waitingForm * waitingF;

    EntryThread();
    void __init__(Restaurant*,QMutex*,waitingForm*);
    void run();
    void pause();
    bool isPriorityNumber(unsigned int);

};

#endif // ENTRYTHREAD_H
