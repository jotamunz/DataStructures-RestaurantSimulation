#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "restaurant.h"
#include "entrythread.h"
#include "assignerthread.h"
#include "tablethread.h"
#include "waiterthread.h"
#include "cheffthread.h"
#include "dishwasherthread.h"
#include "cashierthread.h"
#include "waitingform.h"
#include "assignerform.h"
#include "dishwasherform.h"
#include "cashierform.h"
#include "cheffform.h"
#include "tableform.h"
#include "waiterform.h"
#include "queueform.h"

struct Controller
{
public:
    int tableCount;
    int waiterCount;

    Restaurant* restaurant;
    EntryThread entry;
    AssignerThread assigner;
    TableThread tableThreads[20];
    WaiterThread waiterThreads[20];
    CheffThread cheffThreads[5];
    DishWasherThread dishWasher;
    CashierThread cashier;

    //GUI
    waitingForm * waitingF;
    assignerForm * assignerF;
    dishwasherForm * dishwasherF;
    cashierForm * cashierF;
    cheffForm * cheffF;
    tableForm * tableF;
    waiterForm * waiterF;
    queueForm * queueF;
    Ui::MainWindow * mainUI;

    QMutex * mutexInput0 = new QMutex();
    QMutex * mutexInput1 = new QMutex();
    QMutex * mutexInput2 = new QMutex();
    QMutex * mutexOutput = new QMutex();
    QMutex * mutexDishes = new QMutex();
    QMutex * mutexEntry = new QMutex();
    QMutex * mutexBills = new QMutex();

    Controller(int, int, Ui::MainWindow*, waitingForm *, assignerForm *, dishwasherForm *, cashierForm *, cheffForm *, tableForm *, waiterForm *, queueForm *);
    void startSimulation();
    void stopSimulation();

};

#endif // CONTROLLER_H
