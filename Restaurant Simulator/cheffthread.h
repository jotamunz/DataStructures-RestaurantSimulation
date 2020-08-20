#ifndef CHEFFTHREAD_H
#define CHEFFTHREAD_H

#include <QtCore>
#include <QMutex>
#include <qdebug.h>
#include "restaurant.h"
#include "ui_mainwindow.h"
#include <QProgressBar>
#include "cheffform.h"
#include "ui_cheffform.h"

class CheffThread : public QThread
{
public:
    Restaurant *restaurant;
    Cheff *cheff;
    bool active = true;
    bool paused = false;
    QMutex * mutexInput;
    QMutex * mutexOutput;
    cheffForm * cheffF;
    Ui::MainWindow* mainUI;
    int progressBar = 0;

    CheffThread();
    void __init__(Restaurant*,Cheff*,QMutex*,QMutex*,cheffForm*,Ui::MainWindow*);
    void run();
    void pause();
    Order * getNewOrder();
    void serveOrder();
private slots:
    void on_actionColas_Principales_triggered();
};

#endif // CHEFFTHREAD_H
