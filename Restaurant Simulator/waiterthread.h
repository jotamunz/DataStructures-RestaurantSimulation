#ifndef WAITERTHREAD_H
#define WAITERTHREAD_H

#include <QtCore>
#include <QMutex>
#include <qdebug.h>
#include "restaurant.h"
#include "waiterform.h"
#include "ui_waiterform.h"
#include "queueform.h"
#include "ui_queueform.h"

class WaiterThread : public QThread
{
public:
    Restaurant * restaurant;
    Waiter * waiter;
    bool active = true;
    bool paused = false;
    QMutex * mutexOutput;
    QMutex * mutexDishes;
    QMutex * mutexInputs[3];
    QMutex * mutexBills;
    waiterForm * waiterF;
    queueForm * queueF;

    WaiterThread();
    void __init__(Restaurant*,Waiter*,QMutex*,QMutex*,QMutex*,QMutex*,QMutex*,QMutex*,waiterForm*,queueForm*);
    void run();
    void pause();
    Queue<Order*>* pickOrder();
    void updateQueueForm(queueForm*,QMutex*,QMutex*,QMutex*,QMutex*,QMutex*,QMutex*);

};

#endif // WAITERTHREAD_H

