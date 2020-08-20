#ifndef TABLETHREAD_H
#define TABLETHREAD_H

#include <QtCore>
#include <QMutex>
#include <qdebug.h>
#include "restaurant.h"
#include "assignerform.h"
#include "ui_assignerform.h"
#include "ui_mainwindow.h"
#include "tableform.h"
#include "ui_tableform.h"

class TableThread : public QThread
{
public:
    Restaurant *restaurant;
    Table *table;
    bool active = true;
    assignerForm * assignerF;
    tableForm * tableF;
    Ui::MainWindow* mainUI;
    QLabel * label;

    TableThread();
    void __init__(Restaurant*,Table*,assignerForm*,tableForm*,Ui::MainWindow*);
    void run();
    
};

#endif // TABLETHREAD_H
