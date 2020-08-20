#ifndef CASHIERTHREAD_H
#define CASHIERTHREAD_H

#include <QtCore>
#include <QMutex>
#include <qdebug.h>
#include "restaurant.h"
#include "ui_mainwindow.h"
#include "cashierform.h"
#include "ui_cashierform.h"

class CashierThread : public QThread
{
public:
    Restaurant *restaurant;
    bool active = true;
    bool paused = false;
    QMutex * mutexBills;
    cashierForm * cashierF;
    Ui::MainWindow * mainUI;

    CashierThread();
    void __init__(Restaurant*,QMutex*,cashierForm *,Ui::MainWindow*);
    void run();
    void pause();
};

#endif // CASHIERTHREAD_H
