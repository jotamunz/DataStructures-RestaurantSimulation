#ifndef ASSIGNERTHREAD_H
#define ASSIGNERTHREAD_H

#include <QtCore>
#include <QMutex>
#include <qdebug.h>
#include "restaurant.h"
#include "assignerform.h"
#include "ui_assignerform.h"
#include "tableform.h"
#include "ui_tableform.h"

class AssignerThread : public QThread
{
public:
    Restaurant *restaurant;
    bool active = true;
    bool paused = false;
    QMutex * mutexEntry;
    assignerForm * assignerF;
    tableForm * tableF;

    AssignerThread();
    void __init__(Restaurant*,QMutex*,assignerForm *,tableForm *);
    void run();
    void pause();
    bool isPriorityNumber(unsigned int);
    int getReservedTable(unsigned int);

};

#endif // ASSIGNERTHREAD_H
