#ifndef DISHWASHER_H
#define DISHWASHER_H

#include <QtCore>
#include <QMutex>
#include <qdebug.h>
#include "restaurant.h"
#include "ui_mainwindow.h"
#include "dishwasherform.h"
#include "ui_dishwasherform.h"

class DishWasherThread : public QThread
{
public:
    Restaurant *restaurant;
    bool active = true;
    bool paused = false;
    QMutex * mutexDishes;
    dishwasherForm * dishwasherF;
    Ui::MainWindow * mainUI;

    DishWasherThread();
    void __init__(Restaurant*,QMutex*,dishwasherForm*,Ui::MainWindow*);
    void run();
    void pause();

};

#endif // DISHWASHER_H
